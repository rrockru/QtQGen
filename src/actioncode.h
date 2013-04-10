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

#ifndef _ACTION_CODE_
#define _ACTION_CODE_

#include "SyntaxTextBox.h"
#include "IControls.h"
#include "ilocationpage.h"
#include "actioncode.h"

namespace Ui
{
	class ActionCode :
		public QWidget
	{
        Q_OBJECT

	public:
		ActionCode(QWidget *parent, ILocationPage *locPage, IControls *controls);

		void ClearAction();
		void LoadAction( size_t actIndex );
        void SaveAction( size_t actIndex );

        void SetFocusOnActionCode();

	private:
		SyntaxTextBox *_editor;

		IControls *_controls;
		ILocationPage *_locPage;
		QLineEdit *_pathPicTxtCtrl;
	};

} // namespace Ui

#endif // _ACTION_CODE_
