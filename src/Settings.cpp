#include "stdafx.h"
#include "Settings.h"

namespace Ui
{
	Settings::Settings(QString path)
	{
        _path = path;

        InitSettings();
        LoadSettings();
	}

    void Settings::InitSettings()
    {
        _currentConfigPath = QFileInfo(_currentConfigPath, "qgen.cfg").absoluteFilePath();
        _currentPlayerPath = QFileInfo(_path, "qspgui.exe").absoluteFilePath();
        _currentHelpPath = QFileInfo(_path, "qsp.chm").absoluteFilePath();
        _currentTxt2GamPath = QFileInfo(_path, "txt2gam.exe").absoluteFilePath();
        _leftFramePos = 10;
        _topFramePos = 10;
        _frameWidth = 700;
        _frameHeight = 550;
        _optionsDialogWidth = 420;
        _optionsDialogHeight = 320;
        _isFrameMaximized = false;
        _isShowStatusBar = true;

        _isAutoSave = false;
        _autoSaveInterval = 5;
        _isShowShortLocsDescs = false;
        _isLocDescVisible = true;
        _isLocActsVisible = true;
        _isWrapLines = false;
        _isOpenNewLoc = true;
        _isOpenNewAct = true;
        _isOpenLastGame = true;
        _isShowLinesNums = true;
        _isCreateFirstLoc = false;
        _firstLocName = "";
        _isShowLocsIcons = true;
        _isCollapseCode = false;
        _heightsCoeff = 0.6;
        _widthsCoeff1 = 0.3;
        _widthsCoeff2 = 0.25;
        _tabSize = 4;

        _idLang = QLocale::system().language();

        _textBackColor = QColor(220, 220, 220);
        _baseBackColor = QColor(220, 220, 220);
    }

    void Settings::LoadSettings()
    {
        QSettings settings(_currentConfigPath, QSettings::IniFormat);

        _lastGamePath = settings.value("Paths/LastGam").toString();
    }

    void Settings::SaveSettings()
    {
        QSettings settings(_currentConfigPath, QSettings::IniFormat);

        settings.setValue("Paths/LastGam", _lastGamePath);
    }
}
