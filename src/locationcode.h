#ifndef _LOCATION_CODE_
#define _LOCATION_CODE_

#include "IControls.h"
#include "ilocationpage.h"
#include "SyntaxTextBox.h"

namespace Ui
{
	class LocationCode :
		public QWidget
	{
	public:
		LocationCode(QWidget *parent, ILocationPage *, IControls *controls);

		void LoadCode();

	private:
		SyntaxTextBox *_editor;

		IControls *_controls;
		ILocationPage *_locPage;
	};
} // namespace Ui

#endif // _LOCATION_CODE_