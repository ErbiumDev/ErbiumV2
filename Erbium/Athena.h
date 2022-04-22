#pragma once
#include "Zone.h"
bool IsBR = false;
namespace Athena {
	void LoadBRMap() {
		Update();
		struct {
			FString InMap;
		} params;
		params.InMap = L"Athena_Terrain";
		ProcessEventOG(GPC, FindObject("Function /Script/Engine.PlayerController.SwitchLevel"), &params);
	}

	void StartMatchBR() {
		UObject* GM = *reinterpret_cast<UObject**>(__int64(*GWorldPtr) + __int64(Offsets::World::AuthorityGameMode));
		GCM = GetCM();
		if (GCM->IsValid() == false) {
			StaticConstructObjectInternal = decltype(StaticConstructObjectInternal)(FindPattern("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 44 8B A5 ? ? ? ? 48 8D 05 ? ? ? ?"));
			UObject* NCM = StaticConstructObjectInternal(FindObject("Class /Script/Engine.CheatManager"), GPC, 0, 0, 0, 0, 0, 0, 0);
			*reinterpret_cast<UObject**>(__int64(GPC) + __int64(FindOffset("ObjectProperty /Script/Engine.PlayerController.CheatManager"))) = NCM;
			GCM = NCM;
		}
		GPawn = SpawnActor(*GWorldPtr, FindObject("BlueprintGeneratedClass /Game/Athena/PlayerPawn_Athena.PlayerPawn_Athena_C"), new FVector(1,1,10000), new FVector(0, 0, 0), FActorSpawnParameters());
		ProcessEventOG(GPC, FindObject("Function /Script/Engine.Controller.Possess"), &GPawn);
		ProcessEventOG(GCM, FindObject("Function /Script/Engine.CheatManager.God"), nullptr);
		if (GVersion >= 7.0f) {
			ProcessEventOG(GPC, FindObject("Function /Script/FortniteGame.FortPlayerController.ServerReadyToStartMatch"), nullptr);
		}
		ProcessEventOG(GM, FindObject("Function /Script/Engine.GameMode.StartMatch"), nullptr);
		
		UObject* PlayerState = *reinterpret_cast<UObject**>(__int64(GPC) + __int64(FindOffset("ObjectProperty /Script/Engine.Controller.PlayerState")));
		if (IsBR == false) {
			SpawnActor(*GWorldPtr, FindObject("Class /Script/FortniteGame.FortGameStateZone"), GetLocation(GPawn), {}, FActorSpawnParameters());
			*reinterpret_cast<bool*>(__int64(PlayerState) + __int64(FindOffset("BoolProperty /Script/FortniteGame.FortPlayerState.bIsGameSessionOwner"))) = true;
			ProcessEventOG(PlayerState, FindObject("Function /Script/FortniteGame.FortPlayerState.OnRep_SessionOwner"), nullptr);
		}
		UObject* FortHero = FindObject("FortHero_");
		ShowSkin(FortHero);
		ProcessEventOG(PlayerState, FindObject("Function /Script/FortniteGame.FortPlayerState.OnRep_CharacterParts"), nullptr);
		UObject* SKM = *reinterpret_cast<UObject**>(__int64(GPawn) + __int64(FindOffset("ObjectProperty /Script/Engine.Character.Mesh")));
		ProcessEventOG(SKM, FindObject("Function /Script/Engine.SkeletalMeshComponent.GetAnimInstance"), &GAI);
	}
}