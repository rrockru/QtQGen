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

#ifndef _ACTIONS_PANEL_
#define _ACTIONS_PANEL_

#include "IControls.h"
#include "actionslist.h"
#include "actioncode.h"
#include "ilocationpage.h"

namespace Ui
{
    class ActionsPanel :
        public QWidget
    {
        Q_OBJECT

    public:
        ActionsPanel(QWidget *parent, ILocationPage *locPage, ActionCode *actCode, IControls *controls);

        ActionsList *GetActionsListBox() { return _actsList; }
        void EnableButtons();
    private:
        IControls *_controls;
        ActionsList *_actsList;

        QToolButton *newButton;
        QToolButton *renameButton;
        QToolButton *deleteButton;
    };
}

#endif //_ACTIONS_PANEL_

