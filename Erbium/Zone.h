#pragma once
#include "Finder.h"
#include <map>
bool AISpawned = false;
bool RTSM = false;
FVector* GSpawnPos;
UObject* (*GFPC)(UObject* World);
UObject* GetPC() {
	return GFPC(*GWorldPtr);
}

UObject* GetCM() {
	return *reinterpret_cast<UObject**>(__int64(GPC) + __int64(FindOffset("ObjectProperty /Script/Engine.PlayerController.CheatManager")));
}

void Update() {
	GPC = GetPC();
}

UObject* GAL_Func = nullptr;

FVector GetLocationNP(UObject* Target) {
	FVector Ret;
	if (GAL_Func == nullptr) {
		GAL_Func = FindObject("Function /Script/Engine.Actor.K2_GetActorLocation");
	}
	ProcessEventOG(Target, GAL_Func, &Ret);
	return Ret;
}

FVector* GetLocation(UObject* Target) {
	FVector Ret = GetLocationNP(Target);
	return new FVector(Ret);
}

void SCP(UObject* Part, EFortCustomPartType Type, UObject* Target = GPawn) {
	struct
	{
		TEnumAsByte<EFortCustomPartType> Type;
		UObject* ChosenCharacterPart;
	} Params;

	Params.Type = Type;
	Params.ChosenCharacterPart = Part;

	ProcessEventOG(Target, FindObject("Function /Script/FortniteGame.FortPlayerPawn.ServerChoosePart"), &Params);
}

void ShowSkin(UObject* FortHero) {
	UObject* HeadClass = FindObject("Class /Script/FortniteGame.CustomCharacterHeadData");
	UObject* BodyClass = FindObject("Class /Script/FortniteGame.CustomCharacterBodyData");
	UObject* HatClass = FindObject("Class /Script/FortniteGame.CustomCharacterHatData");
	UObject* BackPackClass = FindObject("Class /Script/FortniteGame.CustomCharacterBackpackData");
	TArray<UObject*> CharacterParts = *reinterpret_cast<TArray<UObject*>*>(__int64(FortHero) + __int64(FindOffset("ArrayProperty /Script/FortniteGame.FortHero.CharacterParts")));
	for (int i = 0; i < CharacterParts.Num(); i++) {
		UObject* Data = *reinterpret_cast<UObject**>(__int64(CharacterParts[i]) + __int64(FindOffset("ObjectProperty /Script/FortniteGame.CustomCharacterPart.AdditionalData")));
		if (Data->IsA(HeadClass) == true) {
			SCP(CharacterParts[i], EFortCustomPartType::Head);
		}
		if (Data->IsA(BodyClass) == true) {
			SCP(CharacterParts[i], EFortCustomPartType::Body);
		}
		if (Data->IsA(HatClass) == true) {
			SCP(CharacterParts[i], EFortCustomPartType::Hat);
		}
		if (Data->IsA(BackPackClass) == true) {
			SCP(CharacterParts[i], EFortCustomPartType::Backpack);
		}
	}
}

void FixBuilds() {
	FVector* Pos = GetLocation(GPawn);
	UObject* B1 = SpawnActor(*GWorldPtr, FindObject("Class /Script/FortniteGame.BuildingPlayerPrimitivePreview"), Pos, {}, FActorSpawnParameters());
	UObject* B2 = SpawnActor(*GWorldPtr, FindObject("Class /Script/FortniteGame.BuildingPlayerPrimitivePreview"), Pos, {}, FActorSpawnParameters());
	UObject* B3 = SpawnActor(*GWorldPtr, FindObject("Class /Script/FortniteGame.BuildingPlayerPrimitivePreview"), Pos, {}, FActorSpawnParameters());
	UObject* B4 = SpawnActor(*GWorldPtr, FindObject("Class /Script/FortniteGame.BuildingPlayerPrimitivePreview"), Pos, {}, FActorSpawnParameters());

	bool SetHidden = true;
	UObject* SAH = FindObject("Function /Script/Engine.Actor.SetActorHiddenInGame");
	ProcessEventOG(B1, SAH, &SetHidden);
	ProcessEventOG(B2, SAH, &SetHidden);
	ProcessEventOG(B3, SAH, &SetHidden);
	ProcessEventOG(B4, SAH, &SetHidden);
}

