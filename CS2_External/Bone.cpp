#include "Bone.h"

bool CBone::UpdateAllBoneData(const uintptr_t& EntityPawnAddress)
{
	if (EntityPawnAddress == 0)
		return false;
	this->EntityPawnAddress = EntityPawnAddress;

    uintptr_t GameSceneNode = ProcessMgr.RAM<uintptr_t>(EntityPawnAddress + Offset::Pawn.GameSceneNode);
	if (!GameSceneNode)
		return false;
    uintptr_t BoneArrayAddress = ProcessMgr.RAM<uintptr_t>(GameSceneNode + Offset::Pawn.BoneArray);
    if (!BoneArrayAddress)
        return false;

	BoneJointData BoneArray[28]{};
	if (!ProcessMgr.ReadMemory(BoneArrayAddress, BoneArray, 28 * sizeof(BoneJointData)))
		return false;

	for (int i = 0; i < 28; i++)
	{
		Vec2 ScreenPos;
		bool IsVisible = false;
        if (gGame.View.WorldToScreen(BoneArray[i].Pos, ScreenPos))
            IsVisible = true;
        else
            IsVisible = false;

		this->BonePosList.push_back({ BoneArray[i].Pos ,ScreenPos,IsVisible });
	}

	return this->BonePosList.size() > 0;
}
