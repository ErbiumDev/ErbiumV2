#pragma once
#include <Windows.h>
#include <string>
#include <locale>
#include <vector>
#include "Sigs.h"
#include "UI.hpp"
bool InGame = false;
bool LogPE = false;
uintptr_t CMS_Offset = 0;
uintptr_t WTS_Offset = 0;
UObject* JumpFunc;
UObject* GetAnimHRFunc;
UObject* PlayMontageFunc;
TEnumAsByte<EFortCustomBodyType> MyBodyType;
TEnumAsByte<EFortCustomGender> MyGender;

LPVOID PEHook(UObject* Object, UObject* Function, void* Params) {
	std::string FuncName = Function->GetFullName();

	if (FuncName.find("ReadyToStartMatch") != std::string::npos && RTSM == false) {
		RTSM = true;
		Update();
		UObject* GM = *reinterpret_cast<UObject**>(__int64(*GWorldPtr) + __int64(Offsets::World::AuthorityGameMode));
		if (IsBR == true) {
			PlayMontageFunc = FindObject("Function /Script/Engine.AnimInstance.Montage_Play");
			GetAnimHRFunc = FindObject("Function /Script/FortniteGame.FortMontageItemDefinitionBase.GetAnimationHardReference");
			JumpFunc = FindObject("Function /Script/Engine.Character.Jump");
			Athena::StartMatchBR();
		}
		else {
			PlayMontageFunc = FindObject("Function /Script/Engine.AnimInstance.Montage_Play");
			GetAnimHRFunc = FindObject("Function /Script/FortniteGame.FortMontageItemDefinitionBase.GetAnimationHardReference");
			JumpFunc = FindObject("Function /Script/Engine.Character.Jump");
			Zone::StartMatchSTW();
		}
		MyBodyType = GetBodyType();
		MyGender = GetGender();
		FixBuilds();
	}

	if (FuncName.find("ServerCreateBuilding") != std::string::npos) {
		auto CurrentBuildableClass = *reinterpret_cast<UObject**>(__int64(GPC) + FindOffset("ClassProperty /Script/FortniteGame.FortPlayerController.CurrentBuildableClass"));
		auto LastPreviewLocation = *reinterpret_cast<FVector*>(__int64(GPC) + FindOffset("StructProperty /Script/FortniteGame.FortPlayerController.LastBuildPreviewGridSnapLoc"));
		auto LastPreviewRotation = *reinterpret_cast<FVector*>(__int64(GPC) + FindOffset("StructProperty /Script/FortniteGame.FortPlayerController.LastBuildPreviewGridSnapRot"));
		auto BuildingActor = SpawnActor(*GWorldPtr, CurrentBuildableClass, new FVector(LastPreviewLocation), new FVector(LastPreviewRotation), FActorSpawnParameters());
		struct
		{
			UObject* BuildingOwner;
			UObject* SpawningController;
		} params;
		params.BuildingOwner = BuildingActor;
		params.SpawningController = GPC;
		ProcessEventOG(BuildingActor, FindObject("Function /Script/FortniteGame.BuildingActor.InitializeKismetSpawnedBuildingActor"), &params);
	}

	//BoogieBombs
	if (FuncName.find("B_Prj_Athena_DanceGrenade_C.OnExploded") != std::string::npos) {
		struct BoogieBombExploded_Params{
			TArray<UObject*> HitActors;
			TArray<UObject*> HitResults;
		};
		BoogieBombExploded_Params* BB_Params = reinterpret_cast<BoogieBombExploded_Params*>(Params);
		for (int i = 0; i < BB_Params->HitActors.Num(); i++) {
			if (BB_Params->HitActors[i]->GetFullName().find("Pawn") != std::string::npos) {
				struct
				{
					UObject* MontageToPlay;
					float InPlayRate;
					EMontagePlayReturnType ReturnValueType;
					float InTimeToStartMontageAt;
					bool bStopAllMontages;
					float ReturnValue;
				} params2;
				params2.MontageToPlay = FindObject("AnimMontage /Game/Animation/Game/MainPlayer/Emotes/Emote_DG_Disco_M.Emote_DG_Disco_M");
				params2.InPlayRate = 1;
				params2.InTimeToStartMontageAt = 0;
				params2.bStopAllMontages = true;
				params2.ReturnValueType = EMontagePlayReturnType::Duration;
				UObject* AnimInst;
				UObject* SKM = *reinterpret_cast<UObject**>(__int64(BB_Params->HitActors[i]) + __int64(FindOffset("ObjectProperty /Script/Engine.Character.Mesh")));
				ProcessEventOG(SKM, FindObject("Function /Script/Engine.SkeletalMeshComponent.GetAnimInstance"), &AnimInst);
				ProcessEventOG(AnimInst, PlayMontageFunc, &params2);
			}
		}
	}

	if (FuncName.find("ServerLoadingScreenDropped") != std::string::npos) {
		if (IsBR == false) {
			Inventory::InitInventory();
			Zone::GiveAllItems();
			Inventory::AddItemToInventory(FindObject("FortWeaponMeleeItemDefinition /Game/Items/Weapons/Melee/Harvest/WID_Harvest_Pickaxe_C_T02.WID_Harvest_Pickaxe_C_T02"), 1, 0, EFortQuickBars::Primary);
			Inventory::AddItemToInventory(FindObject("FortBuildingItemDefinition /Game/Items/Weapons/BuildingTools/BuildingItemData_Wall.BuildingItemData_Wall"), 1, 0, EFortQuickBars::Secondary);
			Inventory::AddItemToInventory(FindObject("FortBuildingItemDefinition /Game/Items/Weapons/BuildingTools/BuildingItemData_Floor.BuildingItemData_Floor"), 1, 1, EFortQuickBars::Secondary);
			Inventory::AddItemToInventory(FindObject("FortBuildingItemDefinition /Game/Items/Weapons/BuildingTools/BuildingItemData_Stair_W.BuildingItemData_Stair_W"), 1, 2, EFortQuickBars::Secondary);
			Inventory::AddItemToInventory(FindObject("FortBuildingItemDefinition /Game/Items/Weapons/BuildingTools/BuildingItemData_RoofS.BuildingItemData_RoofS"), 1, 3, EFortQuickBars::Secondary);
			Inventory::UpdateInventory();
			Inventory::AddItemToInventory(FindObject("FortResourceItemDefinition /Game/Items/ResourcePickups/WoodItemData.WoodItemData"), 999, 0, EFortQuickBars::Secondary);
			Inventory::AddItemToInventory(FindObject("FortResourceItemDefinition /Game/Items/ResourcePickups/StoneItemData.StoneItemData"), 999, 0, EFortQuickBars::Secondary);
			Inventory::AddItemToInventory(FindObject("FortResourceItemDefinition /Game/Items/ResourcePickups/MetalItemData.MetalItemData"), 999, 0, EFortQuickBars::Secondary);
		}
		else {
			Inventory::InitInventory();
			Inventory::AddItemToInventory(FindObject("FortWeaponMeleeItemDefinition /Game/Athena/Items/Weapons/WID_Harvest_Pickaxe_Athena_C_T01.WID_Harvest_Pickaxe_Athena_C_T01"), 1, 0, EFortQuickBars::Primary);
			Inventory::UpdateInventory();
		}
		CMS_Offset = FindOffset("ByteProperty /Script/FortniteGame.FortPawn.CurrentMovementStyle");
		WTS_Offset = FindOffset("BoolProperty /Script/FortniteGame.FortPlayerController.bWantsToSprint");
		InGame = true;
	}

	if (FuncName.find("ServerExecuteInventoryItem") != std::string::npos) {
		FGuid* GUID = reinterpret_cast<FGuid*>(Params);
		Inventory::EquipInventoryItem(GUID);
	}

	if (FuncName.find("ServerEmote") != std::string::npos && GVersion >= 2.5f) {
		struct EmoteParams {
			FName EmoteAsset;
		};
		std::string EmoteName = static_cast<EmoteParams*>(Params)->EmoteAsset.ToString().c_str();
		EmoteName += "." + EmoteName;
		auto EmoteDef = FindObject(EmoteName);
		struct
		{
			TEnumAsByte<EFortCustomBodyType> BodyType;
			TEnumAsByte<EFortCustomGender> Gender;
			UObject* ReturnValue;
		} params;
		params.BodyType = MyBodyType;
		params.Gender = MyGender;
		ProcessEventOG(EmoteDef, GetAnimHRFunc, &params);
		struct
		{
			UObject* MontageToPlay;
			float InPlayRate;
			EMontagePlayReturnType ReturnValueType;
			float InTimeToStartMontageAt;
			bool bStopAllMontages;
			float ReturnValue;
		} params2;
		params2.MontageToPlay = params.ReturnValue;
		params2.InPlayRate = 1;
		params2.InTimeToStartMontageAt = 0;
		params2.bStopAllMontages = true;
		params2.ReturnValueType = EMontagePlayReturnType::Duration;
		ProcessEventOG(GAI, PlayMontageFunc, &params2);
	}

	if (FuncName.find("Tick") != std::string::npos && InGame == true) {
		if (GVersion < 5.0f && GetAsyncKeyState(VK_SPACE) & 0x1) {
			bool IsJumping = *reinterpret_cast<bool*>(__int64(GAI) + __int64(Offsets::FortAnimInstance::bIsJumping));
			if (IsJumping == false) {
				ProcessEventOG(GPawn, JumpFunc, nullptr);
			}
		}
		if (AISpawned == false && GetAsyncKeyState(VK_F3) & 0x1) {
			AISpawned = true;
			auto HuskTest = new HuskAI();
			HuskTest->InitHusk();
		}
		*reinterpret_cast<uint8_t*>(__int64(GPawn) + __int64(CMS_Offset)) = (*reinterpret_cast<bool*>(__int64(GPC) + __int64(WTS_Offset)) == false) ? (uint8_t)EFortMovementStyle::Sprinting : (uint8_t)EFortMovementStyle::Walking;
	}

	return ProcessEventOG(Object, Function, Params);
}