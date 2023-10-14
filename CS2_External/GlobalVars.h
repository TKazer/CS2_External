#pragma once
#include "Game.h"
#include "Globals.hpp"

class globalvars
{
public:
    DWORD64 address = 0;
public:
    float g_fRealTime;
    int g_iFrameCount;
    int g_iMaxClients;
    float g_fIntervalPerTick;
    float g_fCurrentTime;
    float g_fCurrentTime2;
    int g_iTickCount;
    float g_fIntervalPerTick2;
    void* g_vCurrentNetchan; // ?
    char* g_cCurrentMap; // ? https://www.unknowncheats.me/forum/counter-strike-2-a/603800-check-empty-mapname-globalvars.html
    char* g_cCurrentMapName; // ? https://www.unknowncheats.me/forum/counter-strike-2-a/603800-check-empty-mapname-globalvars.html
public:
    bool UpdateGlobalvars();
    bool GetRealTime();
    bool GetFrameCount();
    bool GetMaxClients();
    bool GetIntervalPerTick();
    bool GetcurrentTime();
    bool GetcurrentTime2();
    bool GetTickCount();
    bool GetIntervalPerTick2();
    bool GetCurrentNetchan();
    bool GetCurrentMap();
    bool GetCurrentMapName();
private:
};