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

#include "settings.h"

Settings::Settings(QString path)
{
    _path = path;

    InitSettings();
    LoadSettings();
}

void Settings::InitSettings()
{
    _updateUrl = "http://test-rrock.rhcloud.com/QGen/";

    _currentConfigPath = QFileInfo(_path, "qgen.cfg").absoluteFilePath();
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

    _font[SYNTAX_BASE] = QFont("Courier New", 10);
    _font[SYNTAX_STATEMENTS] = QFont("Courier New", 10, QFont::Bold);
    _font[SYNTAX_FUNCTIONS] = QFont("Courier New", 10, QFont::Bold);
    _font[SYNTAX_SYS_VARIABLES] = QFont("Courier New", 10, QFont::Bold);
    _font[SYNTAX_STRINGS] = QFont("Courier New", 10);
    _font[SYNTAX_NUMBERS] = QFont("Courier New", 10, QFont::Bold);
    _font[SYNTAX_OPERATIONS] = QFont("Courier New", 10, QFont::Bold);
    _font[SYNTAX_LABELS] = QFont("Courier New", 10, QFont::Bold);
    _font[SYNTAX_COMMENTS] = QFont("Courier New", 10);

    _textBackColor = QColor(220, 220, 220);
    _baseBackColor = QColor(220, 220, 220);
    _color[SYNTAX_BASE] = Qt::black;
    _color[SYNTAX_STATEMENTS] = Qt::blue;
    _color[SYNTAX_FUNCTIONS] = Qt::blue;
    _color[SYNTAX_SYS_VARIABLES] = Qt::blue;
    _color[SYNTAX_STRINGS] = QColor(0, 120, 25);
    _color[SYNTAX_NUMBERS] = QColor(150, 0, 150);
    _color[SYNTAX_OPERATIONS] = QColor(0, 0, 140);
    _color[SYNTAX_LABELS] = Qt::red;
    _color[SYNTAX_COMMENTS] = QColor(130, 130, 130);
}

void Settings::LoadSettings()
{
    QSettings settings(_currentConfigPath, QSettings::IniFormat);

    if (!settings.contains("OpenLastGame")) {
        return;
    }

    _isCreateFirstLoc = settings.value("CreateFirstLoc").toBool();
    _firstLocName = settings.value("FirstLocName").toString();
    _isLocActsVisible = settings.value("LocActsVisible").toBool();
    _isLocDescVisible = settings.value("LocDescVisible").toBool();
    _isOpenNewAct = settings.value("OpenNewAct").toBool();
    _isOpenNewLoc = settings.value("OpenNewLoc").toBool();
    _isOpenLastGame = settings.value("OpenLastGame").toBool();
    _isShowLocsIcons = settings.value("ShowLocsIcons").toBool();

    _textBackColor = settings.value("Colors/TextBackground").value<QColor>();
    _baseBackColor = settings.value("Colors/BaseBackground").value<QColor>();
    _color[SYNTAX_BASE] = settings.value("Colors/Base").value<QColor>();
    _color[SYNTAX_STATEMENTS] = settings.value("Colors/Statements").value<QColor>();
    _color[SYNTAX_FUNCTIONS] = settings.value("Colors/Functions").value<QColor>();
    _color[SYNTAX_SYS_VARIABLES] = settings.value("Colors/SysVariables").value<QColor>();
    _color[SYNTAX_STRINGS] = settings.value("Colors/Strings").value<QColor>();
    _color[SYNTAX_NUMBERS] = settings.value("Colors/Numbers").value<QColor>();
    _color[SYNTAX_OPERATIONS] = settings.value("Colors/Operations").value<QColor>();
    _color[SYNTAX_LABELS] = settings.value("Colors/Labels").value<QColor>();
    _color[SYNTAX_COMMENTS] = settings.value("Colors/Comments").value<QColor>();

    _font[SYNTAX_BASE] = settings.value("Fonts/Base").value<QFont>();
    _font[SYNTAX_STATEMENTS] = settings.value("Fonts/Statements").value<QFont>();
    _font[SYNTAX_FUNCTIONS] = settings.value("Fonts/Functions").value<QFont>();
    _font[SYNTAX_SYS_VARIABLES] = settings.value("Fonts/SysVariables").value<QFont>();
    _font[SYNTAX_STRINGS] = settings.value("Fonts/Strings").value<QFont>();
    _font[SYNTAX_NUMBERS] = settings.value("Fonts/Numbers").value<QFont>();
    _font[SYNTAX_OPERATIONS] = settings.value("Fonts/Operations").value<QFont>();
    _font[SYNTAX_LABELS] = settings.value("Fonts/Labels").value<QFont>();
    _font[SYNTAX_COMMENTS] = settings.value("Fonts/Comments").value<QFont>();

    _lastGamePath = settings.value("Paths/LastGame").toString();

    _searchDataStore.LoadSearchData(settings);
}

