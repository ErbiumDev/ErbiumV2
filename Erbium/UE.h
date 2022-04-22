#include <Windows.h>
#include <string>
#include <locale>
#include <vector>
#include "Offsets.h"
float GVersion = 0.0f;
bool IsC1;
#define UE4_20
bool UsedThanos = false;
bool IsTUT = false;

enum class EFortMovementStyle : uint8_t
{
	Running = 0,
	Walking = 1,
	Charging = 2,
	Sprinting = 3,
	PersonalVehicle = 4,
	Flying = 5,
	Tethered = 6,
	EFortMovementStyle_MAX = 7
};

enum class EFortCustomPartType : uint8_t
{
	Head = 0,
	Body = 1,
	Hat = 2,
	Backpack = 3,
	Charm = 4,
	Face = 5,
	NumTypes = 6,
	EFortCustomPartType_MAX = 7
};

enum EPropertyFlags : uint64_t
{
	CPF_None = 0,
	CPF_Edit = 0x0000000000000001,
	///< Property is user-settable in the editor.
	CPF_ConstParm = 0x0000000000000002,
	///< This is a constant function parameter
	CPF_BlueprintVisible = 0x0000000000000004,
	///< This property can be read by blueprint code
	CPF_ExportObject = 0x0000000000000008,
	///< Object can be exported with actor.
	CPF_BlueprintReadOnly = 0x0000000000000010,
	///< This property cannot be modified by blueprint code
	CPF_Net = 0x0000000000000020,
	///< Property is relevant to network replication.
	CPF_EditFixedSize = 0x0000000000000040,
	///< Indicates that elements of an array can be modified, but its size cannot be changed.
	CPF_Parm = 0x0000000000000080,
	///< Function/When call parameter.
	CPF_OutParm = 0x0000000000000100,
	///< Value is copied out after function call.
	CPF_ZeroConstructor = 0x0000000000000200,
	///< memset is fine for construction
	CPF_ReturnParm = 0x0000000000000400,
	///< Return value.
	CPF_DisableEditOnTemplate = 0x0000000000000800,
	///< Disable editing of this property on an archetype/sub-blueprint
	//CPF_      						= 0x0000000000001000,	///< 
	CPF_Transient = 0x0000000000002000,
	///< Property is transient: shouldn't be saved or loaded, except for Blueprint CDOs.
	CPF_Config = 0x0000000000004000,
	///< Property should be loaded/saved as permanent profile.
	//CPF_								= 0x0000000000008000,	///< 
	CPF_DisableEditOnInstance = 0x0000000000010000,
	///< Disable editing on an instance of this class
	CPF_EditConst = 0x0000000000020000,
	///< Property is uneditable in the editor.
	CPF_GlobalConfig = 0x0000000000040000,
	///< Load config from base class, not subclass.
	CPF_InstancedReference = 0x0000000000080000,
	///< Property is a component references.
	//CPF_								= 0x0000000000100000,	///<
	CPF_DuplicateTransient = 0x0000000000200000,
	///< Property should always be reset to the default value during any type of duplication (copy/paste, binary duplication, etc.)
	//CPF_								= 0x0000000000400000,	///< 
	//CPF_    							= 0x0000000000800000,	///< 
	CPF_SaveGame = 0x0000000001000000,
	///< Property should be serialized for save games, this is only checked for game-specific archives with ArIsSaveGame
	CPF_NoClear = 0x0000000002000000,
	///< Hide clear (and browse) button.
	//CPF_  							= 0x0000000004000000,	///<
	CPF_ReferenceParm = 0x0000000008000000,
	///< Value is passed by reference; CPF_OutParam and CPF_Param should also be set.
	CPF_BlueprintAssignable = 0x0000000010000000,
	///< MC Delegates only.  Property should be exposed for assigning in blueprint code
	CPF_Deprecated = 0x0000000020000000,
	///< Property is deprecated.  Read it from an archive, but don't save it.
	CPF_IsPlainOldData = 0x0000000040000000,
	///< If this is set, then the property can be memcopied instead of CopyCompleteValue / CopySingleValue
	CPF_RepSkip = 0x0000000080000000,
	///< Not replicated. For non replicated properties in replicated structs 
	CPF_RepNotify = 0x0000000100000000,
	///< Notify actors when a property is replicated
	CPF_Interp = 0x0000000200000000,
	///< interpolatable property for use with matinee
	CPF_NonTransactional = 0x0000000400000000,
	///< Property isn't transacted
	CPF_EditorOnly = 0x0000000800000000,
	///< Property should only be loaded in the editor
	CPF_NoDestructor = 0x0000001000000000,
	///< No destructor
	//CPF_								= 0x0000002000000000,	///<
	CPF_AutoWeak = 0x0000004000000000,
	///< Only used for weak pointers, means the export type is autoweak
	CPF_ContainsInstancedReference = 0x0000008000000000,
	///< Property contains component references.
	CPF_AssetRegistrySearchable = 0x0000010000000000,
	///< asset instances will add properties with this flag to the asset registry automatically
	CPF_SimpleDisplay = 0x0000020000000000,
	///< The property is visible by default in the editor details view
	CPF_AdvancedDisplay = 0x0000040000000000,
	///< The property is advanced and not visible by default in the editor details view
	CPF_Protected = 0x0000080000000000,
	///< property is protected from the perspective of script
	CPF_BlueprintCallable = 0x0000100000000000,
	///< MC Delegates only.  Property should be exposed for calling in blueprint code
	CPF_BlueprintAuthorityOnly = 0x0000200000000000,
	///< MC Delegates only.  This delegate accepts (only in blueprint) only events with BlueprintAuthorityOnly.
	CPF_TextExportTransient = 0x0000400000000000,
	///< Property shouldn't be exported to text format (e.g. copy/paste)
	CPF_NonPIEDuplicateTransient = 0x0000800000000000,
	///< Property should only be copied in PIE
	CPF_ExposeOnSpawn = 0x0001000000000000,
	///< Property is exposed on spawn
	CPF_PersistentInstance = 0x0002000000000000,
	///< A object referenced by the property is duplicated like a component. (Each actor should have an own instance.)
	CPF_UObjectWrapper = 0x0004000000000000,
	///< Property was parsed as a wrapper class like TSubclassOf<T>, FScriptInterface etc., rather than a USomething*
	CPF_HasGetValueTypeHash = 0x0008000000000000,
	///< This property can generate a meaningful hash value.
	CPF_NativeAccessSpecifierPublic = 0x0010000000000000,
	///< Public native access specifier
	CPF_NativeAccessSpecifierProtected = 0x0020000000000000,
	///< Protected native access specifier
	CPF_NativeAccessSpecifierPrivate = 0x0040000000000000,
	///< Private native access specifier
	CPF_SkipSerialization = 0x0080000000000000,
	///< Property shouldn't be serialized, can still be exported to text
};

