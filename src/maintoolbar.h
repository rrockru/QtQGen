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

#ifndef _MAIN_TOOLBAR_
#define _MAIN_TOOLBAR_

#include <QToolBar>

#include "icontrols.h"
#include "toolbutton.h"

class MainToolBar :
    public QToolBar
{
    Q_OBJECT

public:
    MainToolBar(QString, QWidget *, IControls *);

    void Update(bool isFromObservable = false);

protected:
    void mouseMoveEvent(QMouseEvent* e);
    void leaveEvent(QEvent * event);

private:
    IControls *_controls;

    ToolButton *newLocButton;
    ToolButton *newFoldButton;
    ToolButton *renameButton;
    ToolButton *delButton;
    ToolButton *openButton;
    ToolButton *saveButton;
    ToolButton *saveasButton;
    ToolButton *infoButton;
    ToolButton *searchButton;
    ToolButton *settingsButton;
};

#endif
