@ECHO off

ECHO Running better_hint_generator.exe
cd tools\better_hint_generator\Release
better_hint_generator.exe
cd ..\..\..
ECHO Done.
ECHO.

ECHO Copying library files to graphics folder 
xcopy tools\better_hint_generator\Release\output\library graphics\bmp\r_click\text\cha /y /i
ECHO Copying glossary files to graphics folder 
xcopy tools\better_hint_generator\Release\output\glossary graphics\bmp\r_click\text\glos /y /i
ECHO Done.
ECHO.