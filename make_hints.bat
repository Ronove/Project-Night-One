@ECHO off

ECHO Running HintGenerator.exe
cd tools\hint_generator\bin\
HintGenerator.exe
cd ..\..\..
ECHO Done.
ECHO.

ECHO Copying library files to graphics folder 
tools\xcopy\xcopy.exe tools\hint_generator\bin\output\library graphics\bmp\r_click\text\cha /y /i
ECHO Done.
ECHO.