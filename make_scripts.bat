@ECHO off

ECHO Exporting scripts from scripts.txt
REM Creates compile_scripts.bat from scripts.txt in the root directory
tools\export_scripts\export_scripts.exe scripts.txt tools\export_scripts\compile_scripts.bat
ECHO.

ECHO Compiling scripts into one 0.txt
REM create 0.txt from the generated compile_scripts.bat
CALL tools\export_scripts\compile_scripts.bat
ECHO Done.
ECHO.

ECHO Creating nscript.dat using nscmake
REM create nscript.dat using nscmake
tools\onscrtools\nscmake.exe 0.txt
ECHO Done.
ECHO.

ECHO Copying nscript.dat into /build
REM move the created nscript to the export directory
del build\nscript.dat
MOVE nscript.dat build\
ECHO Done.
ECHO.