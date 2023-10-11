#pragma once
#include <string>

template <typename... Args>
inline std::string Format(const char* pFormat, Args...args)
{
	int Length = std::snprintf(nullptr, 0, pFormat, args...);
	if (Length <= 0)
		return "";
	char* Str = new char[Length + 1];
	std::string Result;
	std::snprintf(Str, Length + 1, pFormat, args...);
	Result = std::string(Str);
	delete[] Str;
	return Result;
}