enum class EVectorQuantization : uint8_t
{
	RoundWholeNumber = 0,
	RoundOneDecimal = 1,
	RoundTwoDecimals = 2,
	EVectorQuantization_MAX = 3
};

enum class ERotatorQuantization : uint8_t
{
	ByteComponents = 0,
	ShortComponents = 1,
	ERotatorQuantization_MAX = 2
};

enum class ESpawnActorCollisionHandlingMethod : uint8_t
{
	Undefined = 0,
	AlwaysSpawn = 1,
	AdjustIfPossibleButAlwaysSpawn = 2,
	AdjustIfPossibleButDontSpawnIfColliding = 3,
	DontSpawnIfColliding = 4,
	ESpawnActorCollisionHandlingMethod_MAX = 5
};

enum class ENetDormancy : uint8_t
{
	DORM_Never = 0,
	DORM_Awake = 1,
	DORM_DormantAll = 2,
	DORM_DormantPartial = 3,
	DORM_Initial = 4,
	DORM_MAX = 5
};

enum class EAutoReceiveInput : uint8_t
{
	Disabled = 0,
	Player0 = 1,
	Player1 = 2,
	Player2 = 3,
	Player3 = 4,
	Player4 = 5,
	Player5 = 6,
	Player6 = 7,
	Player7 = 8,
	EAutoReceiveInput_MAX = 9
};

enum class ENetRole : uint8_t
{
	ROLE_None = 0,
	ROLE_SimulatedProxy = 1,
	ROLE_AutonomousProxy = 2,
	ROLE_Authority = 3,
	ROLE_MAX = 4
};

enum class ETickingGroup : uint8_t
{
	TG_PrePhysics = 0,
	TG_StartPhysics = 1,
	TG_DuringPhysics = 2,
	TG_EndPhysics = 3,
	TG_PostPhysics = 4,
	TG_PostUpdateWork = 5,
	TG_LastDemotable = 6,
	TG_NewlySpawned = 7,
	TG_MAX = 8
};

enum class EFortCustomBodyType : uint8_t
{
	NONE = 0,
	Small = 1,
	Medium = 2,
	MediumAndSmall = 3,
	Large = 4,
	LargeAndSmall = 5,
	LargeAndMedium = 6,
	All = 7,
	Deprecated = 8,
	EFortCustomBodyType_MAX = 9
};

enum class EFortCustomGender : uint8_t
{
	Invalid = 0,
	Male = 1,
	Female = 2,
	Both = 3,
	EFortCustomGender_MAX = 4
};

enum class EMontagePlayReturnType : uint8_t
{
	MontageLength = 0,
	Duration = 1,
	EMontagePlayReturnType_MAX = 2
};

