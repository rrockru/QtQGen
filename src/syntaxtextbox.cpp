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
    _isChanged = false;

    if (_style & SYNTAX_STYLE_COLORED)
    {
        _highlighter = new QspHighlighter(_controls, this->document());

        lineNumberArea = new LineNumberArea(this);
        connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
        connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
        updateLineNumberAreaWidth(0);

        QStringList completionList = _controls->GetKeywordsStore()->GetWordsForCompletion();

        _completer = new QCompleter(completionList, this);
        _completer->setWidget(this);
        _completer->setCompletionMode(QCompleter::PopupCompletion);
        _completer->setCaseSensitivity(Qt::CaseInsensitive);
        connect(_completer, SIGNAL(activated(QString)), this, SLOT(OnInsertCompletion(QString)));
    }

    connect(this, SIGNAL(textChanged()), this, SLOT(OnTextChange()));
    connect(this, SIGNAL(textChanged()), _controls->GetParent(), SLOT(OnChangeGame()));

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
    if (_originalText != toPlainText())
    {
        _isChanged = true;
    }
}

QString SyntaxTextBox::GetText()
{
    _isChanged = false;
    _originalText = toPlainText();
    return _originalText;
}

void SyntaxTextBox::SetText(QString text)
{
    _originalText = text;
    setPlainText(text);
}

void SyntaxTextBox::mouseMoveEvent(QMouseEvent *e)
{
    QPlainTextEdit::mouseMoveEvent(e);

    if (_style & SYNTAX_STYLE_COLORED)
    {
        QString str = textUnderCursor(e);

        if (!str.isEmpty())
        {
            _controls->SetStatusText(_keywordsStore->FindTip(str));
        }
        else
            _controls->CleanStatusText();
    }
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

void SyntaxTextBox::OnInsertCompletion(QString text)
{
    if (_completer->widget() != this)
    {
        return;
    }

    QTextCursor tc = textCursor();
    tc.movePosition(QTextCursor::Left);
    selectTextWithSpec(&tc);
    tc.deleteChar();
    tc.insertText(text);
    setTextCursor(tc);
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

void SyntaxTextBox::keyPressEvent(QKeyEvent *e)
{
    if (_completer && _completer->popup()->isVisible())
    {
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
        case Qt::Key_Escape:
            _isShortCut = false;
            e->ignore();
            return;
        default:
            break;
        }
    }

    bool isShortCut;
    if (!_isShortCut)
    {
        isShortCut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space);
        _isShortCut = isShortCut;
    }
    if (!_completer || !isShortCut)
    {
        QPlainTextEdit::keyPressEvent(e);
    }

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!_completer || (ctrlOrShift && e->text().isEmpty()))
    {
         return;
    }

    if (_style & SYNTAX_STYLE_COLORED)
    {
        QString completionPrefix = textUnderCursor();
        if (_controls->GetKeywordsStore()->ContainsPrefix('$' + completionPrefix))
        {
            completionPrefix = '$' + completionPrefix;
        }
        bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
        static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
        if (!_isShortCut && (hasModifier || e->text().isEmpty()
                            || completionPrefix.length() < 3 || eow.contains(e->text().right(1))))
        {
            _completer->popup()->hide();
            return;
        }

        if (completionPrefix != _completer->completionPrefix())
        {
            _completer->setCompletionPrefix(completionPrefix);
            _completer->popup()->setCurrentIndex(_completer->completionModel()->index(0, 0));
        }

        QRect cr = cursorRect();
        cr.setWidth(_completer->popup()->sizeHintForColumn(0)
                    +_completer->popup()->verticalScrollBar()->sizeHint().width());
        _completer->complete(cr);
    }
}

QString SyntaxTextBox::textUnderCursor(QMouseEvent *e)
{
    QTextCursor tc;
    if (e)
    {
        tc = cursorForPosition(e->pos());
    }
    else
    {
        tc = textCursor();
    }
    selectTextWithSpec(&tc);

    return tc.selectedText();
}

void SyntaxTextBox::selectTextWithSpec(QTextCursor *tc)
{
    tc->select(QTextCursor::WordUnderCursor);
    if (!tc->selectedText().isEmpty() && tc->anchor() > 0)
    {
        if (toPlainText().at(tc->anchor() - 1) == '$')
        {
            int pos = tc->position();
            tc->setPosition(tc->anchor() - 1, QTextCursor::MoveAnchor);
            tc->setPosition(pos, QTextCursor::KeepAnchor);
        }
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
