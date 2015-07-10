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

#include "locationdesc.h"

#include "icontrols.h"

LocationDesc::LocationDesc(QWidget *parent, ILocationPage *locPage, IControls *controls) : QWidget(parent)
{
    _controls = controls;
    _locPage = locPage;

    _editor = new SyntaxTextBox(this, _controls, SYNTAX_STYLE_SIMPLE | SYNTAX_STYLE_NOHELPTIPS);

    QVBoxLayout *vBox = new QVBoxLayout;
    _captionLabel = new QLabel(tr("Description"), this);
    vBox->addWidget(_captionLabel);
    vBox->addWidget(_editor);

    setLayout(vBox);

    adjustSize();
}

void LocationDesc::LoadDesc()
{
    _editor->SetText(_controls->GetContainer()->GetLocationDesc(_locPage->GetLocationIndex()));
}

void LocationDesc::SaveDesc()
{
    if (_editor->IsModified())
    {
        _controls->GetContainer()->SetLocationDesc(_locPage->GetLocationIndex(), _editor->GetText());
        _editor->SetModified(false);
    }
}

void LocationDesc::SelectString(long startPos, long lastPos)
{
    _editor->SetSelection( startPos, lastPos );
}

void LocationDesc::ReplaceString( long start, long end, const QString & str )
{
    _editor->Replace(start, end, str);
}

void LocationDesc::Update(bool isFromObservable)
{
    if (isFromObservable && _controls->GetSettings()->IsLanguageChanged())
    {
        _captionLabel->setText(tr("Description"));
    }
}