enum EObjectFlags
{
	RF_NoFlags = 0x00000000,
	RF_Public = 0x00000001,
	RF_Standalone = 0x00000002,
	RF_MarkAsNative = 0x00000004,
	RF_Transactional = 0x00000008,
	RF_ClassDefaultObject = 0x00000010,
	RF_ArchetypeObject = 0x00000020,
	RF_Transient = 0x00000040,
	RF_MarkAsRootSet = 0x00000080,
	RF_TagGarbageTemp = 0x00000100,
	RF_NeedInitialization = 0x00000200,
	RF_NeedLoad = 0x00000400,
	RF_KeepForCooker = 0x00000800,
	RF_NeedPostLoad = 0x00001000,
	RF_NeedPostLoadSubobjects = 0x00002000,
	RF_NewerVersionExists = 0x00004000,
	RF_BeginDestroyed = 0x00008000,
	RF_FinishDestroyed = 0x00010000,
	RF_BeingRegenerated = 0x00020000,
	RF_DefaultSubObject = 0x00040000,
	RF_WasLoaded = 0x00080000,
	RF_TextExportTransient = 0x00100000,
	RF_LoadCompleted = 0x00200000,
	RF_InheritableComponentTemplate = 0x00400000,
	RF_DuplicateTransient = 0x00800000,
	RF_StrongRefOnFrame = 0x01000000,
	RF_NonPIEDuplicateTransient = 0x02000000,
	RF_Dynamic = 0x04000000,
	RF_WillBeLoaded = 0x08000000,
};

enum ELifetimeCondition
{
	COND_None = 0,
	COND_InitialOnly = 1,
	COND_OwnerOnly = 2,
	COND_SkipOwner = 3,
	COND_SimulatedOnly = 4,
	COND_AutonomousOnly = 5,
	COND_SimulatedOrPhysics = 6,
	COND_InitialOrOwner = 7,
	COND_Custom = 8,
	COND_ReplayOrOwner = 9,
	COND_ReplayOnly = 10,
	COND_SimulatedOnlyNoReplay = 11,
	COND_SimulatedOrPhysicsNoReplay = 12,
	COND_SkipReplay = 13,
	COND_Never = 15,
	COND_Max = 16,
};

enum class EFortQuickBars : uint8_t
{
	Primary,
	Secondary,
	Max_None,
	EFortQuickBars_MAX
};

enum class EAthenaGamePhase
{
	None = 0,
	Setup = 1,
	Warmup = 2,
	Aircraft = 3,
	SafeZones = 4,
	EndGame = 5,
	Count = 6,
	EAthenaGamePhase_MAX = 7
};

enum class EGameplayEffectDurationType : uint8_t
{
	Instant, Infinite, HasDuration, EGameplayEffectDurationType_MAX
};


struct FGuid
{
	int A;
	int B;
	int C;
	int D;
};
template<class T>
struct TArray
{
	friend class FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline T& operator[](int i) const
	{
		return Data[i];
	};

	inline BOOL IsValidIndex(int i) const
	{
		return i < Num();
	}

	inline void Add(T InputData)
	{
		Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
		Data[Count++] = InputData;
		Max = Count;
	};

	inline void Remove(int32_t Index)
	{
		TArray<T> NewArray;
		for (int i = 0; i < this->Count; i++)
		{
			if (i == Index)
				continue;

			NewArray.Add(this->operator[](i));
		}
		this->Data = (T*)realloc(NewArray.Data, sizeof(T) * (NewArray.Count));
		this->Count = NewArray.Count;
		this->Max = NewArray.Count;
	}

	T* Data;
	int Count;
	int Max;
};


struct FString : private TArray<wchar_t>
{
	FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? std::wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	}

	bool IsValid() const
	{
		return Data != nullptr;
	}

	const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

struct FName;

void(__fastcall* FNameToString)(FName* NameIn, FString& Out);
void(__fastcall* FnFree)(__int64);


struct FName
{
	uint32_t ComparisonIndex;
	uint32_t DisplayIndex;

	FName() = default;

	std::string ToString()
	{
		FString temp;
		FNameToString(this, temp);

		std::string ret(temp.ToString());
		FnFree((__int64)temp.c_str());

		return ret;
	}
};

bool IsBadReadPtr(void* p)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQuery(p, &mbi, sizeof(mbi)))
	{
		DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		bool b = !(mbi.Protect & mask);
		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

		return b;
	}
	return true;
}

void* (__fastcall* ProcessEventOG)(void* Object, void* Function, void* Params);

struct UObject
{
	void** VTable;
	int32_t ObjectFlags;
	int32_t InternalIndex;
	UObject* Class;
	FName Name;
	UObject* Outer;

	bool IsA(UObject* cmp) const
	{
		if (cmp == Class)
			return false;
		return false;
	}

	bool IsValid() {
		return !IsBadReadPtr(this);
	}

	void* ProcessEvent(UObject* Function, void* Params = nullptr) {
		return ProcessEventOG(this, Function, Params);
	}

	std::string GetName()
	{
		return Name.ToString();
	}

	std::string GetFullName()
	{
		std::string temp;

		for (auto outer = Outer; outer; outer = outer->Outer)
		{
			temp = outer->GetName() + "." + temp;
		}

		temp = reinterpret_cast<UObject*>(Class)->GetName() + " " + temp + this->GetName();

		return temp;
	}
};

