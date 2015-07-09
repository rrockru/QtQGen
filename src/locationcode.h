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

#ifndef _LOCATION_CODE_
#define _LOCATION_CODE_

#include <QWidget>
#include <QLabel>

#include "icontrols.h"
#include "ilocationpage.h"
#include "syntaxtextbox.h"

class LocationCode :
    public QWidget
{
    Q_OBJECT

public:
    LocationCode(QWidget *parent, ILocationPage *, IControls *controls);

    void LoadCode();
    void SaveCode();

    void SelectString(long startPos, long lastPos);
    void ReplaceString(long start, long end, const QString &str);

    void Update(bool isFromObservable = false);

private:
    QLabel          *_captionLabel;

    SyntaxTextBox *_editor;

    IControls *_controls;
    ILocationPage *_locPage;
};

#endif // _LOCATION_CODE_
