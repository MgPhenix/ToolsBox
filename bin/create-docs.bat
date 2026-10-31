mkdir ..\docs

doxygen\doxygen.exe ..\src\ToolsBox\DoxyfileLocal
start "" ..\docs\index.html