struct UObjectItem
{
	UObject* Object;
	DWORD Flags;
	DWORD ClusterIndex;
	DWORD SerialNumber;
	//DWORD SerialNumber2;
};

struct PreUObjectItem
{
	UObjectItem* FUObject[10];
};

class UObjectArray {
public:
	inline int Num() const
	{
		return NumElements;
	}

	inline UObject* GetByIndex(int32_t index) const
	{
		return Objects[index].Object;
	}

	inline UObjectItem* GetItemByIndex(int32_t index) const
	{
		if (index < NumElements)
		{
			return &Objects[index];
		}
		return nullptr;
	}

private:
	UObjectItem* Objects;
	int MaxElements;
	int NumElements;
};

class OAP {
public:
	int32_t ObjFirstGCIndex;
	int32_t ObjLastNonGCIndex;
	int32_t MaxObjectsNotConsideredByGC;
	int32_t OpenForDisregardForGC;
	UObjectArray Objects;
};

class NewUObjectArray {
public:
	UObjectItem* Objects[9];
};

struct GObjects
{
	NewUObjectArray* ObjectArray;
	BYTE _padding_0[0xC];
	uint32_t NumElements;

	inline void NumChunks(int* start, int* end) const
	{
		int cStart = 0, cEnd = 0;

		if (!cEnd)
		{
			while (1)
			{
				if (ObjectArray->Objects[cStart] == 0)
				{
					cStart++;
				}
				else
				{
					break;
				}
			}

			cEnd = cStart;
			while (1)
			{
				if (ObjectArray->Objects[cEnd] == 0)
				{
					break;
				}
				else
				{
					cEnd++;
				}
			}
		}

		*start = cStart;
		*end = cEnd;
	}

	inline int32_t Num() const
	{
		return NumElements;
	}

	inline UObject* GetItemByIndex(int32_t index) const
	{
		int cStart = 0, cEnd = 0;
		int chunkIndex = 0, chunkSize = 0xFFFF, chunkPos;
		UObjectItem* Object;

		NumChunks(&cStart, &cEnd);

		chunkIndex = index / chunkSize;
		if (chunkSize * chunkIndex != 0 &&
			chunkSize * chunkIndex == index)
		{
			chunkIndex--;
		}

		chunkPos = cStart + chunkIndex;
		if (chunkPos < cEnd)
		{
#pragma warning( push )
#pragma warning( disable : 26451 )
			Object = ObjectArray->Objects[chunkPos] + (index - chunkSize * chunkIndex);
#pragma warning( pop )
			if (!Object) { return NULL; }

			return Object->Object;
		}

		return nullptr;
	}
};

UObjectArray* ObjObjects;
GObjects* GObjs;

template <class TEnum>
class TEnumAsByte
{
public:
	TEnumAsByte()
	{
	}

	TEnumAsByte(TEnum _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	operator TEnum() const
	{
		return static_cast<TEnum>(value);
	}

	TEnum GetValue() const
	{
		return static_cast<TEnum>(value);
	}

private:
	uint8_t value;
};

struct FField
{
	void* idk;
	void* Class;
	void* Owner;
	void* padding;
	FField* Next;
	FName Name;
	EObjectFlags FlagsPrivate;

	std::string GetName()
	{
		return Name.ToString();
	}

	std::string GetFullName()
	{
		std::string temp;

		for (auto outer = Next; outer; outer = outer->Next)
		{
			temp = outer->GetName() + "." + temp;
		}

		temp = static_cast<UObject*>(Class)->GetName() + " " + temp + this->GetName();
		return temp;
	}
};

struct FWeakObjectPtr
{
public:
	inline bool SerialNumbersMatch(UObjectItem* ObjectItem) const
	{
		return ObjectItem->SerialNumber == ObjectSerialNumber;
	}

	int32_t ObjectIndex;
	int32_t ObjectSerialNumber;
};

template<class T, class TWeakObjectPtrBase = FWeakObjectPtr>
struct TWeakObjectPtr : private TWeakObjectPtrBase
{
public:
	inline T* Get() const
	{
		return (T*)TWeakObjectPtrBase::Get();
	}

	inline T& operator*() const
	{
		return *Get();
	}

	inline T* operator->() const
	{
		return Get();
	}

	inline bool IsValid() const
	{
		return TWeakObjectPtrBase::IsValid();
	}
};

struct FText
{
	char UnknownData[0x18];
};

UObject* GPawn;

uintptr_t GetAddressFromOffset(DWORD Offset) {
	return reinterpret_cast<uintptr_t>(GetModuleHandle(NULL) + Offset);
}

uintptr_t FindPattern(const char* signature, bool bRelative = false, uint32_t offset = 0)
{
	uintptr_t base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
	static auto patternToByte = [](const char* pattern)
	{
		auto bytes = std::vector<int>{};
		const auto start = const_cast<char*>(pattern);
		const auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?') ++current;
				bytes.push_back(-1);
			}
			else { bytes.push_back(strtoul(current, &current, 16)); }
		}
		return bytes;
	};

	const auto dosHeader = (PIMAGE_DOS_HEADER)base_address;
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)base_address + dosHeader->e_lfanew);

	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = patternToByte(signature);
	const auto scanBytes = reinterpret_cast<std::uint8_t*>(base_address);

	const auto s = patternBytes.size();
	const auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i)
	{
		bool found = true;
		for (auto j = 0ul; j < s; ++j)
		{
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			uintptr_t address = reinterpret_cast<uintptr_t>(&scanBytes[i]);
			if (bRelative)
			{
				address = ((address + offset + 4) + *(int32_t*)(address + offset));
				return address;
			}
			return address;
		}
	}
	return NULL;
}

