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

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#define QGEN_TITLE "QGen"
#define QSP_CONFIG "qgen.cfg"

#include "locationslistbox.h"
#include "locationpage.h"
#include "tabswidget.h"
#include "icontrols.h"
#include "maintoolbar.h"
#include "searchdialog.h"

enum
{
    ID_MAINDESC,
    ID_VARSDESC,
    ID_OBJECTS,
    ID_ACTIONS,
    ID_VIEWPIC,
    ID_INPUT,
    ID_TIMER,

    ID_DUMMY
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(IControls *controls);
    //~MainWindow();

    LocationsListBox *GetLocListBox() const { return _locListBox; }
    TabsWidget *GetTabsWidget() const { return _tabWidget; }

    void UpdateTitle();
    void Init(QString filename);
    void Update();

private:
    void CreateMenuBar();
    void CreateToolBar();
    void CreateDockWindows();
    void CreateStatusBar();

    bool QuestChange();

    MainToolBar             *_toolbar;
    LocationsListBox        *_locListBox;
    TabsWidget                *_tabWidget;
    QDockWidget               *_dock;
    IControls                *_controls;

    SearchDialog            *_findDlg;

    QAction *saveGameAction;
    QAction *saveAsGameAction;
    QAction *renameAction;
    QAction *delAction;
    QAction *newActAction;
    QAction *renameActAction;
    QAction *delActAction;
    QAction *delAllActAction;
    QAction *toolBarVisAction;
    QAction *locListVisAction;
    QAction *statusBarVisAction;
    QAction *locDescVisAction;
    QAction *locActsVisAction;

private slots:
    void OnAbout();

public slots:
    void OnLoadGame();
    void OnSaveGame();
    void OnSaveGameAs();
    void OnInformationQuest();
    void OnFindDialog();
    void OnNewGame();

    void OnRename();
    void OnDelete();

    void OnCreateLocation();
    void OnRenameLocation();
    void OnDeleteLocation();

    void OnCreateFolder();
    void OnRenameFolder();
    void OnDeleteFolder();

    void OnAddAction();
    void OnRenAction();
    void OnDelAction();
    void OnDelAllActions();

    void OnToggleToolBar(bool);
    void OnToggleLocList(bool);
    void OnToggleStatusBar(bool);

    void OnLocDescVisible();
    void OnLocActsVisible();

    void OnLocVisChanged(bool);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // _MAIN_WINDOW_H_
