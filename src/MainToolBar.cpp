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

#include "maintoolbar.h"

MainToolBar::MainToolBar(QString name, QWidget *parent, IControls *controls) : QToolBar(name, parent)
{
    _controls = controls;
    newLocButton = new ToolButton(QIcon(":/toolbar/location_new"), tr("Create location... (F7)"), this, _controls);
    connect(newLocButton, SIGNAL(triggered()), parent, SLOT(OnCreateLocation()));
    addAction(newLocButton);
    newFoldButton = new ToolButton(QIcon(":/toolbar/folder_new"), tr("Create folder..."), this, _controls);
    connect(newFoldButton, SIGNAL(triggered()), parent, SLOT(OnCreateFolder()));
    addAction(newFoldButton);
    renameButton = new ToolButton(QIcon(":/toolbar/location_rename"), tr("Rename selected folder\\location... (F6)"), this, _controls);
    connect(renameButton, SIGNAL(triggered()), parent, SLOT(OnRename()));
    addAction(renameButton);
    delButton = new ToolButton(QIcon(":/toolbar/location_delete"), tr("Delete selected folder\\location (F8)"), this, _controls);
    connect(delButton, SIGNAL(triggered()), parent, SLOT(OnDelete()));
    addAction(delButton);
    addSeparator();

    openButton = new ToolButton(QIcon(":/toolbar/file_open"), tr("Open game... (Ctrl+O)"), this, _controls);
    connect(openButton, SIGNAL(triggered()), parent, SLOT(OnLoadGame()));
    addAction(openButton);
    saveButton = new ToolButton(QIcon(":/toolbar/file_save"), tr("Save game (Ctrl+S)"), this, _controls);
    connect(saveButton, SIGNAL(triggered()), parent, SLOT(OnSaveGame()));
    addAction(saveButton);
    saveasButton = new ToolButton(QIcon(":/toolbar/file_saveas"), tr("Save game into another file... (Ctrl+W)"), this, _controls);
    connect(saveasButton, SIGNAL(triggered()), parent, SLOT(OnSaveGameAs()));
    addAction(saveasButton);
    addSeparator();

//        ToolButton *playButton = new ToolButton(QIcon(":/toolbar/game_play"), tr("Run game (F5)"), this, _controls);
//        addAction(playButton);
    infoButton = new ToolButton(QIcon(":/toolbar/game_info"), tr("Show game statistics (Ctrl+I)"), this, _controls);
    connect(infoButton, SIGNAL(triggered()), parent, SLOT(OnInformationQuest()));
    addAction(infoButton);
    addSeparator();

//        ToolButton *undoButton = new ToolButton(QIcon(":/toolbar/undo"), tr("Undo (Ctrl+Z)"), this, _controls);
//        addAction(undoButton);
//        ToolButton *redoButton = new ToolButton(QIcon(":/toolbar/redo"), tr("Redo (Ctrl+Y)"), this, _controls);
//        addAction(redoButton);
//        addSeparator();

//        ToolButton *copyButton = new ToolButton(QIcon(":/toolbar/location_copy"), tr("Copy selected location (Ctrl+Shift+C)"), this, _controls);
//        addAction(copyButton);
//        ToolButton *pasteButton = new ToolButton(QIcon(":/toolbar/location_paste"), tr("Paste location (Ctrl+Shift+V)"), this, _controls);
//        addAction(pasteButton);
//        ToolButton *clearButton = new ToolButton(QIcon(":/toolbar/location_clear"), tr("Clear selected location (Ctrl+Shift+D)"), this, _controls);
//        addAction(clearButton);
//        addSeparator();

    searchButton = new ToolButton(QIcon(":/toolbar/text_search"), tr("Find / Replace... (Ctrl+F)"), this, _controls);
    connect(searchButton, SIGNAL(triggered()), parent, SLOT(OnFindDialog()));
    addAction(searchButton);
//        ToolButton *settingsButton = new ToolButton(QIcon(":/toolbar/options"), tr("Settings... (Ctrl+P)"), this, _controls);
//        addAction(settingsButton);

    setMouseTracking(true);
}

void MainToolBar::mouseMoveEvent(QMouseEvent* e)
{
    _controls->CleanStatusText();
}

void MainToolBar::leaveEvent(QEvent * event)
{
    _controls->CleanStatusText();
}

void MainToolBar::Update()
{
    bool isCanPlay = !_controls->GetContainer()->IsEmpty();
    bool isFoldLocSelected = _controls->GetSelectedLocationIndex() >= 0 || _controls->GetSelectedFolderIndex() >= 0;

    renameButton->setEnabled(isFoldLocSelected);
    delButton->setEnabled(isFoldLocSelected);
    saveButton->setEnabled(isCanPlay);
    saveasButton->setEnabled(isCanPlay);
}
