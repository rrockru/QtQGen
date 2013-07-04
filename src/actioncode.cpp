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

#include "actioncode.h"

ActionCode::ActionCode(QWidget *parent, ILocationPage *locPage, IControls *controls) : QWidget(parent)
{
    _controls = controls;
    _locPage = locPage;

    _editor = new SyntaxTextBox(this, _controls, SYNTAX_STYLE_COLORED);
    _pathPicTxtCtrl = new ImagePathTextBox(this);

    QVBoxLayout *vBox = new QVBoxLayout;

    QHBoxLayout *hBox = new QHBoxLayout;
    hBox->addWidget(_pathPicTxtCtrl);
    hBox->addWidget(new QPushButton(tr("Image...")));
    vBox->addLayout(hBox);

    vBox->addWidget(_editor);

    setLayout(vBox);

    setContentsMargins(0, 0, 0, 0);
    vBox->setContentsMargins(0, 0, 0, 0);
}

void ActionCode::ClearAction()
{
    _pathPicTxtCtrl->clear();
    _editor->clear();
    setEnabled(false);
}

void ActionCode::LoadAction(size_t actIndex)
{
    DataContainer *container = _controls->GetContainer();
    size_t locIndex = _locPage->GetLocationIndex();
    _pathPicTxtCtrl->setText(container->GetActionPicturePath(locIndex, actIndex));
    _editor->SetText(container->GetActionCode(locIndex, actIndex));
    setEnabled(true);
}

void ActionCode::SaveAction(size_t actIndex)
{
    DataContainer *container = _controls->GetContainer();
    size_t locIndex = _locPage->GetLocationIndex();
//        if (_pathPicTxtCtrl->IsModified())
//        {
//            container->SetActionPicturePath(locIndex, actIndex, _pathPicTxtCtrl->GetValue());
//            _pathPicTxtCtrl->SetModified(false);
//        }
    if (_editor->IsModified())
    {
        container->SetActionCode(locIndex, actIndex, _editor->toPlainText());
        _editor->SetModified(false);
    }
}

void ActionCode::SetFocusOnActionCode()
{
    _editor->setFocus();
}

void ActionCode::SelectPicturePathString(long startPos, long lastPos)
{
    _pathPicTxtCtrl->setFocus();
    _pathPicTxtCtrl->SetSelection( startPos, lastPos );
}

void ActionCode::SelectCodeString(long startPos, long lastPos )
{
    _editor->setFocus();
    _editor->SetSelection( startPos, lastPos );
}

void ActionCode::ReplacePicturePathString( long start, long end, const QString & str )
{
    _pathPicTxtCtrl->Replace(start, end, str);
}

void ActionCode::ReplaceCodeString( long start, long end, const QString & str )
{
    _editor->Replace(start, end, str);
}
