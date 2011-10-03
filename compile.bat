@ECHO off

ECHO Exporting scripts...
export_scripts.exe scripts.txt compile_scripts.bat

ECHO Compiling scripts...
compile_scripts.bat>NUL