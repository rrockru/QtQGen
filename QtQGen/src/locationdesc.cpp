#include "stdafx.h"
#include "locationdesc.h"

namespace Ui
{
	LocationDesc::LocationDesc() : QWidget()
	{
		QVBoxLayout *vBox = new QVBoxLayout;
		vBox->addWidget(new QLabel(tr("Description")));
		vBox->addWidget(new QTextEdit);

		setLayout(vBox);

		adjustSize();
	}
}

