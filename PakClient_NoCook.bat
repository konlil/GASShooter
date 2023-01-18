@echo off

set UE4_ENGINE_PATH=E:\Work\UE4_RG
set PROJECT_PATH=E:\Work\GASShooter
set PAK_OUTPUT_PATH=%PROJECT_PATH%\PakOutput

rem -CookOutputDir="%PAK_OUTPUT_PATH%\CookOutput\WindowsNoEditor"   指定这个目录会报：UE4 Unreal Game files required to initialize the global shader library are missing from
rem -archive -archivedirectory="%PAK_OUTPUT_PATH%\ArchiveOutput"  不用archive，直接使用Stage的输出（stage会自动清理输出目录）

%UE4_ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="%PROJECT_PATH%\GASShooter.uproject" ^
    -nop4 -cook -SkipCook -compressed -fileopenorder -iterate ^
    -Pak -SkipPak ^
    -build -platform=Win64 -clientconfig=Development -nocompileeditor ^
    -stage -StagingDirectory="%PAK_OUTPUT_PATH%\StageOutput"

pause
