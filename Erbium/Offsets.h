#pragma once
#include <Windows.h>
namespace Offsets {
	namespace World {
		uintptr_t AuthorityGameMode = 0;
		uintptr_t GameState = 0;
		uintptr_t PersistentLevel = 0;
		uintptr_t OwningGameInstance = 0;
	}
	namespace GameInstance {
		uintptr_t LocalPlayers = 0; 
	}
	namespace Player {
		uintptr_t PlayerController = 0;
	}
	namespace PlayerController {
		uintptr_t WorldInventory = 0;
	}
	namespace FortInventory {
		uintptr_t Inventory = 0;
	}
	namespace ItemsList {
		uintptr_t ReplicatedEntries = 0;
		uintptr_t ItemIntstances = 0;
	}
	namespace FortAnimInstance {
		uintptr_t bIsJumping = 0;
	}
}

#define V1_ItemEntrySize 0xA8
#define V3_ItemEntrySize 0xC0
#define V4_5_6_ItemEntrySize 0xD0
#define V7_8_9_X_ItemEntrySize 0x120