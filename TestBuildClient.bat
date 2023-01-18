@echo off

set UE4_ENGINE_PATH="C:\Program Files\Epic Games\UE_4.27\"
set PROJECT_PATH=D:\Github\GASShooter
set PAK_OUTPUT_PATH=D:\Github\GASShooter\PakOutput

%UE4_ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PROJECT_PATH%\GASShooter.uproject" ^
    -nop4 -cook -compressed -fileopenorder -platform=Win64 -clientconfig=Development ^
    -iterate -build -installed -stage -CookOutputDir="%PAK_OUTPUT_PATH%\Client\WindowsNoEditor" -Archive -ArchiveDirectory="%PAK_OUTPUT_PATH%\Client"
    
pause