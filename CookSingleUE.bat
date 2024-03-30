@echo off

REM set UE4_ENGINE_PATH=D:\Work\UE4_RG
REM set PROJECT_PATH=D:\Github\GASShooter

	
REM %UE4_ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PROJECT_PATH%\GASShooter.uproject" ^
    REM -nop4 -cook -compressed -fileopenorder ^
    REM -skippak -skipstage -utf8output ^
    REM -build -platform=Win64 -clientconfig=Development ^
	REM -AdditionalCookerOptions="-cooksinglepackage" -map=/Game/FPWeapon/Materials/MI_FPGun -unversionedcookedcontent
	
	
set UE4_ENGINE_PATH="C:\Program Files\Epic Games\UE_4.27\"
set PROJECT_PATH=D:\Github\GASShooter
set PAK_OUTPUT_PATH=D:\Github\GASShooter\PakOutput

%UE4_ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PROJECT_PATH%\GASShooter.uproject" ^
    -nop4 -cook -compressed -fileopenorder -platform=Win64 -clientconfig=Development ^
    -build -installed -skippak -skipstage ^
	-AdditionalCookerOptions="-cooksinglepackagenorefs" -map=/Game/top_cover.top_cover -unversionedcookedcontent
    

pause
