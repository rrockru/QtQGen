#include "stdafx.h"
#include "actioncode.h"

namespace Ui
{
	ActionCode::ActionCode() : QWidget()
	{
		_editor = new QsciScintilla;
		_editor->SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR, 0);
		_editor->SendScintilla(QsciScintilla::SCI_SETVSCROLLBAR, 0);

		QVBoxLayout *vBox = new QVBoxLayout;
		
		vBox->addWidget(new QLabel(tr("Action code")));
		
		QHBoxLayout *hBox = new QHBoxLayout;		
		hBox->addWidget(new QLineEdit);
		hBox->addWidget(new QPushButton(tr("Image...")));
		vBox->addLayout(hBox);

		vBox->addWidget(_editor);

		setLayout(vBox);
	}
}
