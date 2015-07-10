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
#include "game.h"

SyntaxTextBox::SyntaxTextBox(QWidget *parent, IControls *controls, int style)
    : QsciScintilla(parent)
{
    _controls = controls;
    _style = style;
    _keywordsStore = _controls->GetKeywordsStore();

    setEolMode(EolUnix);
    setWrapMode(WrapWord);
    setMarginWidth(1, 0);

    if (_style & SYNTAX_STYLE_NOSCROLLBARS)
    {
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    if (_style & SYNTAX_STYLE_COLORED)
    {
        _lex = new QSPLexer(_controls, this);
        setLexer(_lex);
    }

    connect(this, SIGNAL(textChanged()), _controls->GetParent(), SLOT(OnChangeGame()));

    Update();
    _controls->GetSettings()->AddObserver(this);
}

void SyntaxTextBox::Update(bool isFromObservable)
{
    Settings *settings = _controls->GetSettings();
    QColor backColor = settings->GetTextBackColor();
    setCaretForegroundColor((backColor.blue() << 16 | backColor.green() << 8
                             | backColor.red()) ^ 0xFFFFFF);
    setColor(settings->GetColor(SYNTAX_BASE));
    setPaper(settings->GetTextBackColor());
    setFont(settings->GetFont(SYNTAX_BASE));

    if (_style & SYNTAX_STYLE_COLORED)
    {
        _lex->setPaper(settings->GetTextBackColor(), 0);
        _lex->setDefaultPaper(settings->GetTextBackColor());
        _lex->setDefaultColor(settings->GetColor(SYNTAX_BASE));
    }

}

void SyntaxTextBox::setValue(QString text)
{
    setText(text);
    setModified(false);
}

void SyntaxTextBox::SetSelection(long from, long to)
{

}

void SyntaxTextBox::Replace( long from, long to, const QString &str )
{

}

int SyntaxTextBox::charIndexFromPos(int fromPos, int pos)
{
    int index = 0;
    while (pos != fromPos)
    {
        pos = positionBefore(pos);
        ++index;
    }
    return index;
}

int SyntaxTextBox::positionBefore(int pos)
{
    return SendScintilla(SCI_POSITIONBEFORE, pos);
}

int SyntaxTextBox::positionFromPoint(QPoint const &p)
{
    return SendScintilla(SCI_POSITIONFROMPOINTCLOSE, p.x(), p.y());
}

QString SyntaxTextBox::wordFromPosition(int pos)
{
    QString str;
    int beginPos, lastPos, realPos, lineInd;
    lineIndexFromPosition(pos, &lineInd, &realPos);
    QString lineStr = text(lineInd).trimmed();
    if (!lineStr.isEmpty())
    {
        if (realPos >= lineStr.length())
            realPos = lineStr.length() - 1;
        beginPos = realPos;
        lastPos = realPos;
        while (beginPos >= 0)
            if (QString(QGEN_DELIMS).indexOf(lineStr.at(beginPos)) != -1)
                break;
            else
                --beginPos;
        while (lastPos < lineStr.length())
            if (QString(QGEN_DELIMS).indexOf(lineStr.at(lastPos)) != -1)
                break;
            else
                ++lastPos;
        if (lastPos > beginPos)
            str = lineStr.mid(beginPos + 1, lastPos - beginPos - 1);
    }

    return str;
}

void SyntaxTextBox::tip(int pos)
{
    QString str = wordFromPosition(pos);
    str = str.toLower();
    if (!str.isEmpty())
        _controls->SetStatusText(_keywordsStore->FindTip(str));
    else
        _controls->CleanStatusText();
}

void SyntaxTextBox::mouseMoveEvent(QMouseEvent *e)
{
    QsciScintilla::mouseMoveEvent(e);

    if (!(_style & SYNTAX_STYLE_NOHELPTIPS))
        tip(positionFromPoint(e->pos()));
}
