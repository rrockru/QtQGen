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

#include "locationcode.h"

namespace Ui
{
    LocationCode::LocationCode(QWidget *parent, ILocationPage *locPage, IControls *controls) : QWidget(parent)
    {
        _controls = controls;
        _locPage = locPage;

        _editor = new SyntaxTextBox(this, _controls, SYNTAX_STYLE_COLORED);

        QVBoxLayout *vBox = new QVBoxLayout(this);
        vBox->addWidget(new QLabel(tr("Execute on  visit"), this));
        vBox->addWidget(_editor);

        setLayout(vBox);
    }

    void LocationCode::LoadCode()
    {
        _editor->setPlainText(_controls->GetContainer()->GetLocationCode(_locPage->GetLocationIndex()));
    }

    void LocationCode::SaveCode()
    {
        if (_editor->IsModified())
        {
            _controls->GetContainer()->SetLocationCode( _locPage->GetLocationIndex(), _editor->toPlainText() );
            _editor->SetModified(false);
        }
    }
}
