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

#include "SyntaxTextBox.h"

namespace Ui
{
    SyntaxTextBox::SyntaxTextBox(QWidget *parent, IControls *controls, int style) : QsciScintilla(parent)
	{
		_controls = controls;
        _style = style;

        this->setUtf8(true);
        this->setMarginWidth(1, 0);

        if (_style & SYNTAX_STYLE_NOSCROLLBARS)
        {
            this->setVerticalScrollBar(false);
            this->setHorizontalScrollBar(false);
        }
        if (_style & SYNTAX_STYLE_COLORED)
        {
            this->SendScintilla(SCI_SETSCROLLWIDTH, -1);
            this->SendScintilla(SCI_SETSCROLLWIDTHTRACKING, true);

//            SetLexer(wxSTC_LEX_VB);
//            SetKeyWords(0, _keywordsStore->GetWords(STATEMENT));
//            SetKeyWords(1, _keywordsStore->GetWords(EXPRESSION));
//            SetKeyWords(2, _keywordsStore->GetWords(VARIABLE));
            this->SendScintilla(SCI_SETINDENTATIONGUIDES, true);
            if (!(_style & SYNTAX_STYLE_NOMARGINS))
            {
                this->setProperty("fold", "1");
                this->SendScintilla(SCI_SETFOLDFLAGS, SC_FOLDLEVELBASE);

                this->setMarginType(SYNTAX_FOLD_MARGIN, QsciScintilla::SymbolMargin);
                this->setMarginMarkerMask(SYNTAX_FOLD_MARGIN, SC_MASK_FOLDERS);
                this->setMarginWidth(SYNTAX_FOLD_MARGIN, 20);

                this->setMarginType(SYNTAX_NUM_MARGIN, QsciScintilla::NumberMargin);

                this->markerDefine(SC_MARKNUM_FOLDER, SC_MARK_PLUS);
                this->markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
                this->markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
                this->markerDefine(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
                this->markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
                this->markerDefine(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
                this->markerDefine(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);

                this->SendScintilla(SCI_SETFOLDFLAGS, SC_FOLDFLAG_LINEAFTER_CONTRACTED);
                this->SendScintilla(SCI_SETMARGINSENSITIVEN, SYNTAX_FOLD_MARGIN, true);
            }
            this->SendScintilla(SCI_AUTOCSETCHOOSESINGLE, true);
            this->SendScintilla(SCI_AUTOCSETIGNORECASE, true);
            this->SendScintilla(SCI_AUTOCSETDROPRESTOFWORD, true);
        }

        Update();

        connect(this, SIGNAL(textChanged()), this, SLOT(OnTextChange()));
	}

    void SyntaxTextBox::OnTextChange()
    {
        _isChanged = true;
    }

    void SyntaxTextBox::Update(bool isFromObservable)
    {
        Settings *settings = _controls->GetSettings();
        QColor backColor = settings->GetTextBackColor();

        if (_style & SYNTAX_STYLE_COLORED)
        {
            this->setWrapMode(settings->GetWrapLines() ? WrapWord : WrapNone);
            if (!(_style & SYNTAX_STYLE_NOMARGINS))
            {
                this->SendScintilla(SCI_SETFOLDMARGINCOLOUR, true, backColor);
                this->setMarginWidth(SYNTAX_NUM_MARGIN, settings->GetShowLinesNums() ? 40 : 0);
            }
        }
    }
}
