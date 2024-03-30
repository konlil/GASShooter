#pragma once

#include "Commandlets/Commandlet.h"
#include "MyCookerTypes.h"
#include "MySingleCookerCommandlet.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMySingleCookerCommandlet, All, All);

static const bool bNoDDC = FParse::Param(FCommandLine::Get(), TEXT("NoDDC"));




UCLASS()
class UMySingleCookerCommandlet :public UCommandlet
{
	GENERATED_BODY()

public:
	virtual int32 Main(const FString& Params)override;
	virtual bool IsSkipObject(UObject* Object){ return false; }
	virtual bool IsSkipPackage(UPackage* Package){ return false; }

protected:
	//void Update(const FString& Params);
	//void MaybeMarkPackageAsAlreadyLoaded(UPackage* Package);
	FString CmdConfigPath;

	TSharedPtr<FMySingleCookerSettings> SingleCookerSetting;
};