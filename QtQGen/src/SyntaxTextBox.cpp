#include "stdafx.h"
#include "SyntaxTextBox.h"

namespace Ui
{
	SyntaxTextBox::SyntaxTextBox(QWidget *parent, IControls *controls) : QsciScintilla(parent)
	{
		//SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 0);
		//SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 0);
		setUtf8(true);
		setMarginWidth(0, 40);
	}
}


