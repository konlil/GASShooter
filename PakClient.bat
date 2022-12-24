@echo off

set UE4_ENGINE_PATH=E:\Work\UE4_RG
set PROJECT_PATH=E:\Work\GASShooter
set PAK_OUTPUT_PATH=%PROJECT_PATH%\PakOutput

%UE4_ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PROJECT_PATH%\GASShooter.uproject" ^
    -nop4 -cook -compressed -fileopenorder -iterate -CookOutputDir="%PAK_OUTPUT_PATH%\CookOutput\WindowsNoEditor" ^
    -Pak ^
    -build -platform=Win64 -clientconfig=Development -nocompileeditor ^
    -stage -StagingDirectory="%PAK_OUTPUT_PATH%\StageOutput" ^
    -archive -archivedirectory="%PAK_OUTPUT_PATH%\ArchiveOutput"
pause
