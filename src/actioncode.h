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