void Settings::SaveSettings()
{
    QSettings settings(_currentConfigPath, QSettings::IniFormat);

    settings.clear();

    settings.setValue("CreateFirstLoc", _isCreateFirstLoc);
    settings.setValue("FirstLocName", _firstLocName);
    settings.setValue("LocActsVisible", _isLocActsVisible);
    settings.setValue("LocDescVisible", _isLocDescVisible);
    settings.setValue("OpenNewAct", _isOpenNewAct);
    settings.setValue("OpenNewLoc", _isOpenNewLoc);
    settings.setValue("OpenLastGame", _isOpenLastGame);
    settings.setValue("ShowLocsIcons", _isShowLocsIcons);

    settings.setValue("Colors/TextBackground", _textBackColor);
    settings.setValue("Colors/BaseBackground", _baseBackColor);
    settings.setValue("Colors/Base", _color[SYNTAX_BASE]);
    settings.setValue("Colors/Statements", _color[SYNTAX_STATEMENTS]);
    settings.setValue("Colors/Functions", _color[SYNTAX_FUNCTIONS]);
    settings.setValue("Colors/SysVariables", _color[SYNTAX_SYS_VARIABLES]);
    settings.setValue("Colors/Strings", _color[SYNTAX_STRINGS]);
    settings.setValue("Colors/Numbers", _color[SYNTAX_NUMBERS]);
    settings.setValue("Colors/Operations", _color[SYNTAX_OPERATIONS]);
    settings.setValue("Colors/Labels", _color[SYNTAX_LABELS]);
    settings.setValue("Colors/Comments", _color[SYNTAX_COMMENTS]);

    settings.setValue("Fonts/Base", _font[SYNTAX_BASE]);
    settings.setValue("Fonts/Statements", _font[SYNTAX_STATEMENTS]);
    settings.setValue("Fonts/Functions", _font[SYNTAX_FUNCTIONS]);
    settings.setValue("Fonts/SysVariables", _font[SYNTAX_SYS_VARIABLES]);
    settings.setValue("Fonts/Strings", _font[SYNTAX_STRINGS]);
    settings.setValue("Fonts/Numbers", _font[SYNTAX_NUMBERS]);
    settings.setValue("Fonts/Operations", _font[SYNTAX_OPERATIONS]);
    settings.setValue("Fonts/Labels", _font[SYNTAX_LABELS]);
    settings.setValue("Fonts/Comments", _font[SYNTAX_COMMENTS]);

    settings.setValue("Paths/LastGame", _lastGamePath);

    _searchDataStore.SaveSearchData(settings);
}

void Settings::AddObserver(IObserver *obj)
{
    _observers.push_back(obj);
}

void Settings::RemoveObserver(IObserver *obj)
{
    _observers.removeOne(obj);
}

void Settings::RemoveAllObservers()
{
    _observers.clear();
}

void Settings::NotifyAll()
{
    QListIterator<IObserver *> i(_observers);
    while (i.hasNext())
        (*i.next()).Update(true);
}
