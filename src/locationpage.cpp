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

    _locCodeSplit = new QSplitter(this);
    _locCodeSplit->setStyleSheet(css);

    _locActsSplit = new QSplitter(Qt::Vertical, this);
    _locActsSplit->setStyleSheet(css);

    _locCodeSplit->addWidget(_locDesc);
    _locCodeSplit->addWidget(_locCode);

    _locCodeSplit->setCollapsible(1, false);

    _locActsSplit->addWidget(_locCodeSplit);
    _locActsSplit->addWidget(_locActs);

    _locActsSplit->setCollapsible(0, false);

    _locActsSplit->setStretchFactor(0, 3);
    _locActsSplit->setStretchFactor(1, 2);

    hbox->addWidget(_locActsSplit);
    setLayout(hbox);

    _locCodeSplit->restoreState(_controls->GetSettings()->GetLocCodeSplitState());
    _locActsSplit->restoreState(_controls->GetSettings()->GetLocActsSplitState());

    connect(_locCodeSplit, SIGNAL(splitterMoved(int,int)), this, SLOT(OnSplitterMoved(int,int)));
    connect(_locActsSplit, SIGNAL(splitterMoved(int,int)), this, SLOT(OnSplitterMoved(int,int)));

    _oldLocCodeSplitSizes = _locCodeSplit->sizes();
    _oldLocActsSplitSizes = _locActsSplit->sizes();

    Update();

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

    _locCodeSplit->restoreState(_controls->GetSettings()->GetLocCodeSplitState());
    _locActsSplit->restoreState(_controls->GetSettings()->GetLocActsSplitState());
    _locActs->Update();
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
        if (_oldLocCodeSplitSizes.at(0) <= 0)
            _oldLocCodeSplitSizes[0] = 200;
        _locCodeSplit->setSizes(_oldLocCodeSplitSizes);
    }
    else
    {
        _oldLocCodeSplitSizes = _locCodeSplit->sizes();
        QList<int> sizes;
        _locCodeSplit->setSizes(sizes << 0 << _oldLocCodeSplitSizes.at(1));
    }
}

void LocationPage::LocActsVisible(bool visible)
{
    if (visible)
    {
        if (_oldLocActsSplitSizes.at(1) <= 0)
            _oldLocActsSplitSizes[1] = 200;
        _locActsSplit->setSizes(_oldLocActsSplitSizes);
    }
    else
    {
        _oldLocActsSplitSizes = _locActsSplit->sizes();
        QList<int> sizes;
        _locActsSplit->setSizes(sizes << _oldLocActsSplitSizes.at(0) << 0);
    }
}


bool LocationPage::IsDescShown()
{
    if (_locCodeSplit->sizes().at(0) > 0)
        return true;
    return false;
}

bool LocationPage::IsActsShown()
{
    if (_locActsSplit->sizes().at(1) > 0)
        return true;
    return false;
}

void LocationPage::OnSplitterMoved(int pos, int index)
{
    _controls->GetSettings()->SetLocCodeSplitState(_locCodeSplit->saveState());
    _controls->GetSettings()->SetLocActsSplitState(_locActsSplit->saveState());
}
