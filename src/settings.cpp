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

    _lastGamePath = settings.value("Paths/LastGame").toString();

    _searchDataStore.LoadSearchData(settings);
}

void Settings::SaveSettings()
{
    QSettings settings(_currentConfigPath, QSettings::IniFormat);

    settings.setValue("CreateFirstLoc", _isCreateFirstLoc);
    settings.setValue("FirstLocName", _firstLocName);
    settings.setValue("LocActsVisible", _isLocActsVisible);
    settings.setValue("LocDescVisible", _isLocDescVisible);
    settings.setValue("OpenNewAct", _isOpenNewAct);
    settings.setValue("OpenNewLoc", _isOpenNewLoc);
    settings.setValue("OpenLastGame", _isOpenLastGame);
    settings.setValue("ShowLocsIcons", _isShowLocsIcons);


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
