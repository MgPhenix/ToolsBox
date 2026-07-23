@echo off

rmdir /s /q ..\ToolsBox_Release

mkdir ..\ToolsBox_Release
mkdir ..\ToolsBox_Release\include
mkdir ..\ToolsBox_Release\lib

xcopy ..\src\ToolsBox\*.h ..\ToolsBox_Release\include\ /S /Y
xcopy ..\src\ToolsBox\*.inl ..\ToolsBox_Release\include\ /S /Y

copy ..\ide\ToolsBox\x64\Release\*.lib ..\ToolsBox_Release\lib
copy ..\README.md ..\ToolsBox_Release\

powershell Compress-Archive ..\ToolsBox_Release ..\ToolsBox_Release.zip -Force

echo done!
pause