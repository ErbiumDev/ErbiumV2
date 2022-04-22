#include "Base.h"
#pragma comment(lib,"minhook/minhook.lib")
#include "minhook/MinHook.h"
void Init() {
    MH_Initialize();
    float GameVersion = std::stof(GetFortniteVersion());
    uintptr_t PEAddr = 0;
    StaticConstructObjectInternal = decltype(StaticConstructObjectInternal)(FindPattern("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 44 8B A5 ? ? ? ? 48 8D 05 ? ? ? ?"));
    if (GameVersion < 2.5f) {
        IsC1 = true;
        uintptr_t GObjsAddr = FindPattern(ObjObjects_1_8, true, 3);
        ObjObjects = new UObjectArray(reinterpret_cast<OAP*>(GObjsAddr)->Objects);
        uintptr_t FNTSAddr = FindPattern(FNTS_OLD);
        FNameToString = decltype(FNameToString)(FNTSAddr);
        uintptr_t FreeAddr = FindPattern(Free_Old);
        FnFree = decltype(FnFree)(FreeAddr);
        PEAddr = FindPattern(ProcessEvent_Old);
    }
    else if (GameVersion < 5.0f) {
        IsC1 = true;
        uintptr_t GObjsAddr = FindPattern(ObjObjects_420,true,3);
        ObjObjects = reinterpret_cast<UObjectArray*>(GObjsAddr);
        uintptr_t FNTSAddr = FindPattern(FNTS_OLD);
        FNameToString = decltype(FNameToString)(FNTSAddr);
        uintptr_t FreeAddr = FindPattern(Free_420);
        FnFree = decltype(FnFree)(FreeAddr);
        void** Engine = *reinterpret_cast<void***>(FindObject("FortEngine_"));
        PEAddr = (uintptr_t)Engine[64];
    }
    else if (GameVersion < 11.0f) {
        IsC1 = true;
        uintptr_t GObjsAddr = FindPattern(GObjects_G, true, 10);
        GObjs = reinterpret_cast<GObjects*>(GObjsAddr);
        uintptr_t FNTSAddr = FindPattern(FNTS_C1);
        FNameToString = decltype(FNameToString)(FNTSAddr);
        uintptr_t FreeAddr = FindPattern(Free_G);
        FnFree = decltype(FnFree)(FreeAddr);
        PEAddr = FindPattern(ProcessEvent_G);
    }
    else if (GameVersion < 16.0f) {
        uintptr_t GObjsAddr = FindPattern(GObjects_G, true, 10);
        GObjs = reinterpret_cast<GObjects*>(GObjsAddr);
        uintptr_t FNTSAddr = FindPattern(FNTS_C2);
        FNameToString = decltype(FNameToString)(FNTSAddr);
        uintptr_t FreeAddr = FindPattern(Free_G);
        FnFree = decltype(FnFree)(FreeAddr);
        PEAddr = FindPattern(ProcessEvent_G);
    }
    else if (GameVersion >= 16.0f) {
        MessageBoxA(0, "16.0+ Versions are Not Supported!", "Erbium", MB_OK);
        return;
    }
    if (IsC1 == true) {
        if (GameVersion >= 2.5f) {
            uintptr_t GWorldAddr = FindPattern(GWorld_C1, true, 3);
            GWorldPtr = reinterpret_cast<UObject**>(GWorldAddr);
        }
        else {
            uintptr_t GWorldAddr = FindPattern(GWorld_1_8, true, 3);
            GWorldPtr = reinterpret_cast<UObject**>(GWorldAddr);
        }
        uintptr_t SAAddr = FindPattern(SpawnActor_C1);
        SpawnActor = decltype(SpawnActor)(SAAddr);
    }
    else {
        uintptr_t GWorldAddr = FindPattern(GWorld_C2, true, 3);
        if (GWorldAddr == 0) {
            GWorldAddr = FindPattern(GWorld_C1, true, 3);
        }
        GWorldPtr = reinterpret_cast<UObject**>(GWorldAddr);
        uintptr_t SAAddr = FindPattern(SpawnActor_C2);
        SpawnActor = decltype(SpawnActor)(SAAddr);
    }
    GVersion = GameVersion;
    GFPC = decltype(GFPC)(FindPattern("83 B9 ? ? ? ? ? 7E ? 48 8B 89 ? ? ? ? E9"));
    ProcessEventOG = decltype(ProcessEventOG)(PEAddr);
    Offsets::InitOffsets();
    UI::Init();
    UI::ShowWindow();
    
    MH_CreateHook((LPVOID)PEAddr, PEHook, (LPVOID*)&ProcessEventOG);
    MH_EnableHook((LPVOID)PEAddr);
};

BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, LPVOID Reserved)
{
    switch (Reason)
    {
    case DLL_PROCESS_ATTACH:
        Init();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
