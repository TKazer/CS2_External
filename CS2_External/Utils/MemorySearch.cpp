#include "ProcessManager.hpp"

#define BLOCKMAXSIZE 409600
BYTE* MemoryData;
short Next[260];

WORD GetSignatureArray(std::string Signature, WORD* SignatureArray)
{
	int len = 0;
	WORD Length = Signature.length() / 3 + 1;

	for (int i = 0; i < Signature.length(); )
	{
		char num[2];
		num[0] = Signature[i++];
		num[1] = Signature[i++];
		i++;
		if (num[0] != '?' && num[1] != '?')
		{
			int sum = 0;
			WORD a[2];
			for (int i = 0; i < 2; i++)
			{
				if (num[i] >= '0' && num[i] <= '9')
					a[i] = num[i] - '0';
				else if (num[i] >= 'a' && num[i] <= 'z')
					a[i] = num[i] - 87;
				else if (num[i] >= 'A' && num[i] <= 'Z')
					a[i] = num[i] - 55;
			}
			sum = a[0] * 16 + a[1];
			SignatureArray[len++] = sum;
		}
		else
			SignatureArray[len++] = 256;
	}
	return Length;
}

void GetNext(short* next, WORD* Signature, WORD SignatureLength)
{
	for (int i = 0; i < 260; i++)
		next[i] = -1;
	for (int i = 0; i < SignatureLength; i++)
		next[Signature[i]] = i;
}

void SearchMemoryBlock(HANDLE hProcess, WORD* Signature, WORD SignatureLength, DWORD64 StartAddress, DWORD size, std::vector<DWORD64>& ResultArray)
{
	if (!ReadProcessMemory(hProcess, (LPCVOID)StartAddress, MemoryData, size, NULL))
		return;

	for (int i = 0, j, k; i < size;)
	{
		j = i; k = 0;

		for (; k < SignatureLength && j < size && (Signature[k] == MemoryData[j] || Signature[k] == 256); k++, j++);

		if (k == SignatureLength)
			ResultArray.push_back(StartAddress + i);

		if ((i + SignatureLength) >= size)
			return;

		int num = Next[MemoryData[i + SignatureLength]];
		if (num == -1)
			i += (SignatureLength - Next[256]);
		else
			i += (SignatureLength - num);
	}
}


std::vector<DWORD64> ProcessManager::SearchMemory(std::string Signature, DWORD64 StartAddress, DWORD64 EndAddress)
{
	MemoryData = new BYTE[BLOCKMAXSIZE];
	int i = 0;
	unsigned long BlockSize;
	MEMORY_BASIC_INFORMATION mbi;
	WORD SignatureLength = Signature.length() / 3 + 1;
	WORD* SignatureArray = new WORD[SignatureLength];
	std::vector<DWORD64>ResultArray;
	GetSignatureArray(Signature, SignatureArray);
	GetNext(Next, SignatureArray, SignatureLength);

	while (VirtualQueryEx(hProcess, (LPCVOID)StartAddress, &mbi, sizeof(mbi)) != 0)
	{
		i = 0;
		BlockSize = mbi.RegionSize;
		while (BlockSize >= BLOCKMAXSIZE)
		{
			SearchMemoryBlock(hProcess, SignatureArray, SignatureLength, StartAddress + (BLOCKMAXSIZE * i), BLOCKMAXSIZE, ResultArray);
			BlockSize -= BLOCKMAXSIZE; i++;
		}
		SearchMemoryBlock(hProcess, SignatureArray, SignatureLength, StartAddress + (BLOCKMAXSIZE * i), BlockSize, ResultArray);
		
		StartAddress += mbi.RegionSize;

		if (EndAddress != 0 && StartAddress > EndAddress)
			return ResultArray;
	}
	delete[] MemoryData;
	delete[] SignatureArray;
	return ResultArray;
}
