#ifndef _SYNTAX_TEXT_BOX_
#define _SYNTAX_TEXT_BOX_

#include <Qsci/qsciscintilla.h>
#include "IControls.h"

namespace Ui
{
	class SyntaxTextBox :
		public QsciScintilla
	{
	public:
		SyntaxTextBox(QWidget *parent, IControls *controls);
	};
}

#endif //_SYNTAX_TEXT_BOX_


