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

SyntaxTextBox::SyntaxTextBox(QWidget *parent, IControls *controls, int style) : QPlainTextEdit(parent)
{
    _controls = controls;
    _style = style;
    _keywordsStore = _controls->GetKeywordsStore();

    if (_style & SYNTAX_STYLE_COLORED)
    {
        _highlighter = new QspHighlighter(_controls, this->document());

        lineNumberArea = new LineNumberArea(this);
        connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
        connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
        updateLineNumberAreaWidth(0);
    }

    connect(this, SIGNAL(textChanged()), this, SLOT(OnTextChange()));

    setMouseTracking(true);

    Update();
    _controls->GetSettings()->AddObserver(this);
}

void SyntaxTextBox::Update(bool isFromObservable)
{
    setFont(_controls->GetSettings()->GetFont(SYNTAX_BASE));
    setStyleSheet(
                QString("background-color:%1; \
                        color:%2")
                .arg(_controls->GetSettings()->GetTextBackColor().name())
                .arg(_controls->GetSettings()->GetColor(SYNTAX_BASE).name()));
}

void SyntaxTextBox::OnTextChange()
{
    _isChanged = true;
}

void SyntaxTextBox::SetText(QString text)
{
    setPlainText(text);
    _isChanged = false;
}

void SyntaxTextBox::mouseMoveEvent(QMouseEvent *e)
{
    QPlainTextEdit::mouseMoveEvent(e);

    // Далее тупой хак для возможности находить слова, начинающиеся с символа '$'
    QTextCursor tc = cursorForPosition(e->pos());
    tc.select(QTextCursor::BlockUnderCursor);
    QString block = tc.selectedText();
    //

    tc = cursorForPosition(e->pos());
    tc.select(QTextCursor::WordUnderCursor);
    QString str = tc.selectedText();

    if (!str.isEmpty())
    {
        // второй хак
        int pos = block.indexOf(str);

        if ((pos != 0) && (block.at(pos - 1) == '$'))
            str = '$' + str;
        //

        _controls->SetStatusText(_keywordsStore->FindTip(str));
    }
    else
        _controls->CleanStatusText();
}

int SyntaxTextBox::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void SyntaxTextBox::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void SyntaxTextBox::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void SyntaxTextBox::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    if (_style & SYNTAX_STYLE_COLORED)
    {
        QRect cr = contentsRect();
        lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
    }
}

void SyntaxTextBox::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void SyntaxTextBox::SetSelection(long from, long to)
{
    QTextCursor c = textCursor();
    c.setPosition(from);
    c.setPosition(to, QTextCursor::KeepAnchor);
    setTextCursor(c);
}

void SyntaxTextBox::Replace( long from, long to, const QString &str )
{
    QTextCursor c = textCursor();
    c.setPosition(from);
    c.setPosition(to, QTextCursor::KeepAnchor);
    c.insertText(str);
}