std::vector<std::pair<UObject*, std::string>> KnownObjs;
UObject* FindKnownObject(std::string FullName) {
	for (int i = 0; i < KnownObjs.size(); i++) {
		if (KnownObjs[i].second == FullName) {
			return KnownObjs[i].first;
		}
	}
	return nullptr;
}

template <typename T = UObject*> static T __fastcall FindObject(std::string ObjectToFind, bool IsEqual = false)
{
	UObject* Object = FindKnownObject(ObjectToFind);
	if (Object != nullptr) {
		return Object;
	}
	else {
		if (GVersion < 5.0f) {
			for (int i = 0; i < ObjObjects->Num(); i++)
			{
				Object = ObjObjects->GetItemByIndex(i)->Object;

				if (Object == nullptr)
				{
					continue;
				}

				if (IsEqual)
				{
					if (Object->GetFullName() == ObjectToFind)
					{
						KnownObjs.push_back(std::make_pair(Object, ObjectToFind));
						return (T)Object;
					}
				}
				else
				{
					if (Object->GetFullName().find(ObjectToFind) != std::string::npos)
					{
						KnownObjs.push_back(std::make_pair(Object, Object->GetFullName()));
						return (T)Object;
					}
				}
			}
		}
		else {
			for (int i = 0; i < GObjs->Num(); i++)
			{
				Object = GObjs->GetItemByIndex(i);

				if (Object == nullptr)
				{
					continue;
				}

				if (IsEqual == true)
				{
					if (Object->GetFullName() == ObjectToFind)
					{
						KnownObjs.push_back(std::make_pair(Object, ObjectToFind));
						return (T)Object;
					}
				}
				else
				{
					if (Object->GetFullName().find(ObjectToFind) != std::string::npos)
					{
						KnownObjs.push_back(std::make_pair(Object, Object->GetFullName()));
						return (T)Object;
					}
				}
			}
		}
	}

	return nullptr;
}

UObject** GWorldPtr;


inline DWORD FindOffset(const char* PropertyName)
{
	UObject* VariableObj = FindObject(PropertyName, true);
	if (VariableObj)
	{
		return *reinterpret_cast<uint32_t*>(__int64(VariableObj) + 0x44);
	}
	return NULL;
}

struct FVector {
	float X;
	float Y;
	float Z;

	FVector() {
		X = Y = Z = 0;
	}

	FVector(float NX, float NY, float NZ) {
		X = NX;
		Y = NY;
		Z = NZ;
	}
};

FVector GetDifference(FVector A, FVector B) {
	return FVector(A.X - B.X, A.Y - B.Y, A.Z - B.Z);
}

UObject* GPC;
UObject* GCM;
UObject* GAI;

struct FGameplayAbilitySpecDef
{
	UObject* Ability;
	unsigned char Unk00[0x90];
};

struct FActorSpawnParameters
{
	FActorSpawnParameters() : Name(), Template(nullptr), Owner(nullptr), Instigator(nullptr), OverrideLevel(nullptr), SpawnCollisionHandlingOverride(ESpawnActorCollisionHandlingMethod::AlwaysSpawn), bRemoteOwned(0), bNoFail(0),
		bDeferConstruction(0),
		bAllowDuringConstructionScript(0),
		NameMode(),
		ObjectFlags()
	{
	}
	;


	FName Name;

	UObject* Template;

	UObject* Owner;

	UObject* Instigator;

	UObject* OverrideLevel;

	ESpawnActorCollisionHandlingMethod SpawnCollisionHandlingOverride;

private:

	uint8_t bRemoteOwned : 1;

public:

	uint8_t bNoFail : 1;

	uint8_t bDeferConstruction : 1;

	uint8_t bAllowDuringConstructionScript : 1;


	enum class ESpawnActorNameMode : uint8_t
	{
		Required_Fatal,

		Required_ErrorAndReturnNull,

		Required_ReturnNull,

		Requested
	};


	ESpawnActorNameMode NameMode;

	EObjectFlags ObjectFlags;
};

