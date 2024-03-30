@echo off

set UE4_ENGINE_PATH=D:\Work\UE4_RG
set PROJECT_PATH=D:\Github\GASShooter
set PAK_OUTPUT_PATH=%PROJECT_PATH%\PakOutput

rem -CookOutputDir="%PAK_OUTPUT_PATH%\CookOutput\WindowsNoEditor"   指定这个目录会报：UE4 Unreal Game files required to initialize the global shader library are missing from
rem -archive -archivedirectory="%PAK_OUTPUT_PATH%\ArchiveOutput"  不用archive，直接使用Stage的输出（stage会自动清理输出目录）

%UE4_ENGINE_PATH%\Engine\Binaries\Win64\UE4Editor-Cmd.exe "%PROJECT_PATH%\GASShooter.uproject" -run=Cook -TargetPlatform=WindowsNoEditor

pause
