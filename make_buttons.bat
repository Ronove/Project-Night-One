@ECHO OFF

ECHO Generating buttons from tools\glossary_button_generator\Release\dataset.csv
cd tools\glossary_button_generator\Release
glossary_button_generator.exe
cd ..\..\..
ECHO Done.
ECHO.

ECHO Copying buttons to graphics folder
xcopy tools\glossary_button_generator\Release\output graphics\bmp\glos_btn /y /i
ECHO Done.
ECHO.