UObject* (*StaticConstructObjectInternal)(void*, void*, void*, int, unsigned int, void*, bool, void*, bool);
UObject* (__fastcall*SpawnActor)(UObject* World, UObject* Class, FVector* Position, FVector* Rotation, const FActorSpawnParameters& SpawnParameters);
namespace Offsets {
	void InitOffsets() {
		World::AuthorityGameMode = FindOffset("ObjectProperty /Script/Engine.World.AuthorityGameMode");
		World::GameState = FindOffset("ObjectProperty /Script/Engine.World.GameState");
		World::PersistentLevel = FindOffset("ObjectProperty /Script/Engine.World.PersistentLevel");
		World::OwningGameInstance = FindOffset("ObjectProperty /Script/Engine.WorldContext.OwningGameInstance");
		GameInstance::LocalPlayers = FindOffset("ArrayProperty /Script/Engine.GameInstance.LocalPlayers");
		Player::PlayerController = FindOffset("ObjectProperty /Script/Engine.Player.PlayerController");
		PlayerController::WorldInventory = FindOffset("ObjectProperty /Script/FortniteGame.FortPlayerController.WorldInventory");
		FortInventory::Inventory = FindOffset("StructProperty /Script/FortniteGame.FortInventory.Inventory");
		ItemsList::ReplicatedEntries = FindOffset("ArrayProperty /Script/FortniteGame.FortItemList.ReplicatedEntries");
		ItemsList::ItemIntstances = FindOffset("ArrayProperty /Script/FortniteGame.FortItemList.ItemInstances");
		FortAnimInstance::bIsJumping = FindOffset("BoolProperty /Script/FortniteGame.FortAnimInstance.bIsJumping");
	}
}
std::string GetFortniteVersion()
{
	void* Result;
	auto Add = FindPattern(("40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 8B C8 41 B8 04 ? ? ? 48 8B D3"));
	if (FindPattern(Free_Old) != 0 && FindPattern(GObjects_G) == 0) { //Scuffed way to make 1.8 not crash
		return "1.8";
	}
	auto String = reinterpret_cast<FString * (__fastcall*)(void*)>(Add)(&Result)->ToString();
	return String.substr(34, 4);
}

namespace Inventory {
	UObject* GInventory = nullptr;
	UObject* GQuickBars;
	uintptr_t ItemEntryOffset = 0;
	UObject* CreateTemporaryItemInstanceBPFunc = nullptr;
	UObject* ServerAddItemInternalFunc = nullptr;
	UObject* SetOwningControllerForTemporaryItem = nullptr;
	UObject* GetItemGuid = nullptr;
	//Credit to Ultimanite For 99% of This
	void ServerAddItemInternal(UObject* Quickbars, FGuid Item, EFortQuickBars Quickbar, int Slot)
	{
		if (ServerAddItemInternalFunc == nullptr) {
			ServerAddItemInternalFunc = FindObject("Function /Script/FortniteGame.FortQuickBars.ServerAddItemInternal");
		}

		struct
		{
			FGuid Item;
			EFortQuickBars Quickbar;
			int Slot;
		} Params;

		Params.Item = Item;
		Params.Quickbar = Quickbar;
		Params.Slot = Slot;

		ProcessEventOG(Quickbars, ServerAddItemInternalFunc, &Params);
	}


	FGuid GetGuid(UObject* Target)
	{
		if (GetItemGuid == nullptr) {
			GetItemGuid = FindObject("Function /Script/FortniteGame.FortItem.GetItemGuid");
		}
		FGuid ReturnValue;

		ProcessEventOG(Target, GetItemGuid, &ReturnValue);

		return ReturnValue;
	}

	UObject* CreateTemporaryItemInstanceBP(UObject* ItemDefinition, int Count, int Level)
	{
		if (CreateTemporaryItemInstanceBPFunc == nullptr) {
			CreateTemporaryItemInstanceBPFunc = FindObject("Function /Script/FortniteGame.FortItemDefinition.CreateTemporaryItemInstanceBP");
		}
		struct
		{
			int Count;
			int Level;
			UObject* ReturnValue;
		} Params;

		Params.Count = Count;
		Params.Level = Level;

		ProcessEventOG(ItemDefinition, CreateTemporaryItemInstanceBPFunc, &Params);

		if (SetOwningControllerForTemporaryItem == nullptr) {
			SetOwningControllerForTemporaryItem = FindObject("Function /Script/FortniteGame.FortItem.SetOwningControllerForTemporaryItem");
		}

		ProcessEventOG(Params.ReturnValue, SetOwningControllerForTemporaryItem, &GPC);

		return Params.ReturnValue;
	}

	UObject* CreateItem(UObject* ItemDefinition, int Count)
	{
		UObject* TemporaryItemInstance = CreateTemporaryItemInstanceBP(ItemDefinition, Count, 1);

		int* CurrentCount = reinterpret_cast<int*>(__int64(TemporaryItemInstance) + static_cast<__int64>(ItemEntryOffset) + static_cast<__int64>(0xC));
		*CurrentCount = Count;

		return TemporaryItemInstance;
	}

