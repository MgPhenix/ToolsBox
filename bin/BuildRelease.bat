@echo off

rmdir /s /q ..\ToolsBox_Release

mkdir ..\ToolsBox_Release
mkdir ..\ToolsBox_Release\include
mkdir ..\ToolsBox_Release\lib
mkdir ..\ToolsBox_Release\Examples
mkdir ..\ToolsBox_Release\docs

xcopy ..\src\ToolsBox\*.h ..\ToolsBox_Release\include\ /S /Y
xcopy ..\src\ToolsBox\*.inl ..\ToolsBox_Release\include\ /S /Y

copy ..\ide\ToolsBox\x64\Release\*.lib ..\ToolsBox_Release\lib
copy ..\README.md ..\ToolsBox_Release\

xcopy ..\src\Examples ..\ToolsBox_Release\Examples /S /Y

doxygen\doxygen.exe ..\src\ToolsBox\Doxyfile

powershell Compress-Archive ..\ToolsBox_Release ..\ToolsBox_Release.zip -Force

echo done!

start "" ..\ToolsBox_Release\docs\html\index.html

pause