@echo off
cls

SET VC=c:\Program Files (x86)\Microsoft Visual Studio 10.0
SET QGEN_PATH=%~dp0\..\..
SET BUILD_PATH=%~dp0

SET QGEN_RELEASE_PATH=%QGEN_PATH%\release\QGen5
rem --------------------------------------------------------------------------
rd /s /q "%QGEN_RELEASE_PATH%"
cd /d "%QGEN_PATH%"

echo Building QGen -----------------------------------------------------------
call "%VC%\Common7\Tools\vsvars32.bat"
qmake "CONFIG += release"
nmake Makefile.Release

echo Making Release ----------------------------------------------------------
echo Copying QGen
md %QGEN_RELEASE_PATH%
copy %QGEN_PATH%\release\QGen.exe %QGEN_RELEASE_PATH%
echo Generating translate
md %QGEN_RELEASE_PATH%\langs
lrelease -silent -compress %QGEN_PATH%\misc\langs\qgen_ru.ts -qm %QGEN_RELEASE_PATH%\langs\qgen_ru.qm

echo Copying Qt ligraries
copy %QTDIR%\bin\Qt5Core.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\Qt5Gui.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\Qt5Widgets.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\Qt5Network.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\Qt5Xml.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\bin\qscintilla2.dll %QGEN_RELEASE_PATH%
md %QGEN_RELEASE_PATH%\platforms
copy %QTDIR%\plugins\platforms\qwindows.dll %QGEN_RELEASE_PATH%\platforms

echo Copying MSVC redist
copy "%VC%\VC\redist\x86\Microsoft.VC100.CRT\msvcp100.dll" %QGEN_RELEASE_PATH%
copy "%VC%\VC\redist\x86\Microsoft.VC100.CRT\msvcr100.dll" %QGEN_RELEASE_PATH%

echo Packing release ---------------------------------------------------------
cd %~dp0
7za a "%QGEN_PATH%"\QGen5.zip %QGEN_RELEASE_PATH%

cd %~dp0
echo Done! -------------------------------------------------------------------
pause
