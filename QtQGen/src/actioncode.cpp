#include "stdafx.h"
#include "actioncode.h"

namespace Ui
{
	ActionCode::ActionCode() : QWidget()
	{
		QVBoxLayout *vBox = new QVBoxLayout;
		vBox->addWidget(new QLabel(tr("Action code")));
		vBox->addWidget(new QLineEdit);
		vBox->addWidget(new QTextEdit);

		setLayout(vBox);
	}
}
