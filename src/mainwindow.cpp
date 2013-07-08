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

#include "mainwindow.h"
#include "game.h"

MainWindow::MainWindow(IControls *controls) :
    QMainWindow()
{
    _controls = controls;

    setMinimumSize(QSize(550, 300));
    setDockNestingEnabled(true);
    resize(640, 480);

    // Set QMainWindow in the center of desktop
    QRect _defRect = geometry();
    _defRect.moveCenter(QApplication::desktop()->availableGeometry().center());
    setGeometry(_defRect);

    setContextMenuPolicy(Qt::NoContextMenu);

    _tabWidget = new TabsWidget(this, _controls);
    setCentralWidget(_tabWidget);

    CreateDockWindows();
    CreateMenuBar();
    CreateToolBar();
    CreateStatusBar();

    _findDlg = NULL;
}

void MainWindow::CreateMenuBar()
{
    QMenu *file_menu = menuBar()->addMenu(tr("&Game"));
    file_menu->addAction(QIcon(":/menu/game_new"), tr("&New\tCtrl+N"), this, SLOT(OnNewGame()), QKeySequence(Qt::CTRL + Qt::Key_N));
    file_menu->addAction(QIcon(":/menu/file_open"), tr("&Open...\tCtrl+O"), this, SLOT(OnLoadGame()), QKeySequence(Qt::CTRL + Qt::Key_O));
//        file_menu->addAction(tr("&Merge game...\tCtrl+M"));
    saveGameAction = new QAction(QIcon(":/menu/file_save"), tr("&Save\tCtrl+S"), file_menu);
    saveGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    connect(saveGameAction, SIGNAL(triggered()), this, SLOT(OnSaveGame()));
    file_menu->addAction(saveGameAction);
    saveAsGameAction = new QAction(tr("Save &as...\tCtrl+W"), file_menu);
    saveAsGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
    connect(saveAsGameAction, SIGNAL(triggered()), this, SLOT(OnSaveGameAs()));
    file_menu->addAction(saveAsGameAction);
//        file_menu->addSeparator();
//        QMenu *file_sub_exp_menu = new QMenu(tr("&Export"));
//        file_sub_exp_menu->addAction(tr("Text file..."));
//        file_sub_exp_menu->addAction(tr("Text file in TXT2GAM format..."));
//        file_menu->addMenu(file_sub_exp_menu);
//        QMenu *file_sub_imp_menu = new QMenu(tr("&Import"));
//        file_sub_imp_menu->addAction(tr("Text file in TXT2GAM format..."));
//        file_menu->addMenu(file_sub_imp_menu);
    file_menu->addSeparator();
    file_menu->addAction(QIcon(":/menu/exit"), tr("&Exit\tAlt+X"), this, SLOT(close()), QKeySequence(Qt::CTRL + Qt::Key_X));

    QMenu *util_menu = menuBar()->addMenu(tr("&Utilities"));
//        util_menu->addAction(QIcon(":/menu/game_play"), tr("&Run game\tF5"));
    util_menu->addAction(QIcon(":/menu/text_search"), tr("&Find / Replace\tCtrl+F"), this, SLOT(OnFindDialog()), QKeySequence(Qt::CTRL + Qt::Key_F));
    util_menu->addAction(QIcon(":/menu/game_info"), tr("&Game info\tCtrl+I"), this, SLOT(OnInformationQuest()), QKeySequence(Qt::CTRL + Qt::Key_I));
//        util_menu->addSeparator();
//        util_menu->addAction(tr("&Settings...\tCtrl+P"));

    QMenu *loc_menu = menuBar()->addMenu(tr("&Locations"));
    loc_menu->addAction(tr("&Create...\tF7"), this, SLOT(OnCreateLocation()), QKeySequence(Qt::Key_F7));
    renameLocAction = new QAction(tr("&Rename...\tF6"), loc_menu);
    renameLocAction->setShortcut(QKeySequence(Qt::Key_F6));
    connect(renameLocAction, SIGNAL(triggered()), this, SLOT(OnRenameLocation()));
    loc_menu->addAction(renameLocAction);
    delLocAction = new QAction(tr("&Delete\tF8"), loc_menu);
    delLocAction->setShortcut(QKeySequence(Qt::Key_F8));
    connect(delLocAction, SIGNAL(triggered()), this, SLOT(OnDeleteLocation()));
    loc_menu->addAction(delLocAction);
    loc_menu->addSeparator();
    loc_menu->addAction(tr("Create folder..."), this, SLOT(OnCreateFolder()));
    renameFoldAction = new QAction(tr("Rename folder..."), loc_menu);
    connect(renameFoldAction, SIGNAL(triggered()), this, SLOT(OnRenameFolder()));
    loc_menu->addAction(renameFoldAction);
    delFoldAction = new QAction(tr("Delete folder"), loc_menu);
    connect(delFoldAction, SIGNAL(triggered()), this, SLOT(OnDeleteFolder()));
    loc_menu->addAction(delFoldAction);
    loc_menu->addSeparator();
//    loc_menu->addAction(tr("&Copy\tCtrl+Shift+C"));
//        loc_menu->addAction(tr("&Paste\tCtrl+Shift+V"));
//        loc_menu->addAction(tr("&Replace\tCtrl+Shift+R"));
//        loc_menu->addAction(tr("P&aste in...\tCtrl+Shift+N"));
//        loc_menu->addAction(tr("C&lear\tCtrl+Shift+D"));
//        loc_menu->addSeparator();
    QMenu *loc_action_sub_menu = new QMenu("&Actions");
    newActAction = new QAction(tr("&Create...\tAlt+F7"), loc_action_sub_menu);
    newActAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F7));
    connect(newActAction, SIGNAL(triggered()), this, SLOT(OnAddAction()));
    loc_action_sub_menu->addAction(newActAction);
    renameActAction = new QAction(tr("&Rename...\tAlt+F6"), loc_action_sub_menu);
    renameActAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F6));
    connect(renameActAction, SIGNAL(triggered()), this, SLOT(OnRenAction()));
    loc_action_sub_menu->addAction(renameActAction);
    delActAction = new QAction(tr("&Delete\tAlt+F8"), loc_action_sub_menu);
    delActAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F8));
    connect(delActAction, SIGNAL(triggered()), this, SLOT(OnDelAction()));
    loc_action_sub_menu->addAction(delActAction);
    loc_action_sub_menu->addSeparator();
    delAllActAction = new QAction(tr("D&elete all\tAlt+F10"), loc_action_sub_menu);
    delAllActAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F10));
    connect(delAllActAction, SIGNAL(triggered()), this, SLOT(OnDelAllActions()));
    loc_action_sub_menu->addAction(delAllActAction);
    loc_menu->addMenu(loc_action_sub_menu);
