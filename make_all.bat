@ECHO OFF

MKDIR build
cd build
MKDIR HiganbanaEnglish
cd ..

REM Script processing
CALL make_glossary.bat
CALL make_scripts.bat

REM Graphics processing
CALL make_hints.bat
CALL make_graphics.bat
CALL make_buttons.bat

REM DLLs
CALL make_dlls.bat

REM Font
CALL make_font.bat

REM Executable shenanigans
CALL make_onscripter.bat
CALL make_icon.bat

PAUSE