#include "MyCookerEditor.h"


void FMyCookerEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Warning, TEXT("MyCookerEditorModule: Log Started"));
}



void FMyCookerEditorModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyCookerEditorModule, MyCookerEditor)