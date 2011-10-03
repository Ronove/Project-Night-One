@ECHO off

ECHO Exporting scripts...
tools\export_scripts\export_scripts.exe scripts.txt tools\export_scripts\compile_scripts.bat

ECHO Compiling scripts...
tools\export_scripts\compile_scripts.bat>NUL