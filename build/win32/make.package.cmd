@echo off

SET QGEN_PATH=%1
SET BUILD_PATH=%cd%
SET PATH=%QTDIR%\bin;%PATH%

SET QGEN_RELEASE_PATH=%BUILD_PATH%\QGen5
rem --------------------------------------------------------------------------
rd /s /q "%QGEN_RELEASE_PATH%"
cd /d "%QGEN_PATH%"

echo Making Release ----------------------------------------------------------
echo Copying QGen
md %QGEN_RELEASE_PATH%
copy %BUILD_PATH%\release\QGen.exe %QGEN_RELEASE_PATH%
echo Generating translate
md %QGEN_RELEASE_PATH%\langs
lrelease -silent -compress %QGEN_PATH%\misc\langs\qgen_ru.ts -qm %QGEN_RELEASE_PATH%\langs\qgen_ru.qm
copy %QGEN_PATH%\misc\keywords\keywords.xml %QGEN_RELEASE_PATH%
md %QGEN_RELEASE_PATH%\crash

echo Copying Qt ligraries
copy %QTDIR%\bin\Qt5Core.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\Qt5Gui.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\Qt5Widgets.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\Qt5Network.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\Qt5Xml.dll %QGEN_RELEASE_PATH%
md %QGEN_RELEASE_PATH%\platforms
copy %QTDIR%\plugins\platforms\qwindows.dll %QGEN_RELEASE_PATH%\platforms

echo Packing release ---------------------------------------------------------
cd %QGEN_PATH%\tools\win32
upx -9 %QGEN_RELEASE_PATH%\QGen.exe
del "%BUILD_PATH%"\QGen5*.zip
7za a "%BUILD_PATH%"\QGen5_%date:~-4,4%%date:~-7,2%%date:~-10,2%.zip %QGEN_RELEASE_PATH%

cd %~dp0
echo Done! -------------------------------------------------------------------
pause
