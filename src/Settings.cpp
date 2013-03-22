// Copyright (C) 2013
// Shchannikov Dmitry (rrock DOT ru AT gmail DOT com)
// Nex (nex AT otaku DOT ru)
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

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
