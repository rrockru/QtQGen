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
	public:
		ActionsPanel(QWidget *parent, ILocationPage *locPage, ActionCode *actCode, IControls *controls);

		ActionsList *GetActionsListBox() { return _actsList; };
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

