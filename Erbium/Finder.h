#pragma once
#include "UE.h"
namespace Finder {
	struct UField_Old : UObject
	{
		UField_Old* Next;
		/*void* padding_01;
		void* padding_02;*/
	};

	struct UField_New : UObject
	{
		UField_New* Next;
		void* padding_01;
		void* padding_02;
	};

	struct UStruct_Old : UField_Old
	{
		struct StructBOI* Super;
		UField_Old* Children;
		uint32_t Size;
		char pad[0x44];
	};

	struct UStruct_New : UField_New
	{
		struct StructBOI* Super;
		UField_New* Children;
		uint32_t Size;
		char pad[0x44];
	};

	int32_t GetPropertySize(UObject* Struct) {
		if (GVersion < 5.0f) {//Idk if thats the right version lmao
			UStruct_Old* TStruct = reinterpret_cast<UStruct_Old*>(Struct);
			return TStruct->Size;
		}
		else {
			UStruct_New* TStruct = reinterpret_cast<UStruct_New*>(Struct);
			return TStruct->Size;
		}
	}
}