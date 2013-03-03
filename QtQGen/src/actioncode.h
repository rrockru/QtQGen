#ifndef _ACTION_CODE_
#define _ACTION_CODE_

#include "SyntaxTextBox.h"
#include "IControls.h"

namespace Ui
{
	class ActionCode :
		public QWidget
	{
	public:
		ActionCode(QWidget *parent, IControls *controls);

	private:
		SyntaxTextBox *_editor;

		IControls *_controls;
	};

} // namespace Ui

#endif // _ACTION_CODE_