//        loc_menu->addSeparator();
//        loc_menu->addAction(tr("So&rt ascending\tCtrl+Shift+O"));
//        loc_menu->addAction(tr("Sor&t descending\tCtrl+Shift+P"));
//        loc_menu->addSeparator();
//        loc_menu->addAction(tr("G&o to selected location\tCtrl+G"));

//        QMenu *text_menu = menuBar()->addMenu(tr("&Text"));
//        text_menu->addAction(QIcon(":/menu/undo"), tr("&Undo\tCtrl+Z"));
//        text_menu->addAction(QIcon(":/menu/redo"), tr("&Redo\tCtrl+Y"));
//        text_menu->addSeparator();
//        text_menu->addAction(QIcon(":/menu/text_cut"), tr("&Cut\tCtrl+X"));
//        text_menu->addAction(QIcon(":/menu/text_copy"), tr("C&opy\tCtrl+C"));
//        text_menu->addAction(QIcon(":/menu/text_paste"), tr("&Paste\tCtrl+V"));
//        text_menu->addAction(QIcon(":/menu/text_delete"), tr("&Delete\tCtrl+D"));
//        text_menu->addSeparator();
//        text_menu->addAction(tr("S&elect all\tCtrl+A"));

//        QMenu *view_menu = menuBar()->addMenu(tr("&View"));
//        QMenu *list_controls = new QMenu(tr("&Windows list"));
//        list_controls->addAction(tr("&Toolbar"));
//        list_controls->addAction(tr("&Locations list"));
//        list_controls->addAction(tr("&Statusbar"));
//        view_menu->addMenu(list_controls);
//        view_menu->addSeparator();
//        view_menu->addAction(tr("&Close all tabs\tCtrl+Alt+F4"));
//        view_menu->addAction(tr("Close all tabs &except current"));
//        view_menu->addAction(tr("Close c&urrent tab\tCtrl+F4"));
//        view_menu->addSeparator();
//        view_menu->addAction(tr("Pin/Unpin &tab"));
//        view_menu->addSeparator();
//        view_menu->addAction(tr("Show/Hide location's &description\tCtrl+Alt+D"));
//        view_menu->addAction(tr("Show/Hide location's &actions\tCtrl+Alt+A"));

    QMenu *help_menu = menuBar()->addMenu(tr("&Help"));
