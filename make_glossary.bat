@ECHO off

ECHO Running glossary_generator.exe to update glossary entries
cd tools\glossary_generator\bin
glossary_generator.exe dataset.csv ..\..\..\glossary.script
cd ..\..\..
ECHO Done.
ECHO.