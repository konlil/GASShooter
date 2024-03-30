#include "MySingleCookerCommandlet.h"
// engine header
#include "CoreMinimal.h"
#include "MyCookerStatics.h"
#include "MyCookerTypes.h"
#include "HAL/ExceptionHandling.h"
#include "Kismet/KismetTextLibrary.h"
#include "Misc/FileHelper.h"
#include "Misc/CommandLine.h"
#include "Misc/Paths.h"

DEFINE_LOG_CATEGORY(LogMySingleCookerCommandlet);

UPackage* GetPackageFromPath(const FString& PackagePath)
{
	if (PackagePath.IsEmpty())
	{
		return NULL;
	}

	UPackage* Package = FindPackage(NULL, *PackagePath);
	if (Package)
	{
		Package->FullyLoad();
	}
	else
	{
		Package = LoadPackage(NULL, *PackagePath, LOAD_None);
	}

	return Package;
}

#define PATCHER_CONFIG_PARAM_NAME TEXT("-config=")

int32 UMySingleCookerCommandlet::Main(const FString& Params)
{
	Super::Main(Params);
	SCOPED_NAMED_EVENT_TEXT("UMySingleCookerCommandlet::Main",FColor::Red);
	
	UE_LOG(LogMySingleCookerCommandlet, Display, TEXT("UMySingleCookerCommandlet::Main"));

	bool bStatus = FParse::Value(*Params, *FString(PATCHER_CONFIG_PARAM_NAME).ToLower(), CmdConfigPath);
	if (!bStatus)
	{
		UE_LOG(LogMySingleCookerCommandlet, Warning, TEXT("not -config=xxxx.json params."));
		return -1;
	}
	
	if(CmdConfigPath.IsEmpty())
	{
		return -1;
	}

	SingleCookerSetting = MakeShareable(new FMySingleCookerSettings);
	
	FString JsonContent;
	if (FPaths::FileExists(CmdConfigPath) && FFileHelper::LoadFileToString(JsonContent, *CmdConfigPath))
	{
		MyCooker::TDeserializeJsonStringAsStruct(JsonContent,*SingleCookerSetting);
	}
	
	UE_LOG(LogMySingleCookerCommandlet, Display, TEXT("===MyCooker starts with assets Num %d"), SingleCookerSetting->CookAssets.Num());

	GAlwaysReportCrash = false;

	TArray<UPackage*> AssetsPackage;
	for (const auto& PackagePath : SingleCookerSetting->CookAssets)
	{
		UPackage* AssetPackage = GetPackageFromPath(PackagePath);
		AssetsPackage.AddUnique(AssetPackage);
	}

	bool bExportStatus = true;
	
	const auto& Platforms = SingleCookerSetting->CookTargetPlatforms;
	for (auto CurrentPlatform : Platforms)
	{
		//Create folder and Cook assets
		FString CookedDir = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Cooked")));
		for (const auto& AssetPacakge : AssetsPackage)
		{
			FString CookedSavePath = MyCooker::GetCookAssetsSaveDir(CookedDir, AssetPacakge, CurrentPlatform);

			//Start Cook Assets
			bool bCookStatus = MyCooker::CookPackage(AssetPacakge, Platforms, CookedDir);
			
			//CreateSaveFileNotify(Msg, CookedSavePath, CookStatus);
			UE_LOG(LogTemp, Warning, TEXT("Cook Single Assets, %s"), bCookStatus?TEXT("True"):TEXT("False"));

			bExportStatus = bExportStatus && bCookStatus;
		}
	}
	
	
	// CommandletHelper::MainTick([SingleCookerProxy]()->bool
	// {
	// 	return SingleCookerProxy->IsFinsihed();
	// });
	
	UE_LOG(LogMySingleCookerCommandlet,Display,TEXT("===MyCooker %s!"),bExportStatus?TEXT("Successed"):TEXT("Failure"));
	
	if(FParse::Param(FCommandLine::Get(), TEXT("wait")))
	{
		system("pause");
	}
	
	return bExportStatus ? 0 : -1;
}