//        help_menu->addAction(QIcon(":/menu/help"), tr("&Help\tF1"));
//        help_menu->addAction(QIcon(":/menu/help_search"), tr("Help by &keyword\tCtrl+F1"));
//        help_menu->addSeparator();
    help_menu->addAction(tr("&About..."), this, SLOT(OnAbout()));
}

void MainWindow::CreateToolBar()
{
    _toolbar = new MainToolBar(tr("ToolBar"), this, _controls);
    addToolBar(_toolbar);
}

void MainWindow::CreateDockWindows()
{
    QDockWidget* dock = new QDockWidget(tr("Locations"), this);
    _locListBox = new LocationsListBox(this, _controls);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(_locListBox);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void MainWindow::CreateStatusBar()
{
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

void MainWindow::OnLoadGame()
{
    // Задолбал диалог открытия, открытый в директории проекта!
    QString lastPath = QFileInfo(_controls->GetSettings()->GetLastGamePath()).absoluteDir().absolutePath();

    QFileDialog *dlg = new QFileDialog(this);
    QString filename = dlg->getOpenFileName(this,                     // parent
                                            "",                       // caption
                                            lastPath,                       // dir
                                            "QSP games (*.qsp *.gam)" // filter
                                            );
    if (!filename.isEmpty())
    {
        if (_controls->LoadGame(filename))
            UpdateTitle();
            Update();
    }
}

void MainWindow::OnSaveGame()
{
    if (_controls->IsCanSaveGame())
    {
        if (!_controls->SaveGameWithCheck()) OnSaveGameAs();
    }
}

void MainWindow::OnSaveGameAs()
{
    if (_controls->IsCanSaveGame())
    {
        bool ok;
        QFileDialog *dlg = new QFileDialog(this);
        QString filename = dlg->getSaveFileName(this,                     // parent
                                                "",                       // caption
                                                "",                       // dir
                                                "QSP games (*.qsp *.gam)" // filter
                                                );
        if (!filename.isEmpty())
        {
            QString password = QInputDialog::getText(this, QInputDialog::tr("Game password"),
               QInputDialog::tr("Input password:"), QLineEdit::Password,
                "", &ok);
            if (!ok  || password.isEmpty())
            {
                password = QString::fromWCharArray(QGEN_PASSWD);
            }
            if (_controls->SaveGame(filename, password))
                UpdateTitle();
            else
                _controls->ShowMessage(QGEN_MSG_CANTSAVEGAME);
        }
    }
}

bool MainWindow::QuestChange()
{
    if (!_controls->IsGameSaved() && _controls->IsCanSaveGame())
    {
        QMessageBox *dlg = new QMessageBox(this);
        dlg->setWindowTitle(tr("File was changed"));
        dlg->setText(tr("Save game file?"));
        dlg->setStandardButtons(QMessageBox::Ok | QMessageBox::No);
        switch (dlg->exec())
        {
        case QMessageBox::Ok:
            OnSaveGame();
            return true;
        case QMessageBox::No:
            return true;
        }
        return false;
    }
    return true;
}

void MainWindow::UpdateTitle()
{
    QString title;
    if (_controls->IsGameSaved())
        title = QString("%1 - %2").arg(QDir::toNativeSeparators(_controls->GetGamePath()), QString(QGEN_TITLE));
    else
        title = QString("* %1 - %2").arg(QDir::toNativeSeparators(_controls->GetGamePath()), QString(QGEN_TITLE));
    setWindowTitle(title);
}

void MainWindow::Init(QString filename)
{
    if (_controls->LoadGame(filename))
    {
        UpdateTitle();
        Update();
    }
}

void MainWindow::OnInformationQuest()
{
    QMessageBox *info = new QMessageBox(this);
    info->information(this, tr("Game statistics"), _controls->GetGameInfo());
}

void MainWindow::OnFindDialog()
{
    if (!_findDlg)
    {
        _findDlg = new SearchDialog(_controls, tr("Find / Replace"), this);
        _controls->InitSearchData();
    }
     _findDlg->Show(true);
}

void MainWindow::OnNewGame()
{
    if (QuestChange())
    {
        _controls->NewGame();
        UpdateTitle();
        Update();
    }
}

void MainWindow::OnCreateLocation()
{
    _controls->AddLocation();
    Update();
}

void MainWindow::OnRenameLocation()
{
    _controls->RenameSelectedLocation();
}

void MainWindow::OnDeleteLocation()
{
    _controls->DeleteSelectedLocation();
    Update();
}

void MainWindow::OnCreateFolder()
{
    _controls->AddFolder();
}

void MainWindow::OnRenameFolder()
{
    _controls->RenameSelectedFolder();
}

void MainWindow::OnDeleteFolder()
{
    _controls->DeleteSelectedFolder();
}

void MainWindow::OnAddAction()
{
    _controls->AddActionOnSelectedLoc();
    Update();
}

void MainWindow::OnRenAction()
{
    _controls->RenameSelectedAction();
}

void MainWindow::OnDelAction()
{
    _controls->DeleteSelectedAction();
    Update();
}

void MainWindow::OnDelAllActions()
{
    _controls->DeleteAllActions();
    Update();
}

void MainWindow::OnAbout()
{
    QPixmap icon = QPixmap(":/about/logo");
    QString version(QString::fromWCharArray(QGEN_VER));
    QString guiCompiledDate(tr(__DATE__) + tr(", ") + tr(__TIME__));
    QMessageBox *dlg = new QMessageBox(QMessageBox::NoIcon, tr("About..."), tr(""), QMessageBox::Ok, this);
    dlg->setIconPixmap(icon);
    QString text = (tr("<h2>QGen</h2>"
        "<p>QSP game editor"));
    text += tr("<p>Version: %1<br/>Compiled: %2").arg(version, guiCompiledDate);
    text += tr("<p><a href=\"http://qsp.su\">http://qsp.su</a>");
    text += tr("<p>Developers:<br/>"
        "rrock.ru [rrock.ru@gmail.com]<br/>"
        "Nex [nex@otaku.ru]<br/>");
    dlg->setText(text);
    dlg->exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QuestChange())
    {
        //SaveLayout();
        QMainWindow::closeEvent(event);
    }
}

void MainWindow::Update()
{
    _toolbar->Update();

    bool isCanPlay = !_controls->GetContainer()->IsEmpty();
    bool isLocSelected = _controls->GetSelectedLocationIndex() >= 0;
    bool isFoldSelected = _controls->GetSelectedFolderIndex() >= 0;
    bool isActions = !_controls->IsActionsOnSelectedLocEmpty();

    saveGameAction->setEnabled(isCanPlay);
    saveAsGameAction->setEnabled(isCanPlay);
    renameLocAction->setEnabled(isLocSelected);
    delLocAction->setEnabled(isLocSelected);
    renameFoldAction->setEnabled(isFoldSelected);
    delFoldAction->setEnabled(isFoldSelected);
    newActAction->setEnabled(isLocSelected);
    renameActAction->setEnabled(isActions);
    delActAction->setEnabled(isActions);
    delAllActAction->setEnabled(isActions);
}

void MainWindow::OnRename()
{
    if (_controls->GetSelectionCount() > 1)
        return;
    if (_controls->GetSelectedLocationIndex() >= 0)
        OnRenameLocation();
    else
        OnRenameFolder();
}

void MainWindow::OnDelete()
{
    if (_controls->GetSelectionCount() > 1)
    {
        _controls->DeleteSelectedItems();
        return;
    }
    if (_controls->GetSelectedLocationIndex() >= 0)
        OnDeleteLocation();
    else
        OnDeleteFolder();
}
