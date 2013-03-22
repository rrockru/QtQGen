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

#ifndef _SYNTAX_TEXT_BOX_
#define _SYNTAX_TEXT_BOX_

#include <QPlainTextEdit>

#include "IControls.h"

namespace Ui
{
    enum
    {
        SYNTAX_FOLD_MARGIN = 1,
        SYNTAX_NUM_MARGIN
    };

    enum
    {
        SYNTAX_STYLE_SIMPLE =			0,
        SYNTAX_STYLE_COLORED =			1 << 0,
        SYNTAX_STYLE_NOHOTKEYS =		1 << 1,
        SYNTAX_STYLE_SIMPLEMENU =		1 << 2,
        SYNTAX_STYLE_NOSCROLLBARS =	1 << 3,
        SYNTAX_STYLE_NOMARGINS =		1 << 4,
        SYNTAX_STYLE_NOHELPTIPS =		1 << 5
    };

    class SyntaxTextBox :
        public QPlainTextEdit
	{
        Q_OBJECT

	public:
        SyntaxTextBox(QWidget *parent, IControls *controls, int style);

        bool IsModified() { return _isChanged; }
        void SetModified(bool modified) {_isChanged = modified; }

	private:
		IControls *_controls;

		int _style;
        bool _isChanged;

    private slots:
        void OnTextChange();
	};
}

#endif //_SYNTAX_TEXT_BOX_


