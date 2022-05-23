#pragma once

#define AddCheats_430 "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 48 8B 01 0F B6 DA 48 8B F9 FF 90 ? ? ? ? 48 83 BF ? ? ? ? ? 48 8B F0" //Didnt work...

#define ProcessEvent_G "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 8B 41 0C 45 33 F6 3B 05 ? ? ? ? 4D 8B F8 48 8B F2 4C 8B E1 41 B8 ? ? ? ? 7D 2A"
#define Free_G "48 85 C9 74 2E 53"
#define GObjects_G "49 63 C8 48 8D 14 40 48 8B 05 ? ? ? ? 48 8B 0C C8 48 8D 04 D1" //10

#define FNTS_C2 "48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 30 8B 01 48 8B F1 44 8B 49 04 8B F8"
#define SpawnActor_C2 "53 56 57 48 83 EC 70 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 60 0F 28 1D ? ? ? ? 0F 57 D2 48 8B B4 24 B0"
#define GWorld_C2 "48 89 05 ? ? ? ? 48 8B B6 ? ? ? ?" //3

#define SpawnActor_C1 "40 53 56 57 48 83 EC 70 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 0F 28 1D ? ? ? ? 0F 57 D2 48 8B B4 24 ? ? ? ? 0F 28 CB"
#define GWorld_C1 "48 8B 1D ? ? ? ? 48 85 DB 74 3B 41" //3
#define ObjObjects_420 "48 8B 05 ? ? ? ? 48 8D 1C C8 81 4B ? ? ? ? ? 49 63 76 30" //3
#define FNTS_OLD "48 89 5C 24 ? 57 48 83 EC 40 83 79 04 00 48 8B DA 48 8B F9"
#define FNTS_C1 "48 89 5C 24 ? 57 48 83 EC 30 83 79 04 00 48 8B DA 48 8B F9"
#define Free_420 "48 85 C9 74 1D 4C 8B 05 ? ? ? ? 4D 85 C0"

#define GWorld_1_8 "48 8B 1D ? ? ? ? ? ? ? 10 4C 8D 4D ? 4C" //3
#define ObjObjects_1_8 "48 8D 0D ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 48 8B D6" //3
#define Free_Old "48 85 C9 74 2E 53 48 83 EC 20 48 8B D9 48 8B 0D ? ? ? ? 48 85 C9 75 0C"
#define ProcessEvent_Old "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 48 63 41 0C"
