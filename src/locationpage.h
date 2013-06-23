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

#ifndef _LOCATION_PAGE_
#define _LOCATION_PAGE_

#include "locationdesc.h"
#include "locationcode.h"
#include "locationactions.h"

class LocationPage :
    public QWidget,
    public ILocationPage
{
public:
    LocationPage(QWidget *parent, IControls *controls);

    void SetLocationIndex(size_t locIndex);
    size_t GetLocationIndex();

    void LoadPage();
    void SavePage();

    void ExpandCollapseAll(bool isExpanded);

    void SelectAction(size_t actIndex);
    size_t AddAction(const QString& name);
    long GetSelectedAction();
    void RenameAction(size_t actIndex, const QString& name);
    void DeleteAction(size_t actIndex);
    void MoveActionTo( size_t actIndex, size_t moveTo );

    void SetFocusOnActionCode();

    void SelectLocDescString( long startPos, long lastPos );
    void SelectLocCodeString( long startPos, long lastPos );
    void SelectPicturePathString( long startPos, long lastPos );
    void SelectActionCodeString( long startPos, long lastPos);

    void ReplaceLocDescString(long start, long end, const QString & str);
    void ReplaceLocCodeString(long start, long end, const QString & str);
    void ReplacePicturePathString(long start, long end, const QString & str);
    void ReplaceActionCodeString(long start, long end, const QString & str);


private:
    IControls    *_controls;

    int            _locIndex;
    LocationDesc *_locDesc;
    LocationCode *_locCode;
    LocationActions *_locActs;
};

#endif // _LOCATION_PAGE_
