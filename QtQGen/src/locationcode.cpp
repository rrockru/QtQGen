#include "stdafx.h"
#include "locationcode.h"

namespace Ui
{
	LocationCode::LocationCode() : QWidget()
	{
		_editor = new QsciScintilla;
		_editor->SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 0);
		_editor->SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 0);

		QVBoxLayout *vBox = new QVBoxLayout;
		vBox->addWidget(new QLabel(tr("Execute on  visit")));
		vBox->addWidget(_editor);

		setLayout(vBox);
	}
}
