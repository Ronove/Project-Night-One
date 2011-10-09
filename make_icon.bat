@ECHO OFF

ECHO Changing build/onscripter-en.exe's icon to icon/icon.ico
"tools\Resource Hacker\ResHacker.exe" -modify onscripter-en/onscripter-en.exe, build/onscripter-en.exe, icon\icon.ico, icon, 101,
ECHO Done.
ECHO.