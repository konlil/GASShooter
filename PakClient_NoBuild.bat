@echo off

set UE4_ENGINE_PATH=E:\Work\UE4_RG
set PROJECT_PATH=E:\Work\GASShooter
set PAK_OUTPUT_PATH=%PROJECT_PATH%\PakOutput

%UE4_ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PROJECT_PATH%\GASShooter.uproject" ^
    -nop4 -cook -compressed -fileopenorder -platform=Win64 -clientconfig=Development ^
    -iterate -installed -stage -CookOutputDir="%PAK_OUTPUT_PATH%\Client\WindowsNoEditor" -Archive -ArchiveDirectory="%PAK_OUTPUT_PATH%\Client"
    
pause
