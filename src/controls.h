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

#ifndef _CONTROLS_
#define _CONTROLS_

#include "icontrols.h"
#include "mainwindow.h"

#include "game.h"
#include "mergedialog.h"
#include "settings.h"

struct DataSearch
{
    int			idxLoc;
    int			idxAct;
    long		startPos;
    long		stringLen;
    int			countChecking;
    SearchPlace foundAt;
    SearchPlace findAt;
    bool		isFoundAny;
};

class Controls :
    public IControls
{
public:
    Controls(const QString);

    void SetMainWindow(MainWindow *wnd) { _mainWindow = wnd; }
    void SetLocListBox(LocationsListBox *loc) { _locListBox = loc; }
    void SetTabsWidget(TabsWidget *tabs) { _tabsWidget = tabs; }

    void SetStatusText(const QString &text);
    void CleanStatusText();
    bool LoadGame(const QString &filename);
    bool SaveGame(const QString &filename, const QString &password);
    bool SaveGameWithCheck();
    void NewGame();
    bool IsGameSaved();
    bool IsCanSaveGame();

    void InitSearchData();

    void ShowMessage(long errorNum);
    void ShowMessage(QString msg);
    QString GetMessageDesc(long errorNum);

    QString GetGamePath() const { return _currentGamePath; }

    void SetParent(QWidget *wnd) { _parent = wnd; }
    QWidget *GetParent() { return _parent; }
    void Update();

    Settings *GetSettings() const { return _settings; }
    DataContainer *GetContainer() const { return _container; }

    void UpdateLocationsList();
    void SyncWithLocationsList();
    void ShowOpenedLocationsIcons();

    LocationPage *ShowLocation(const QString & locName);

    bool AddFolder();
    bool DeleteSelectedFolder();
    bool RenameSelectedFolder();
    bool RenameFolder(size_t folderIndex, const QString &name);

    void UpdateLocationIcon(size_t locIndex, bool isOpened);
    void UpdateActionsOnAllLocs();
    bool AddActionOnSelectedLoc();
    bool DeleteSelectedAction();
    bool RenameSelectedAction();
    bool RenameAction(size_t locIndex, size_t actIndex, const QString &name);
    void MoveActionTo(size_t locIndex, size_t actIndex, size_t moveTo);
    bool DeleteAllActions();

    bool IsActionsOnSelectedLocEmpty() const;

    bool UpdateLocale(QLocale::Language lang);

    QTranslator * GetTranslator() { return _translator; }

    KeywordsStore *GetKeywordsStore() const { return _keywordsStore; }

    void UpdateOpenedLocationsIndexes();

    QString GetGameInfo() const;

    int AddLocation(const QString &name = "");
    int AddLocationByName(const QString &name);
    bool RenameSelectedLocation();
    int GetSelectedLocationIndex() const;
    int GetSelectedFolderIndex() const;
    bool RenameLocation(size_t locIndex, const QString &name);
    bool DeleteSelectedLocation();
    void SetFailedFilesList(const QStringList files) { _failedFiles = files; }
    bool SearchString(const QString &str, bool findAgain, bool isMatchCase = false, bool isWholeString = false);
    void ReplaceSearchString(const QString & replaceString);
    bool SearchNextLoc();

    int GetSelectionCount() const;
    void DeleteSelectedItems();

    void SwitchLocDesc();
    void SwitchLocActs();

    bool GetSaveState() { return _lastSaveState; }

private:
    void InitData();

    MainWindow *_mainWindow;
    QWidget *_parent;
    LocationsListBox *_locListBox;
    TabsWidget *_tabsWidget;
    DataContainer *_container;
    Settings *_settings;
    KeywordsStore* _keywordsStore;
    DataSearch _dataSearch;

    QTranslator *_translator;

    QString        _currentPath;
    QString        _currentGamePath;
    QString        _currentGamePass;

    QStringList _failedFiles;

    bool _lastSaveState;

    static QString ConvertSearchString(const QString& s, bool isMatchCase);
    static int FindSubString(const QString& s, const QString& sub, bool isWholeString, int ind = 0);
};

#endif // _CONTROLS_

