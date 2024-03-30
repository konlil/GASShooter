#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"

namespace MyCooker
{
	template<typename TStructType>
	static bool TDeserializeJsonObjectAsStruct(const TSharedPtr<FJsonObject>& OutJsonObject,TStructType& InStruct)
	{
		SCOPED_NAMED_EVENT_TEXT("TDeserializeJsonObjectAsStruct",FColor::Red);
		bool bStatus = false;
		if(OutJsonObject.IsValid())
		{
			bStatus = FJsonObjectConverter::JsonObjectToUStruct(OutJsonObject.ToSharedRef(),TStructType::StaticStruct(),&InStruct,0,0);
		}
		return bStatus;
	}
	
	template<typename TStructType>
	static bool TDeserializeJsonStringAsStruct(const FString& InJsonString,TStructType& OutStruct)
	{
		bool bRunStatus = false;
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(InJsonString);
		TSharedPtr<FJsonObject> DeserializeJsonObject;
		if (FJsonSerializer::Deserialize(JsonReader, DeserializeJsonObject))
		{
			bRunStatus = MyCooker::TDeserializeJsonObjectAsStruct<TStructType>(DeserializeJsonObject,OutStruct);
		}
		return bRunStatus;
	}

	static bool CookPackage(UPackage* Package, const TArray<FString>& Platforms, const FString& SavePath);
	static FString GetCookAssetsSaveDir(const FString& BaseDir, UPackage* Package, const FString& Platform);
	static FString ConvertToFullSandboxPath(const FString& FileName, bool bForWrite);
	
}

