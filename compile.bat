@ECHO off

ECHO Exporting scripts from scripts.txt
REM Creates compile_scripts.bat from scripts.txt in the root directory
tools\export_scripts\export_scripts.exe scripts.txt tools\export_scripts\compile_scripts.bat>NUL
ECHO Done.
ECHO.

ECHO Compiling scripts into one 0.txt
REM create 0.txt from the generated compile_scripts.bat
CALL tools\export_scripts\compile_scripts.bat>NUL
ECHO Done.
ECHO.

ECHO Creating nscript.dat using nscmake
ECHO Press any key to continue
REM create nscript.dat using nscmake
tools\nscr_sdk\nscmake.exe>NUL
ECHO Done.
ECHO.

ECHO Copying nscript.dat into /export
REM move the created nscript to the export directory
MOVE nscript.dat export\>NUL
ECHO Done.
ECHO.