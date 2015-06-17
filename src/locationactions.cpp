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

#include "locationactions.h"

LocationActions::LocationActions(QWidget *parent, ILocationPage *locPage, IControls *controls) : QWidget(parent)
{
    _controls = controls;
    _locPage = locPage;
    _actCodeSplitter = new QSplitter(this);

    QHBoxLayout *boxLayout = new QHBoxLayout;
    _actCode = new ActionCode(this, _locPage, _controls);
    _actPanel = new ActionsPanel(this, _locPage, _actCode, _controls);

    QWidget *actCode = new QWidget;
    QVBoxLayout *vBox = new QVBoxLayout;
    _captionLabel = new QLabel(tr("Action code"), this);
    vBox->addWidget(_captionLabel);
    vBox->addWidget(_actCode);
    actCode->setLayout(vBox);

    _actCodeSplitter->addWidget(_actPanel);
    _actCodeSplitter->addWidget(actCode);

    boxLayout->addWidget(_actCodeSplitter);
    setLayout(boxLayout);

    _actCodeSplitter->restoreState(_controls->GetSettings()->GetActCodeSplitState());
    connect(_actCodeSplitter, SIGNAL(splitterMoved(int,int)), this, SLOT(OnSplitterMoved(int,int)));

    setContentsMargins(0, 0, 0, 0);
    boxLayout->setContentsMargins(0, 0, 0, 0);
}

void LocationActions::LoadAllActions()
{
    _actPanel->GetActionsListBox()->LoadAllActions();
    _actPanel->EnableButtons();
}

void LocationActions::SelectActionInList(size_t actIndex)
{
    _actPanel->GetActionsListBox()->setFocus();
    _actPanel->GetActionsListBox()->Select(actIndex);
}

void LocationActions::SaveAction()
{
    _actPanel->GetActionsListBox()->SaveActionData();
}

size_t LocationActions::AddActionToList(const QString &name)
{
    size_t index = _actPanel->GetActionsListBox()->AddAction(name);
    _actPanel->EnableButtons();
    return index;
}

void LocationActions::SetFocusOnActionCode()
{
    _actCode->SetFocusOnActionCode();
}

long LocationActions::GetSelectedAction()
{
    return _actPanel->GetActionsListBox()->GetSelection();
}

void LocationActions::RenameActionInList(size_t index, const QString& name)
{
    _actPanel->GetActionsListBox()->SetString(index, name);
}

void LocationActions::DeleteActionFromList(size_t actIndex)
{
    _actPanel->GetActionsListBox()->DeleteAction(actIndex);
    _actPanel->EnableButtons();
}

void LocationActions::SelectPicturePathString( long startPos, long lastPos )
{
    _actCode->SelectPicturePathString( startPos, lastPos );
}

void LocationActions::SelectActionCodeString( long startPos, long lastPos )
{
    _actCode->SelectCodeString( startPos, lastPos );
}

void LocationActions::ReplacePicturePathString( long start, long end, const QString & str )
{
    _actCode->ReplacePicturePathString(start, end, str);
}

void LocationActions::ReplaceActionCodeString( long start, long end, const QString & str )
{
    _actCode->ReplaceCodeString(start, end, str);
}

void LocationActions::MoveActionTo( size_t actIndex, size_t moveTo )
{
    _actPanel->GetActionsListBox()->MoveItemTo(actIndex, moveTo);
}

void LocationActions::Clear()
{
    _actPanel->GetActionsListBox()->DeleteAllActions();
    _actPanel->EnableButtons();
}

bool LocationActions::IsActionsListEmpty()
{
    return !_actPanel->GetActionsListBox()->count();
}

void LocationActions::OnSplitterMoved(int pos, int index)
{
    _controls->GetSettings()->SetActCodeSplitState(_actCodeSplitter->saveState());
}

void LocationActions::Update(bool isFromObservable)
{
    _actCodeSplitter->restoreState(_controls->GetSettings()->GetActCodeSplitState());

    if (isFromObservable && _controls->GetSettings()->IsLanguageChanged())
    {
        _captionLabel->setText(tr("Action code"));
    }
}
