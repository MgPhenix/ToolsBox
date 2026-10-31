mkdir ..\docs

doxygen\doxygen.exe ..\src\ToolsBox\DoxyfileLocal
start "" ..\docs\html\index.html