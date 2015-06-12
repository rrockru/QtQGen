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

#include "QColor"
#include "QFont"

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

    void SetFirstLocName(const QString &name) { _firstLocName = name; }
    QString GetFirstLocName() { return _firstLocName; }
    void SetAutoSave(bool status) { _isAutoSave = status; }
    bool GetAutoSave() { return _isAutoSave; }
    void SetShowShortLocsDescs(bool status) { _isShowShortLocsDescs = status; }
    bool GetShowShortLocsDescs() { return _isShowShortLocsDescs; }
    void SetLocDescVisible(bool status) { _isLocDescVisible = status; }
    bool GetLocDescVisible() { return _isLocDescVisible; }
    void SetLocActsVisible(bool status) { _isLocActsVisible = status; }
    bool GetLocActsVisible() { return _isLocActsVisible; }
    void SetWrapLines(bool status){ _isWrapLines = status; }
    bool GetWrapLines(){ return _isWrapLines; }
    void SetOpenNewLoc(bool status) { _isOpenNewLoc = status; }
    bool GetOpenNewLoc() { return _isOpenNewLoc; }
    void SetOpenNewAct(bool status) { _isOpenNewAct = status; }
    bool GetOpenNewAct() { return _isOpenNewAct; }
    void SetOpenLastGame(bool status) { _isOpenLastGame = status; }
    bool GetOpenLastGame() { return _isOpenLastGame; }
    void SetShowLinesNums(bool status) { _isShowLinesNums = status; }
    bool GetShowLinesNums() { return _isShowLinesNums; }
    void SetLastGamePath(const QString &path) { _lastGamePath = path; }
    QString GetLastGamePath() { return _lastGamePath; }
    void SetCreateFirstLoc(bool status) { _isCreateFirstLoc = status; }
    bool GetCreateFirstLoc() { return _isCreateFirstLoc; }
    void SetShowLocsIcons(bool status) { _isShowLocsIcons = status; }
    bool GetShowLocsIcons() { return _isShowLocsIcons; }
    void SetCollapseCode(bool status) { _isCollapseCode = status; }
    bool GetCollapseCode() { return _isCollapseCode; }
    void SetCurrentPlayerPath(const QString &path) { _currentPlayerPath = path; }
    QString GetCurrentPlayerPath() { return _currentPlayerPath; }
    void SetCurrentHelpPath(const QString &path) { _currentHelpPath = path; }
    QString GetCurrentHelpPath() { return _currentHelpPath; }
    void SetCurrentTxt2GamPath(const QString &path) { _currentTxt2GamPath = path; }
    QString GetCurrentTxt2GamPath() { return _currentTxt2GamPath; }
    void SetAutoSaveInterval(int min) { _autoSaveInterval = min; }
    int GetAutoSaveInterval() { return _autoSaveInterval; }
    void SetHeightsCoeff(double h) { _heightsCoeff = h; }
    double GetHeightsCoeff() { return _heightsCoeff; }
    void SetWidthsCoeff1(double w) { _widthsCoeff1 = w; }
    double GetWidthsCoeff1() { return _widthsCoeff1; }
    void SetWidthsCoeff2(double w) { _widthsCoeff2 = w; }
    double GetWidthsCoeff2() { return _widthsCoeff2; }
    void SetTabSize(int sz) { _tabSize = sz; }
    int GetTabSize() { return _tabSize; }
    QFont GetFont(SyntaxType type) { return _font[type]; }
    void SetFont(SyntaxType type, const QFont &font) { _font[type] = font; }
    QColor GetColor(SyntaxType type) { return _color[type]; }
    void SetColor(SyntaxType type, const QColor &col) { _color[type] = col; }
    QColor GetTextBackColor() { return _textBackColor; }
    void SetTextBackColor(const QColor &col) { _textBackColor = col; }
    QColor GetBaseBackColor() { return _baseBackColor; }
    void SetBaseBackColor(const QColor &col) { _baseBackColor = col; }
    void SetLeftFramePos(int left) { _leftFramePos = left; }
    int GetLeftFramePos() { return _leftFramePos; }
    void SetTopFramePos(int top) { _topFramePos = top; }
    int GetTopFramePos() { return _topFramePos; }
    void SetFrameWidth(int width) { _frameWidth = width; }
    int GetFrameWidth() { return _frameWidth; }
    void SetFrameHeight(int height) { _frameHeight = height; }
    int GetFrameHeight() { return _frameHeight; }
    void SetOptionsDialogWidth(int width) { _optionsDialogWidth = width; }
    int GetOptionsDialogWidth() { return _optionsDialogWidth; }
    void SetOptionsDialogHeight(int height) { _optionsDialogHeight = height; }
    int GetOptionsDialogHeight() { return _optionsDialogHeight; }
    void SetMaximizeFrame(bool status) { _isFrameMaximized = status; }
    bool GetMaximizeFrame() { return _isFrameMaximized; }
    void SetShowStatusBar(bool status) { _isShowStatusBar = status; }
    bool GetShowStatusBar() { return _isShowStatusBar; }
    void SetPanelsPos(const QString &panels) { _panelsPos = panels; }
    QString GetSetPanelsPos() { return _panelsPos; }
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

    //HotkeysStore *GetHotKeys() { return &_hotkeysStore; }
    SearchDataStore *GetSearchDataStore() { return &_searchDataStore; }
    void SetIdLang(QLocale::Language id) { _idLang = id; }
    QLocale::Language GetLangId() { return _idLang; }
    //wxString GetPath() const { return _path; }



private:
    int                _leftFramePos;
    int                _topFramePos;
    int                _frameWidth;
    int                _frameHeight;
    int                _optionsDialogWidth;
    int                _optionsDialogHeight;
    int                _autoSaveInterval;
    int                _tabSize;
    bool            _isFrameMaximized;
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
    double            _heightsCoeff;
    double            _widthsCoeff1;
    double            _widthsCoeff2;
    QFont            _font[SYNTAX_DUMMY];
    QColor         _color[SYNTAX_DUMMY];
    QColor         _textBackColor;
    QColor         _baseBackColor;
    QString         _path;
    QString         _currentConfigPath;
    QString         _currentPlayerPath;
    QString         _currentHelpPath;
    QString         _currentTxt2GamPath;
    QString         _firstLocName;
    QString         _lastGamePath;
    QString         _panelsPos;
    QString         _updateUrl;

    QByteArray      _locCodeSplitState;
    QByteArray      _locActsSplitState;
    QByteArray      _actCodeSplitState;

    //HotkeysStore    _hotkeysStore;
    SearchDataStore _searchDataStore;
    QLocale::Language                _idLang;
    QList<IObserver *>    _observers;
};

#endif // _SETTINGS_

