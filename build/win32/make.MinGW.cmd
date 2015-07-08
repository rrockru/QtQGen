@echo off
cls

SET MINGW=X:\Tools\Qt\5.4\mingw491_32
SET QTDIR=x:\Tools\Qt\5.4\Src\qtbase\bin\
SET QGEN_PATH=%~dp0\..\..
SET BUILD_PATH=%~dp0

SET QGEN_RELEASE_PATH=%QGEN_PATH%\release\QGen5
rem --------------------------------------------------------------------------
rd /s /q "%QGEN_RELEASE_PATH%"
call "%MINGW%\bin\qtenv2.bat"

echo Building QGen -----------------------------------------------------------
cd /d "%QGEN_PATH%"
qmake "CONFIG += release"

if not "%1"=="clean" goto compile
mingw32-make clean --quiet -j 5

:compile
mingw32-make --quiet -j 5 -f Makefile.Release

echo Making Release ----------------------------------------------------------
echo Copying QGen
md %QGEN_RELEASE_PATH%
copy %QGEN_PATH%\release\QGen.exe %QGEN_RELEASE_PATH%
echo Generating translate
md %QGEN_RELEASE_PATH%\langs
lrelease -silent -compress %QGEN_PATH%\misc\langs\qgen_ru.ts -qm %QGEN_RELEASE_PATH%\langs\qgen_ru.qm
copy %QGEN_PATH%\misc\keywords\keywords.xml %QGEN_RELEASE_PATH%

echo Copying Qt ligraries
copy %QTDIR%\Qt5Core.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\Qt5Gui.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\Qt5Widgets.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\Qt5Network.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\Qt5Xml.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\libgcc*.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\libwinpthread*.dll %QGEN_RELEASE_PATH%
copy %QTDIR%\libstdc*.dll %QGEN_RELEASE_PATH%
md %QGEN_RELEASE_PATH%\platforms
copy %QTDIR%\plugins\platforms\qwindows.dll %QGEN_RELEASE_PATH%\platforms

echo Packing release ---------------------------------------------------------
cd %~dp0
del "%QGEN_PATH%"\QGen5.zip
7za a "%QGEN_PATH%"\QGen5.zip %QGEN_RELEASE_PATH%

cd %~dp0
echo Done! -------------------------------------------------------------------
pause
