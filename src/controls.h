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

#include "IControls.h"
#include "mainwindow.h"

#include "game.h"
#include "mergedialog.h"
#include "Settings.h"

namespace Ui
{
    class Controls :
        public IControls
    {


    public:
        Controls(const QString);

        void SetMainWindow(MainWindow *wnd) { _mainWindow = wnd; }
        void SetLocListBox(LocationsListBox *loc) { _locListBox = loc; }
        void SetTabsWisget(TabsWidget *tabs) { _tabsWidget = tabs; }

        void SetStatusText(const QString &text);
        void CleanStatusText();
        bool LoadGame(QString);
        bool SaveGame(const QString &path, const QString &password);
        bool SaveGameWithCheck();
        void NewGame();
        bool IsGameSaved();
        bool IsCanSaveGame();

        void ShowMessage(long errorNum);
        void ShowMessage(QString msg);
        QString GetMessageDesc(long errorNum);

        QString GetGamePath() const { return _currentGamePath; }

        QWidget *GetParent() { return _mainWindow; }

        Settings *GetSettings() const { return _settings; }
        DataContainer *GetContainer() const { return _container; }

        void UpdateLocationsList();
        void SyncWithLocationsList();

        LocationPage *ShowLocation(const QString & locName);

        void UpdateLocationIcon(size_t locIndex, bool isOpened);
        void UpdateActionsOnAllLocs();
        bool AddActionOnSelectedLoc();
        bool DeleteSelectedAction();
        bool RenameSelectedAction();
        bool RenameAction(size_t locIndex, size_t actIndex, const QString &name);

        bool UpdateLocale(QLocale::Language lang);

        QTranslator * GetTranslator() { return _translator; }

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

    private:
        void InitData();

        MainWindow *_mainWindow;
        LocationsListBox *_locListBox;
        TabsWidget *_tabsWidget;
        DataContainer *_container;
        Settings *_settings;

        QTranslator *_translator;

        QString        _currentPath;
        QString        _currentGamePath;
        QString        _currentGamePass;

        QStringList _failedFiles;
    };
} // namespace Ui

#endif // _CONTROLS_

