#include "MyCookerStatics.h"

#include "Editor.h"
#include "Interfaces/IPluginManager.h"

namespace MyCooker{

static FString ConvertToFullSandboxPath(const FString& FileName, bool bForWrite)
{
	FString ProjectContentAbsir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	if (FileName.StartsWith(ProjectContentAbsir))
	{
		FString GameFileName = FileName;
		GameFileName.RemoveFromStart(ProjectContentAbsir);
		return FPaths::Combine(FApp::GetProjectName(), TEXT("Content"), GameFileName);
	}
	if (FileName.StartsWith(FPaths::EngineContentDir()))
	{
		FString EngineFileName = FileName;
		EngineFileName.RemoveFromStart(FPaths::EngineContentDir());
		return FPaths::Combine(TEXT("Engine/Content"), EngineFileName);;
	}
	TArray<TSharedRef<IPlugin> > PluginsToRemap = IPluginManager::Get().GetEnabledPlugins();
	// Ideally this would be in the Sandbox File but it can't access the project or plugin
	if (PluginsToRemap.Num() > 0)
	{
		// Handle remapping of plugins
		for (TSharedRef<IPlugin> Plugin : PluginsToRemap)
		{
			FString PluginContentDir;
			if (FPaths::IsRelative(FileName))
				PluginContentDir = Plugin->GetContentDir();
			else
				PluginContentDir = FPaths::ConvertRelativePathToFull(Plugin->GetContentDir());
			// UE_LOG(LogHotPatcherEditorHelper,Log,TEXT("Plugin Content:%s"),*PluginContentDir);
			if (FileName.StartsWith(PluginContentDir))
			{
				FString SearchFor;
				SearchFor /= Plugin->GetName() / TEXT("Content");
				int32 FoundAt = FileName.Find(SearchFor, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
				check(FoundAt != -1);
				// Strip off everything but <PluginName/Content/<remaing path to file>
				FString SnippedOffPath = FileName.RightChop(FoundAt);

				FString LoadingFrom;
				switch (Plugin->GetLoadedFrom())
				{
				case EPluginLoadedFrom::Engine:
				{
					LoadingFrom = TEXT("Engine/Plugins");
					break;
				}
				case EPluginLoadedFrom::Project:
				{
					LoadingFrom = FPaths::Combine(FApp::GetProjectName(), TEXT("Plugins"));
					break;
				}
				}

				return FPaths::Combine(LoadingFrom, SnippedOffPath);
			}
		}
	}

	return TEXT("");
}

static FString GetCookAssetsSaveDir(const FString& BaseDir, UPackage* Package, const FString& Platform)
{
	FString Filename;
	FString PackageFilename;
	FString StandardFilename;
	//Content folder
	if (FPackageName::DoesPackageExist(Package->FileName.ToString(), NULL, &Filename, false))
	{
		StandardFilename = PackageFilename = FPaths::ConvertRelativePathToFull(Filename);
		FPaths::MakeStandardFilename(StandardFilename);
	}
	//MakeSure Engine or Project or Plugin Contents
	FString SandboxFilename = MyCooker::ConvertToFullSandboxPath(StandardFilename, true);

	FString CookDir = FPaths::Combine(BaseDir, Platform, SandboxFilename);

	return 	CookDir;
}


static bool CookPackage(UPackage* Package, const TArray<FString>& Platforms, const FString& SavePath)
{
	bool bSuccessed = false;
	const bool bSaveConcurrent = FParse::Param(FCommandLine::Get(), TEXT("ConcurrentSave"));
	bool bUnversioned = false;
	uint32 SaveFlags = SAVE_KeepGUID | SAVE_Async | SAVE_ComputeHash | (bUnversioned ? SAVE_Unversioned : 0);
	EObjectFlags CookedFlags = RF_Public;
	if (Cast<UWorld>(Package))
	{
		CookedFlags = RF_NoFlags;
	}
	if (bSaveConcurrent)
	{
		SaveFlags |= SAVE_Concurrent;
	}
	ITargetPlatformManagerModule& TPM = GetTargetPlatformManagerRef();
	const TArray<ITargetPlatform*>& TargetPlatforms = TPM.GetTargetPlatforms();
	TArray<ITargetPlatform*> CookPlatforms;
	for (ITargetPlatform* TargetPlatform : TargetPlatforms)
	{
		if (Platforms.Contains(TargetPlatform->PlatformName()))
		{
			CookPlatforms.AddUnique(TargetPlatform);
		}
	}
	if (Package->FileName.IsNone())
		return bSuccessed;
	for (auto& Platform : CookPlatforms)
	{
		struct FFilterEditorOnlyFlag
		{
			FFilterEditorOnlyFlag(UPackage* InPackage, ITargetPlatform* InPlatform)
			{
				Package = InPackage;
				Platform = InPlatform;
				if (!Platform->HasEditorOnlyData())
				{
					Package->SetPackageFlags(PKG_FilterEditorOnly);
				}
				else
				{
					Package->ClearPackageFlags(PKG_FilterEditorOnly);
				}
			}
			~FFilterEditorOnlyFlag()
			{
				if (!Platform->HasEditorOnlyData())
				{
					Package->ClearPackageFlags(PKG_FilterEditorOnly);
				}
			}
			UPackage* Package;
			ITargetPlatform* Platform;
		};

		FFilterEditorOnlyFlag SetPackageEditorOnlyFlag(Package, Platform);

		FString CookedSavePath = MyCooker::GetCookAssetsSaveDir(SavePath, Package, Platform->PlatformName());
		// delete old cooked assets
		if (FPaths::FileExists(CookedSavePath))
		{
			IFileManager::Get().Delete(*CookedSavePath);
		}
		// UE_LOG(LogHotPatcherEditorHelper,Log,TEXT("Cook Assets:%s"),*Package->GetName());
		Package->FullyLoad();
		TArray<UObject*> ExportMap;
		GetObjectsWithOuter(Package, ExportMap);
		for (const auto& ExportObj : ExportMap)
		{
			ExportObj->BeginCacheForCookedPlatformData(Platform);
		}


		GIsCookerLoadingPackage = true;
		//UE_LOG(LogTemp, Warning, TEXT("Cook Assets:%s save to %s"), *Package->GetName(), *CookedSavePath);
		FSavePackageResultStruct Result = GEditor->Save(Package, nullptr, CookedFlags, *CookedSavePath,
			GError, nullptr, false, false, SaveFlags, Platform,
			FDateTime::MinValue(), false, /*DiffMap*/ nullptr);
		GIsCookerLoadingPackage = false;
		bSuccessed = Result == ESavePackageResult::Success;
	}
	return bSuccessed;
}




//void CreateSaveFileNotify(const FText& InMsg, const FString& InSavedFile, SNotificationItem::ECompletionState NotifyType)
//{
	// auto Message = InMsg;
	// FNotificationInfo Info(Message);
	// Info.bFireAndForget = true;
	// Info.ExpireDuration = 5.0f;
	// Info.bUseSuccessFailIcons = false;
	// Info.bUseLargeFont = false;
	//
	// const FString HyperLinkText = InSavedFile;
	// Info.Hyperlink = FSimpleDelegate::CreateLambda(
	// 	[](FString SourceFilePath)
	// 	{
	// 		FPlatformProcess::ExploreFolder(*SourceFilePath);
	// 	},
	// 	HyperLinkText
	// 		);
	// Info.HyperlinkText = FText::FromString(HyperLinkText);
	//
	// FSlateNotificationManager::Get().AddNotification(Info)->SetCompletionState(NotifyType);
//}

}	