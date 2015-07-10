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

#include "syntaxtextbox.h"

SyntaxTextBox::SyntaxTextBox(QWidget *parent, IControls *controls, int style)
    : QsciScintilla(parent)
{
    _controls = controls;
    _style = style;
    _keywordsStore = _controls->GetKeywordsStore();
    _isChanged = false;

    if (_style & SYNTAX_STYLE_COLORED)
    {
    }

    Update();
    _controls->GetSettings()->AddObserver(this);
}

void SyntaxTextBox::Update(bool isFromObservable)
{
//    setFont(_controls->GetSettings()->GetFont(SYNTAX_BASE));
//    setStyleSheet(
//                QString("background-color:%1; \
//                        color:%2")
//                .arg(_controls->GetSettings()->GetTextBackColor().name())
//                .arg(_controls->GetSettings()->GetColor(SYNTAX_BASE).name()));
}

QString SyntaxTextBox::GetText()
{
    _isChanged = false;
    return "";
}

void SyntaxTextBox::SetText(QString text)
{

}

void SyntaxTextBox::SetSelection(long from, long to)
{

}

void SyntaxTextBox::Replace( long from, long to, const QString &str )
{

}
