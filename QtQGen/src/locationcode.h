#ifndef _LOCATION_CODE_
#define _LOCATION_CODE_

#include <Qsci/qsciscintilla.h>

namespace Ui
{
	class LocationCode :
		public QWidget
	{
	public:
		LocationCode();

	private:
		QsciScintilla *_editor;
	};
} // namespace Ui

#endif // _LOCATION_CODE_