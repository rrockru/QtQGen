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

        QsciLexerCPP * lexCpp = new QsciLexerCPP(this);
        this->setLexer(lexCpp);

        this->setUtf8(true);
        this->setMarginWidth(1, 0);

        if (_style & SYNTAX_STYLE_NOSCROLLBARS)
        {
            this->setVerticalScrollBar(false);
            this->setHorizontalScrollBar(false);
        }
        if (_style & SYNTAX_STYLE_COLORED)
        {
//            SetScrollWidth(-1);
//            SetScrollWidthTracking(true);

//            SetLexer(wxSTC_LEX_VB);
//            SetKeyWords(0, _keywordsStore->GetWords(STATEMENT));
//            SetKeyWords(1, _keywordsStore->GetWords(EXPRESSION));
//            SetKeyWords(2, _keywordsStore->GetWords(VARIABLE));
//            //	SetViewEOL(true);
//            //	SetViewWhiteSpace(true);
//            SetIndentationGuides(true);
            if (!(_style & SYNTAX_STYLE_NOMARGINS))
            {
//                SetProperty(wxT("fold"), wxT("1"));
//                //	SetProperty(wxT("fold.compact"), wxT("0"));
//                //	SetProperty(wxT("fold.comment"), wxT("1"));
//                SetFoldFlags(wxSTC_FOLDLEVELBASE);

                this->setMarginType(SYNTAX_FOLD_MARGIN, QsciScintilla::SymbolMargin);
                this->setMarginMarkerMask(SYNTAX_FOLD_MARGIN, SC_MASK_FOLDERS);
                this->setMarginWidth(SYNTAX_FOLD_MARGIN, 20);

                this->setMarginType(SYNTAX_NUM_MARGIN, QsciScintilla::NumberMargin);

//                MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_PLUS);
//                MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_MINUS);
//                MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_EMPTY);
//                MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
//                MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_EMPTY);
//                MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY);
//                MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY);

//                SetFoldFlags(wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

//                this->setMarginSensitive(SYNTAX_FOLD_MARGIN, true);
            }
//            AutoCompSetChooseSingle(true);
//            AutoCompSetIgnoreCase(true);
//            AutoCompSetDropRestOfWord(true);
        }

        connect(this, SIGNAL(textChanged()), this, SLOT(OnTextChange()));
	}

    void SyntaxTextBox::OnTextChange()
    {
        _isChanged = true;
    }
}