	void UpdateInventory()
	{
		static UObject* HandleWorldInventoryLocalUpdate = FindObject("Function /Script/FortniteGame.FortPlayerController.HandleWorldInventoryLocalUpdate");
		static UObject* HandleInventoryLocalUpdate = FindObject("Function /Script/FortniteGame.FortInventory.HandleInventoryLocalUpdate");
		static UObject* OnRep_QuickBar = FindObject("Function /Script/FortniteGame.FortPlayerController.OnRep_QuickBar");
		static UObject* ClientForceUpdateQuickbar = FindObject("Function /Script/FortniteGame.FortPlayerController.ClientForceUpdateQuickbar");
		static UObject* OnRep_SecondaryQuickBar = FindObject("Function /Script/FortniteGame.FortQuickBars.OnRep_SecondaryQuickBar");
		static UObject* OnRep_PrimaryQuickBar = FindObject("Function /Script/FortniteGame.FortQuickBars.OnRep_PrimaryQuickBar");

		ProcessEventOG(GInventory, HandleInventoryLocalUpdate, nullptr);
		ProcessEventOG(GPC, HandleWorldInventoryLocalUpdate, nullptr);
		if (OnRep_QuickBar)
		{
			ProcessEventOG(GPC, OnRep_QuickBar, nullptr);
			ProcessEventOG(GQuickBars, OnRep_SecondaryQuickBar, nullptr);
			ProcessEventOG(GQuickBars, OnRep_PrimaryQuickBar, nullptr);
		}
		else
		{
			auto PrimaryQuickbar = EFortQuickBars::Primary;
			auto SecondaryQuickbar = EFortQuickBars::Secondary;
			ProcessEventOG(GPC, ClientForceUpdateQuickbar, &PrimaryQuickbar);
			ProcessEventOG(GPC, ClientForceUpdateQuickbar, &SecondaryQuickbar);
		}
	}

	void AddItemToInventory(UObject* ItemDef,int Count, int Slot, EFortQuickBars Index) {
		if (ItemDef->IsValid()) {
			ItemDef = CreateItem(ItemDef, Count);
			float FNVersion = GVersion;
			if (FNVersion < 2.0f) {
				struct ItemEntrySize
				{
					unsigned char Unk00[V1_ItemEntrySize];
				};
				auto ItemEntry = reinterpret_cast<ItemEntrySize*>(reinterpret_cast<uintptr_t>(ItemDef) + ItemEntryOffset);
				reinterpret_cast<TArray<ItemEntrySize>*>(__int64(GInventory) + static_cast<__int64>(Offsets::FortInventory::Inventory) + static_cast<__int64>(Offsets::ItemsList::ReplicatedEntries))->Add(*ItemEntry);
			}
			else if (FNVersion < 4.0f) {
				struct ItemEntrySize
				{
					unsigned char Unk00[V3_ItemEntrySize];
				};
				auto ItemEntry = reinterpret_cast<ItemEntrySize*>(reinterpret_cast<uintptr_t>(ItemDef) + ItemEntryOffset);
				reinterpret_cast<TArray<ItemEntrySize>*>(__int64(GInventory) + static_cast<__int64>(Offsets::FortInventory::Inventory) + static_cast<__int64>(Offsets::ItemsList::ReplicatedEntries))->Add(*ItemEntry);
			}
			else if (FNVersion < 7.0f) {
				struct ItemEntrySize
				{
					unsigned char Unk00[V4_5_6_ItemEntrySize];
				};
				auto ItemEntry = reinterpret_cast<ItemEntrySize*>(reinterpret_cast<uintptr_t>(ItemDef) + ItemEntryOffset);
				reinterpret_cast<TArray<ItemEntrySize>*>(__int64(GInventory) + static_cast<__int64>(Offsets::FortInventory::Inventory) + static_cast<__int64>(Offsets::ItemsList::ReplicatedEntries))->Add(*ItemEntry);
			}
			else if (FNVersion < 11.0f) {
				struct ItemEntrySize
				{
					unsigned char Unk00[V7_8_9_X_ItemEntrySize];
				};
				auto ItemEntry = reinterpret_cast<ItemEntrySize*>(reinterpret_cast<uintptr_t>(ItemDef) + ItemEntryOffset);
				reinterpret_cast<TArray<ItemEntrySize>*>(__int64(GInventory) + static_cast<__int64>(Offsets::FortInventory::Inventory) + static_cast<__int64>(Offsets::ItemsList::ReplicatedEntries))->Add(*ItemEntry);
			}
			reinterpret_cast<TArray<UObject*>*>(__int64(GInventory) + static_cast<__int64>(Offsets::FortInventory::Inventory) + static_cast<__int64>(Offsets::ItemsList::ItemIntstances))->Add(ItemDef);
			if (FNVersion < 7.4f) {
				ServerAddItemInternal(GQuickBars, GetGuid(ItemDef), Index, Slot);
			}
		}
	}

	//void AddItemToInventory(UObject* ItemDef, int Count, int Slot, EFortQuickBars Index) {
	//	/*struct
	//	{
	//		UObject* ItemDefinition;
	//		EFortQuickBars Quickbar;
	//		int Slot;
	//	} Params;
	//	ItemDef = CreateItem(ItemDef, Count);
	//	Params.ItemDefinition = ItemDef;
	//	Params.Quickbar = Index;
	//	Params.Slot = Slot;