void SetActorGodMode(UObject* InActor, bool bGodMode)
{
	struct
	{
		UObject* Actor;
		bool bCanBeDamaged;
	} SetCanBeDamagedParams;

	SetCanBeDamagedParams.Actor = InActor;
	SetCanBeDamagedParams.bCanBeDamaged = !bGodMode;
	ProcessEventOG(FindObject("FortKismetLibrary /Script/FortniteGame.Default__FortKismetLibrary"), FindObject("Function /Script/FortniteGame.FortKismetLibrary.SetCanBeDamaged"), &SetCanBeDamagedParams);
}

//Not working atm
void HuskAI_Thread(UObject* HuskC) {
	UObject* AMIFunc = FindObject("Function /Script/Engine.Pawn.AddMovementInput");
	while (true && HuskC->IsValid())
	{
		/*FVector Pos = GetDifference(GetLocationNP(GPawn), GetLocationNP(HuskPawn));
		struct {
			FVector TargetPos;
			float Scale;
			bool Force;
		} params;
		params.TargetPos = Pos;
		params.Scale = 1;
		params.Force = true;
		ProcessEventOG(HuskPawn, AMIFunc, &params);*/
		struct {
			UObject* Target;
			float ARadius;
			bool SOO;
			bool UsePF;
			bool CanStrafe;
			UObject* FC;
			bool APP;
			void* Ret;
		} params;
		params.Target = GPawn;
		params.ARadius = 0.1f;
		params.SOO = false;
		params.UsePF = true;
		params.CanStrafe = true;//?
		params.FC = nullptr;
		params.APP = false;
		ProcessEventOG(HuskC, FindObject("Function /Script/AIModule.AIController.MoveToActor"), &params);
		Sleep(1000 / 30);
	}
}

class HuskAI {
public:

	void InitHusk() {
		FVector* Pos = GetLocation(GPawn);
		Pos->X += 500;
		HuskPawn = SpawnActor(*GWorldPtr, FindObject("BlueprintGeneratedClass /Game/Characters/Enemies/Husk/Blueprints/HuskPawn.HuskPawn_C"), Pos, new FVector(0, 275, 0), FActorSpawnParameters());
		if (HuskPawn != nullptr) {
			*reinterpret_cast<bool*>(__int64(HuskPawn) + __int64(FindOffset("BoolProperty /Script/FortniteGame.FortAIPawn.bIsSleeping"))) = false;
			UObject* NewController = SpawnActor(*GWorldPtr, FindObject("Class /Script/AIModule.AIController"), Pos, {}, FActorSpawnParameters());
			ProcessEventOG(NewController, FindObject("Function /Script/Engine.Controller.Possess"), &HuskPawn);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HuskAI_Thread, NewController, 0, 0);
		}
		AISpawned = false;
	}
private:
	UObject* HuskPawn;
	UObject* HuskController;
};

namespace Zone {
	void LoadSTWMap(FString Map) {
		Update();
		struct {
			FString InMap;
		} params;
		params.InMap = Map;
		ProcessEventOG(GPC, FindObject("Function /Script/Engine.PlayerController.SwitchLevel"), &params);
	}

	void GiveAllItems() {
		if (GVersion < 5.0f) {
			for (int i = 0; i < ObjObjects->Num(); i++)
			{
				UObject* Object = ObjObjects->GetItemByIndex(i)->Object;

				if (Object == nullptr)
				{
					continue;
				}
				if (Object->GetFullName().find("FortniteGame") == std::string::npos) {
					if (Object->GetFullName().find("FortAmmoItemDefinition") != std::string::npos) {
						Inventory::AddItemToInventory(Object, 999, 0, EFortQuickBars::Secondary);
					}
					if (Object->GetFullName().find("FortWeaponRangedItemDefinition") != std::string::npos || Object->GetFullName().find("FortWeaponMeleeItemDefinition") != std::string::npos)
					{
						Inventory::AddItemToInventory(Object, 1, 0, EFortQuickBars::Primary);
					}
				}
			}
		}
		else {
			for (int i = 0; i < GObjs->Num(); i++)
			{
				UObject* Object = GObjs->GetItemByIndex(i);

				if (Object == nullptr)
				{
					continue;
				}
				if (Object->GetFullName().find("FortniteGame") == std::string::npos) {
					if (Object->GetFullName().find("FortAmmoItemDefinition") != std::string::npos) {
						Inventory::AddItemToInventory(Object, 999, 0, EFortQuickBars::Secondary);
					}
					if (Object->GetFullName().find("FortWeaponRangedItemDefinition") != std::string::npos || Object->GetFullName().find("FortWeaponMeleeItemDefinition") != std::string::npos)
					{
						Inventory::AddItemToInventory(Object, 1, 0, EFortQuickBars::Primary);
					}
				}
			}
		}
	}

