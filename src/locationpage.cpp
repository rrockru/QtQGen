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

#include "locationpage.h"

LocationPage::LocationPage(QWidget *parent, IControls *controls) : QWidget(parent)
{
    _controls = controls;
    _settings = controls->GetSettings();

    _locDesc = new LocationDesc(this, this, _controls);
    _locCode = new LocationCode(this, this, _controls);
    _locActs = new LocationActions(this, this, _controls);

    QHBoxLayout *hbox = new QHBoxLayout;

    QString css = "QSplitter::handle { \
            background: gray; \
        } \
        QSplitter::handle:horizontal { \
            width: 2px; \
        } \
        QSplitter::handle:vertical { \
            height: 2px; \
        } \
        QSplitter::handle:pressed { \
            background: black; \
        }";

    _topSplit = new QSplitter(this);
    _topSplit->setStyleSheet(css);

    _vertSplit = new QSplitter(Qt::Vertical, this);
    _vertSplit->setStyleSheet(css);

    _topSplit->addWidget(_locDesc);
    _topSplit->addWidget(_locCode);

    _topSplit->setCollapsible(1, false);

    _vertSplit->addWidget(_topSplit);
    _vertSplit->addWidget(_locActs);

    _vertSplit->setCollapsible(0, false);

    _vertSplit->setStretchFactor(0, 3);
    _vertSplit->setStretchFactor(1, 2);

    hbox->addWidget(_vertSplit);
    setLayout(hbox);

    _oldTopSplitSizes = _topSplit->sizes();
    _oldVertSplitSizes = _vertSplit->sizes();

    _settings->AddObserver(this);
}

void LocationPage::SetLocationIndex(size_t locIndex)
{
    _locIndex = locIndex;
}

size_t LocationPage::GetLocationIndex()
{
    return _locIndex;
}

void LocationPage::LoadPage()
{
    _locDesc->LoadDesc();
    _locCode->LoadCode();
    _locActs->LoadAllActions();
}

void LocationPage::ExpandCollapseAll(bool isExpanded)
{

}

void LocationPage::SelectAction(size_t actIndex)
{
    _locActs->SelectActionInList(actIndex);
}

void LocationPage::SavePage()
{
    _locDesc->SaveDesc();
    _locCode->SaveCode();
    _locActs->SaveAction();
}

void LocationPage::Update(bool isFromObservable)
{
    LocDescVisible(_settings->GetLocDescVisible());
    LocActsVisible(_settings->GetLocActsVisible());
}

size_t LocationPage::AddAction(const QString &name)
{
    return _locActs->AddActionToList(name);
}

void LocationPage::SetFocusOnActionCode()
{
    _locActs->SetFocusOnActionCode();
}

long LocationPage::GetSelectedAction()
{
    return _locActs->GetSelectedAction();
}

void LocationPage::RenameAction(size_t actIndex, const QString& name)
{
    _locActs->RenameActionInList(actIndex, name);
}

void LocationPage::DeleteAction(size_t actIndex)
{
    _locActs->DeleteActionFromList(actIndex);
}

void LocationPage::SelectLocDescString(long startPos, long lastPos)
{
    _locDesc->setFocus();
    _locDesc->SelectString( startPos, lastPos );
}

void LocationPage::SelectLocCodeString(long startPos, long lastPos)
{
    _locCode->setFocus();
    _locCode->SelectString( startPos, lastPos );
}

void LocationPage::SelectPicturePathString( long startPos, long lastPos )
{
    _locActs->SelectPicturePathString( startPos, lastPos );
}

void LocationPage::SelectActionCodeString( long startPos, long lastPos)
{
    _locActs->SelectActionCodeString( startPos, lastPos );
}

void LocationPage::ReplaceLocDescString( long start, long end, const QString & str )
{
    _locDesc->ReplaceString(start, end, str);
}

void LocationPage::ReplaceLocCodeString( long start, long end, const QString & str )
{
    _locCode->ReplaceString(start, end, str);
}

void LocationPage::ReplacePicturePathString( long start, long end, const QString & str )
{
    _locActs->ReplacePicturePathString(start, end, str);
}

void LocationPage::ReplaceActionCodeString( long start, long end, const QString & str )
{
    _locActs->ReplaceActionCodeString(start, end, str);
}

void LocationPage::MoveActionTo( size_t actIndex, size_t moveTo )
{
    _locActs->MoveActionTo(actIndex, moveTo);
}

void LocationPage::DeleteAllActions()
{
    _locActs->Clear();
}

bool LocationPage::IsActionsEmpty()
{
    return _locActs->IsActionsListEmpty();
}

void LocationPage::LocDescVisible(bool visible)
{
    if (visible)
    {
        if (_oldTopSplitSizes.at(0) <= 0)
            _oldTopSplitSizes[0] = 200;
        _topSplit->setSizes(_oldTopSplitSizes);
    }
    else
    {
        _oldTopSplitSizes = _topSplit->sizes();
        QList<int> sizes;
        _topSplit->setSizes(sizes << 0 << _oldTopSplitSizes.at(1));
    }
}

void LocationPage::LocActsVisible(bool visible)
{
    if (visible)
    {
        if (_oldVertSplitSizes.at(1) <= 0)
            _oldVertSplitSizes[1] = 200;
        _vertSplit->setSizes(_oldVertSplitSizes);
    }
    else
    {
        _oldVertSplitSizes = _vertSplit->sizes();
        QList<int> sizes;
        _vertSplit->setSizes(sizes << _oldVertSplitSizes.at(0) << 0);
    }
}


bool LocationPage::IsDescShown()
{
    if (_topSplit->sizes().at(0) > 0)
        return true;
    return false;
}

bool LocationPage::IsActsShown()
{
    if (_vertSplit->sizes().at(1) > 0)
        return true;
    return false;
}
