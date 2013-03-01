#include "stdafx.h"
#include "locationcode.h"

namespace Ui
{
	LocationCode::LocationCode() : QWidget()
	{
		QVBoxLayout *vBox = new QVBoxLayout;
		vBox->addWidget(new QLabel(tr("Execute on  visit")));
		vBox->addWidget(new QTextEdit);

		setLayout(vBox);
	}
}
