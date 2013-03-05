#include "stdafx.h"
#include "SyntaxTextBox.h"

namespace Ui
{
    SyntaxTextBox::SyntaxTextBox(QWidget *parent, IControls *controls, int style) : QPlainTextEdit(parent)
	{
		_controls = controls;
		_style = style;
	}
}
