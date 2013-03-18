#ifndef _LOCATION_DESC_
#define _LOCATION_DESC_

#include "IControls.h"
#include "ilocationpage.h"
#include "SyntaxTextBox.h"

namespace Ui
{

	class LocationDesc :
		public QWidget
	{
        Q_OBJECT

	public:
		LocationDesc(QWidget *, ILocationPage *, IControls *);

		void LoadDesc();
        void SaveDesc();

	private:
		IControls *_controls;
		ILocationPage *_locPage;

		SyntaxTextBox *_editor;
	};

} // namespace Ui

#endif // _LOCATION_DESC_
