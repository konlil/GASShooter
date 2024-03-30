// Copyright 2019 Lipeng Zha, Inc. All Rights Reserved.

#pragma once

// engine header
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyCookerEditor,All,All)


class MYCOOKEREDITOR_API FMyCookerEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
