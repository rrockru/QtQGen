#ifndef _ACTION_CODE_
#define _ACTION_CODE_

#include <Qsci/qsciscintilla.h>

namespace Ui
{
	class ActionCode :
		public QWidget
	{
	public:
		ActionCode(void);

	private:
		QsciScintilla *_editor;
	};

} // namespace Ui

#endif // _ACTION_CODE_