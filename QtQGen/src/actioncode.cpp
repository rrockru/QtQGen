#include "stdafx.h"
#include "actioncode.h"

namespace Ui
{
	ActionCode::ActionCode(QWidget *parent, IControls *controls) : QWidget(parent)
	{
		_controls = controls;

		_editor = new SyntaxTextBox(this, _controls);

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
