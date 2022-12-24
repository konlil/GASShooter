@echo off

set UE4_ENGINE_PATH=E:\Work\UE4_RG
set PROJECT_PATH=E:\Work\GASShooter
set PAK_OUTPUT_PATH=%PROJECT_PATH%\PakOutput

%UE4_ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PROJECT_PATH%\GASShooter.uproject" ^
    -nop4 -cook -SkipCook -compressed -fileopenorder -platform=Win64 -clientconfig=Development ^
    -iterate -nocompileeditor -build -installed -stage -CookOutputDir="%PAK_OUTPUT_PATH%\Client\WindowsNoEditor" ^
    -Pak -SkipPak ^
    -Archive -ArchiveDirectory="%PAK_OUTPUT_PATH%\Client"
    
pause