	void StartMatchSTW() {
		UObject* GM = *reinterpret_cast<UObject**>(__int64(*GWorldPtr) + __int64(Offsets::World::AuthorityGameMode));
		GCM = GetCM();
		if (GVersion >= 5.0f) {
			UObject* NCM = StaticConstructObjectInternal(FindObject("Class /Script/Engine.CheatManager"), GPC, 0, 0, 0, 0, 0, 0, 0);
			UObject** MCM = reinterpret_cast<UObject**>(__int64(GPC) + __int64(FindOffset("ObjectProperty /Script/Engine.PlayerController.CheatManager")));
			*MCM = NCM;
			GCM = NCM;
		}
		struct {
			UObject* Controller;
			FString IncomingName;
			UObject* RetValue;
		} params;
		params.Controller = GPC;
		params.IncomingName = FString(L"");
		ProcessEventOG(GM, FindObject("Function /Script/Engine.GameModeBase.K2_FindPlayerStart"), &params);
		if (params.RetValue->IsValid() && GVersion < 5.0f) {
			GSpawnPos = GetLocation(params.RetValue);
		}
		if (GVersion >= 2.5f) {
			GPawn = SpawnActor(*GWorldPtr, FindObject("BlueprintGeneratedClass /Game/Athena/PlayerPawn_Athena.PlayerPawn_Athena_C"), GSpawnPos, new FVector(0, 275, 0), FActorSpawnParameters());
		}
		else {
			GPawn = SpawnActor(*GWorldPtr, FindObject("BlueprintGeneratedClass /Game/Abilities/Player/Pawns/PlayerPawn_Generic.PlayerPawn_Generic_C"), GSpawnPos, new FVector(0, 275, 0), FActorSpawnParameters());
		}
		ProcessEventOG(GPC, FindObject("Function /Script/Engine.Controller.Possess"), &GPawn);
		ProcessEventOG(GCM, FindObject("Function /Script/Engine.CheatManager.God"), nullptr);
		if (GVersion < 5.0f) {
			ProcessEventOG(GM, FindObject("Function /Script/Engine.GameMode.StartMatch"), nullptr);
			ProcessEventOG(GCM, FindObject("Function /Script/FortniteGame.FortCheatManager.ToggleInfiniteAmmo"), nullptr);
		}
		if (GVersion > 7.0f) {
			ProcessEventOG(GPC, FindObject("Function /Script/FortniteGame.FortPlayerController.ServerReadyToStartMatch"), nullptr);
		}
		UObject* GSC = FindObject("Class /Script/FortniteGame.FortGameStateZone");
		SpawnActor(*GWorldPtr, GSC, {}, {}, FActorSpawnParameters());
		UObject* PlayerState = *reinterpret_cast<UObject**>(__int64(GPC) + __int64(FindOffset("ObjectProperty /Script/Engine.Controller.PlayerState")));
		*reinterpret_cast<bool*>(__int64(PlayerState) + __int64(FindOffset("BoolProperty /Script/FortniteGame.FortPlayerState.bIsGameSessionOwner"))) = true;
		ProcessEventOG(PlayerState, FindObject("Function /Script/FortniteGame.FortPlayerState.OnRep_SessionOwner"), nullptr);
		ProcessEventOG(PlayerState, FindObject("Function /Script/FortniteGame.FortPlayerState.OnRep_CharacterParts"), nullptr);
		ProcessEventOG(GPawn, FindObject("Function /Script/FortniteGame.FortPlayerPawn.OnCharacterPartsReinitialized"), nullptr);
		UObject* SKM = *reinterpret_cast<UObject**>(__int64(GPawn) + __int64(FindOffset("ObjectProperty /Script/Engine.Character.Mesh")));
		ProcessEventOG(SKM, FindObject("Function /Script/Engine.SkeletalMeshComponent.GetAnimInstance"), &GAI);
	}
}