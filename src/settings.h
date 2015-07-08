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

#ifndef _SETTINGS_
#define _SETTINGS_

#include <QColor>
#include <QFont>
#include <QLocale>
#include <QSettings>

#include "iobserver.h"
#include "searchdatastore.h"

enum SyntaxType
{
    SYNTAX_STATEMENTS,
    SYNTAX_FUNCTIONS,
    SYNTAX_SYS_VARIABLES,
    SYNTAX_STRINGS,
    SYNTAX_NUMBERS,
    SYNTAX_OPERATIONS,
    SYNTAX_LABELS,
    SYNTAX_COMMENTS,
    SYNTAX_BASE,
    SYNTAX_DUMMY
};

class Settings
{
public:
    Settings(QString);
    void InitSettings();
    void LoadSettings();
    void SaveSettings();
    void AddObserver(IObserver *obj);
    void RemoveObserver(IObserver *obj);
    void RemoveAllObservers();
    void NotifyAll();

    void SetCreateFirstLoc(const bool &status) { _isCreateFirstLoc = status; }
    bool GetCreateFirstLoc() { return _isCreateFirstLoc; }
    void SetFirstLocName(const QString &name) { _firstLocName = name; }
    QString GetFirstLocName() { return _firstLocName; }
    void SetAutoSave(const bool &status) { _isAutoSave = status; }
    bool GetAutoSave() { return _isAutoSave; }
    //void SetAutoSaveInterval(int min) { _autoSaveInterval = min; }
    int GetAutoSaveInterval() { return _autoSaveInterval; }
    void SetShowShortLocsDescs(const bool &status) { _isShowShortLocsDescs = status; }
    bool GetShowShortLocsDescs() { return _isShowShortLocsDescs; }
    void SetLocDescVisible(const bool &status) { _isLocDescVisible = status; }
    bool GetLocDescVisible() { return _isLocDescVisible; }
    void SetLocActsVisible(const bool &status) { _isLocActsVisible = status; }
    bool GetLocActsVisible() { return _isLocActsVisible; }
    //void SetWrapLines(const bool &status){ _isWrapLines = status; }
    //bool GetWrapLines(){ return _isWrapLines; }
    void SetOpenNewLoc(const bool &status) { _isOpenNewLoc = status; }
    bool GetOpenNewLoc() { return _isOpenNewLoc; }
    void SetOpenNewAct(const bool &status) { _isOpenNewAct = status; }
    bool GetOpenNewAct() { return _isOpenNewAct; }
    void SetOpenLastGame(const bool &status) { _isOpenLastGame = status; }
    bool GetOpenLastGame() { return _isOpenLastGame; }
    //void SetShowLinesNums(const bool &status) { _isShowLinesNums = status; }
    //bool GetShowLinesNums() { return _isShowLinesNums; }
    void SetShowLocsIcons(const bool &status) { _isShowLocsIcons = status; }
    bool GetShowLocsIcons() { return _isShowLocsIcons; }
    //void SetCollapseCode(const bool &status) { _isCollapseCode = status; }
    bool GetCollapseCode() { return _isCollapseCode; }
    void SetPlayerPath(const QString &path) { _pathPlayer = path; }
    QString GetPlayerPath() { return _pathPlayer; }
    //void SetHelpPath(const QString &path) { _currentHelpPath = path; }
    //QString GetHelpPath() { return _currentHelpPath; }
    //void SetTxt2GamPath(const QString &path) { _currentTxt2GamPath = path; }
    //QString GetTxt2GamPath() { return _currentTxt2GamPath; }
    QFont GetFont(SyntaxType type) { return _font[type]; }
    void SetFont(SyntaxType type, const QFont &font) { _font[type] = font; }
    QColor GetColor(SyntaxType type) { return _color[type]; }
    void SetColor(SyntaxType type, const QColor &col) { _color[type] = col; }
    QColor GetTextBackColor() { return _textBackColor; }
    void SetTextBackColor(const QColor &col) { _textBackColor = col; }
    QColor GetBaseBackColor() { return _baseBackColor; }
    void SetBaseBackColor(const QColor &col) { _baseBackColor = col; }
    void SetUpdateURL(const QString &url) { _updateUrl = url; }
    QString GetUpdateURL() { return _updateUrl; }
    void SetSaveGameWithPassword(bool status) { _isSaveGameWithPassword = status; }
    bool GetSaveGameWithPassword() { return _isSaveGameWithPassword; }
    void SetLocCodeSplitState(QByteArray state) { _locCodeSplitState = state; }
    QByteArray GetLocCodeSplitState() { return _locCodeSplitState; }
    void SetLocActsSplitState(QByteArray state) { _locActsSplitState = state; }
    QByteArray GetLocActsSplitState() { return _locActsSplitState; }
    void SetActCodeSplitState(QByteArray state) { _actCodeSplitState = state; }
    QByteArray GetActCodeSplitState() { return _actCodeSplitState; }
    void SetMainWindowState(QByteArray state) { _mainWindowState = state; }
    QByteArray GetMainWindowState() { return _mainWindowState; }
    void SetLastGamePath(const QString &path) { _lastGamePath = path; }
    QString GetLastGamePath() { return _lastGamePath; }
    void SetLocale(QLocale locale);
    QLocale GetLocale() { return _locale; }
    void SetAutoUpdate(bool state) { _isAutoUpdate = state; }
    bool GetAutoUpdate() { return _isAutoUpdate; }

    //HotkeysStore *GetHotKeys() { return &_hotkeysStore; }
    SearchDataStore *GetSearchDataStore() { return &_searchDataStore; }

    bool IsLanguageChanged() { return _isLanguageChanged; }

private:
    int             _autoSaveInterval;

    bool            _isShowStatusBar;
    bool            _isAutoSave;
    bool            _isShowShortLocsDescs;
    bool            _isLocDescVisible;
    bool            _isLocActsVisible;
    bool            _isWrapLines;
    bool            _isOpenNewLoc;
    bool            _isOpenNewAct;
    bool            _isOpenLastGame;
    bool            _isShowLinesNums;
    bool            _isCreateFirstLoc;
    bool            _isShowLocsIcons;
    bool            _isCollapseCode;
    bool            _isSaveGameWithPassword;
    bool            _isAutoUpdate;

    bool            _isLanguageChanged;

    double            _heightsCoeff;
    double            _widthsCoeff1;
    double            _widthsCoeff2;
    QFont            _font[SYNTAX_DUMMY];
    QColor         _color[SYNTAX_DUMMY];
    QColor         _textBackColor;
    QColor         _baseBackColor;
    QString         _path;
    QString         _pathConfig;
    QString         _pathPlayer;
    QString         _pahtHelp;
    QString         _pathTxt2Gam;
    QString         _firstLocName;
    QString         _lastGamePath;
    QString         _panelsPos;
    QString         _updateUrl;

    QByteArray      _locCodeSplitState;
    QByteArray      _locActsSplitState;
    QByteArray      _actCodeSplitState;
    QByteArray      _mainWindowState;

    //HotkeysStore    _hotkeysStore;
    SearchDataStore _searchDataStore;
    QLocale                _locale;
    QList<IObserver *>    _observers;
};

#endif // _SETTINGS_

