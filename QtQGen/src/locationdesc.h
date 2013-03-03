#ifndef _LOCATION_DESC_
#define _LOCATION_DESC_

#include "IControls.h"
#include "ilocationpage.h"

namespace Ui
{

	class LocationDesc :
		public QWidget
	{
	public:
		LocationDesc(QWidget *, ILocationPage *, IControls *);

		void LoadDesc();

	private:
		IControls *_controls;
		ILocationPage *_locPage;

		QTextEdit *_editor;
	};

} // namespace Ui

#endif // _LOCATION_DESC_