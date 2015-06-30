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
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(IControls *controls) :
    QMainWindow(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _controls = controls;
    _controls->SetParent(this);

    setMinimumSize(QSize(640, 480));
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
    CreateToolBar();
    CreateStatusBar();

    _controls->GetSettings()->AddObserver(this);

    restoreGeometry(_controls->GetSettings()->GetMainWindowState());

    _autoSaveTimer = new QTimer(this);
    connect(_autoSaveTimer, SIGNAL(timeout()), this, SLOT(OnSaveGame()));
    connect(this, SIGNAL(gameUpdate()), this, SLOT(OnGameUpdate()));

    _findDlg = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateToolBar()
{
    _toolbar = new MainToolBar(tr("ToolBar"), this, _controls);
    addToolBar(_toolbar);
}

void MainWindow::CreateDockWindows()
{
    _dock = new QDockWidget(tr("Locations"), this);
    connect(_dock, SIGNAL(visibilityChanged(bool)), this, SLOT(OnLocVisChanged(bool)));

    _locListBox = new LocationsListBox(this, _controls);
    _dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    _dock->setWidget(_locListBox);
    addDockWidget(Qt::LeftDockWidgetArea, _dock);
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
            emit gameUpdate();
    }
}

void MainWindow::OnSaveGame()
{
    if (_controls->IsCanSaveGame())
    {
        if (!_controls->SaveGameWithCheck())
        {
            OnSaveGameAs();
        }
        else
        {
            UpdateTitle();
        }
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
            QString password = QString::fromWCharArray(QGEN_PASSWD);
            if (_controls->GetSettings()->GetSaveGameWithPassword())
            {
                QString pass = QInputDialog::getText(this, QInputDialog::tr("Game password"),
                   QInputDialog::tr("Input password:"), QLineEdit::Password,
                    "", &ok);
                if (ok && !pass.isEmpty())
                {
                    password = pass;
                }
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
        emit gameUpdate();
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
        emit gameUpdate();
    }
}

void MainWindow::OnPlayGame()
{
    Settings *settings = _controls->GetSettings();
    if (!QFile::exists(settings->GetPlayerPath()))
    {
        QString path = QFileDialog::getOpenFileName(this,
                                                    tr("Path to QSP player"),
                                                    QString(),
                                                    tr("QSP Player (qspgui.exe)"));
        if (!path.isEmpty())
        {
            settings->SetPlayerPath(path);
        }
    }
    OnSaveGame();
    if (_controls->IsGameSaved())
    {
        QProcess::execute(settings->GetPlayerPath(), QStringList() << _controls->GetGamePath());
    }
}

void MainWindow::OnCreateLocation()
{
    _controls->AddLocation();
    emit gameUpdate();
}

void MainWindow::OnRenameLocation()
{
    _controls->RenameSelectedLocation();
}

void MainWindow::OnDeleteLocation()
{
    _controls->DeleteSelectedLocation();
    emit gameUpdate();
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
    emit gameUpdate();
}

void MainWindow::OnRenAction()
{
    _controls->RenameSelectedAction();
}

void MainWindow::OnDelAction()
{
    _controls->DeleteSelectedAction();
    emit gameUpdate();
}

void MainWindow::OnDelAllActions()
{
    _controls->DeleteAllActions();
    emit gameUpdate();
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

void MainWindow::OnGameUpdate()
{
    bool isCanPlay = !_controls->GetContainer()->IsEmpty();
    bool isLocSelected = _controls->GetSelectedLocationIndex() >= 0;
    bool isFoldSelected = _controls->GetSelectedFolderIndex() >= 0;
    bool isActions = !_controls->IsActionsOnSelectedLocEmpty();

    ui->actionSave->setEnabled(isCanPlay);
    ui->actionSaveAs->setEnabled(isCanPlay);
    ui->actionRenameLocation->setEnabled(isLocSelected || isFoldSelected);
    ui->actionDeleteLocation->setEnabled(isLocSelected || isFoldSelected);
    ui->actionCreateAction->setEnabled(isLocSelected);
    ui->actionRenameAction->setEnabled(isActions);
    ui->actionDeleteAction->setEnabled(isActions);
    ui->actionDeleteAllActions->setEnabled(isActions);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QuestChange())
    {
        //SaveLayout();
        QMainWindow::closeEvent(event);
    }
    _controls->GetSettings()->SetMainWindowState(saveGeometry());
}

void MainWindow::Update(bool isFromObservable)
{
    if (isFromObservable && _controls->GetSettings()->IsLanguageChanged())
    {
        ui->retranslateUi(this);
        _dock->setWindowTitle(tr("Locations"));
    }
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
        emit gameUpdate();
        return;
    }
    if (_controls->GetSelectedLocationIndex() >= 0)
        OnDeleteLocation();
    else
        OnDeleteFolder();
}

void MainWindow::OnToggleToolBar(bool visible)
{
    _toolbar->setVisible(visible);
}

void MainWindow::OnToggleLocList(bool visible)
{
    _dock->setVisible(visible);
}

void MainWindow::OnToggleStatusBar(bool visible)
{
    statusBar()->setVisible(visible);
}

void MainWindow::OnLocDescVisible()
{
    _controls->SwitchLocDesc();
}

void MainWindow::OnLocActsVisible()
{
    _controls->SwitchLocActs();
}

void MainWindow::OnLocVisChanged(bool visible)
{
    if (!visible) ui->actionToggleLocationsList->setChecked(false);
}

void MainWindow::OnOptionsDialog()
{
    OptionsDialog dialog(_controls, this);
    dialog.exec();
}

void MainWindow::OnChangeGame()
{
    if (!_controls->IsGameSaved())
    {
        UpdateTitle();
        if (_controls->GetSettings()->GetAutoSave() && _controls->GetSaveState())
        {
            _autoSaveTimer->start(1000 * _controls->GetSettings()->GetAutoSaveInterval());
        }
    }
}