	//	ProcessEventOG(GPC, FindObject("Function /Script/FortniteGame.FortPlayerController.AddItemToQuickBars"), &Params);*/
	//	ItemDef = CreateItem(ItemDef, Count);
	//	ServerAddItemInternal(GQuickBars, GetGuid(ItemDef), Index, Slot);
	//}

	bool CheckGUID(FGuid guidA, FGuid guidB) {
		if (guidA.A == guidB.A && guidA.B == guidB.B && guidA.C == guidB.C && guidA.D == guidB.D)
			return true;
		else
			return false;
	}

	void EquipItem(UObject* Item, FGuid GUID) {
		struct
		{
			UObject* ItemDefinition;
			FGuid ItemGuid;
			UObject* ReturnValue;
		} params;
		if (Item->GetFullName().find("AthenaGadget") != std::string::npos)
		{
			auto FUN_weapondef = FindObject(("Function /Script/FortniteGame.FortGadgetItemDefinition.GetWeaponItemDefinition"));

			UObject* prm_ReturnValue;

			ProcessEventOG(Item, FUN_weapondef, &prm_ReturnValue);

			if (prm_ReturnValue->IsValid())
			{
				Item = prm_ReturnValue;
			}
		}
		params.ItemDefinition = Item;
		params.ItemGuid = GUID;
		ProcessEventOG(GPawn, FindObject("Function /Script/FortniteGame.FortPawn.EquipWeaponDefinition"), &params);
	}

	void EquipInventoryItem(FGuid* GUID) {
		TArray<UObject*> ItemInstances = *reinterpret_cast<TArray<UObject*>*>(__int64(GInventory) + static_cast<__int64>(Offsets::FortInventory::Inventory) + static_cast<__int64>(Offsets::ItemsList::ItemIntstances));
		for (int i = 0; i < ItemInstances.Num(); i++) {
			auto ItemInstance = ItemInstances.operator[](i);
			FGuid ItemGUID;
			ProcessEventOG(ItemInstance, FindObject("Function /Script/FortniteGame.FortItem.GetItemGuid"), &ItemGUID);
			if (CheckGUID(ItemGUID, *GUID) == true) {
				UObject* ItemDef;
				ProcessEventOG(ItemInstance, FindObject("Function /Script/FortniteGame.FortItem.GetItemDefinitionBP"), &ItemDef);
				EquipItem(ItemDef, *GUID);
			}
		}
	}

	void SetOwner(UObject* TargetActor, UObject* NewOwner)
	{
		static UObject* SetOwner = FindObject(("Function /Script/Engine.Actor.SetOwner"));

		ProcessEventOG(TargetActor, SetOwner, &NewOwner);
	}

	void InitInventory() {
		*reinterpret_cast<int*>(__int64(GPC) + __int64(FindOffset("IntProperty /Script/FortniteGame.FortPlayerController.OverriddenBackpackSize"))) = 9999;
		struct Pointer {
			UObject* Object;
		};
		ItemEntryOffset = FindOffset("StructProperty /Script/FortniteGame.FortWorldItem.ItemEntry");
		GInventory = reinterpret_cast<Pointer*>(__int64(GPC) + __int64(Offsets::PlayerController::WorldInventory))->Object;
		DWORD QuickbarOffset = FindOffset("ObjectProperty /Script/FortniteGame.FortPlayerController.QuickBars");
		if (QuickbarOffset != 0)
		{
			GQuickBars = SpawnActor(*GWorldPtr, FindObject("Class /Script/FortniteGame.FortQuickBars"), new FVector{ -122398, -103873, 3962}, {}, FActorSpawnParameters());
			reinterpret_cast<Pointer*>(__int64(GPC) + __int64(QuickbarOffset))->Object = GQuickBars;
		}
		else
		{
			QuickbarOffset = FindOffset("ObjectProperty /Script/FortniteGame.FortPlayerController.ClientQuickBars");
			GQuickBars = reinterpret_cast<Pointer*>(__int64(GPC) + __int64(QuickbarOffset))->Object;
		}
		SetOwner(GQuickBars, GPC);
	}
}

inline EFortCustomGender GetGender() {
	struct
	{
		TEnumAsByte<EFortCustomGender> ReturnValue;
	} params;

	ProcessEventOG(GPawn, FindObject("Function /Script/FortniteGame.FortPlayerPawn.GetCharacterGender"), &params);

	return params.ReturnValue.GetValue();
}

inline EFortCustomBodyType GetBodyType() {
	struct
	{
		TEnumAsByte<EFortCustomBodyType> ReturnValue;
	} params;

	ProcessEventOG(GPawn, FindObject("Function /Script/FortniteGame.FortPlayerPawn.GetCharacterBodyType"), &params);

	return params.ReturnValue.GetValue();
}