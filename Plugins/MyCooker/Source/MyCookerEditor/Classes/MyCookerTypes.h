#pragma once
#include "CoreMinimal.h"
#include "MyCookerTypes.generated.h"

// USTRUCT(BlueprintType)
// struct FMyAssetDetail
// {
// 	GENERATED_BODY()
//
// 	FMyAssetDetail() = default;
// 	FMyAssetDetail(const FMyAssetDetail&) = default;
// 	FMyAssetDetail& operator=(const FMyAssetDetail&) = default;
// 	FORCEINLINE FMyAssetDetail(const FName& InAssetPackagePath, const FName& InAsetType, const FName& InGuid)
// 		: PackagePath(InAssetPackagePath), AssetType(InAsetType), Guid(InGuid){}
// 	FORCEINLINE FMyAssetDetail(const FString& InAssetPackagePath, const FString& InAsetType,const FString& InGuid)
// 		: FMyAssetDetail(FName(*InAssetPackagePath),FName(*InAsetType),FName(*InGuid)){}
//
// 	bool operator==(const FMyAssetDetail& InRight)const
// 	{
// 		const bool bSamePackageName = (PackagePath == InRight.PackagePath);
// 		const bool bSameAssetType = (AssetType == InRight.AssetType);
// 		const bool bSameGUID = (Guid == InRight.Guid);
//
// 		return bSamePackageName && bSameAssetType && bSameGUID;
// 	}
// 	FORCEINLINE bool IsValid()const
// 	{
// 		return !PackagePath.IsNone() && !AssetType.IsNone() && !Guid.IsNone();
// 	}
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FName PackagePath;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FName AssetType;
// 	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FName Guid;
// 	
// };

USTRUCT(BlueprintType)
struct MYCOOKEREDITOR_API FMySingleCookerSettings
{
	GENERATED_USTRUCT_BODY()

	FMySingleCookerSettings(){};

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "MyCooker")
	TArray<FString> CookAssets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCooker")
	TArray<FString> CookTargetPlatforms;
};