#include "stdafx.h"
#include "locationdesc.h"

#include "IControls.h"

namespace Ui
{
	LocationDesc::LocationDesc(QWidget *parent, ILocationPage *locPage, IControls *controls) : QWidget(parent)
	{
		_controls = controls;
		_locPage = locPage;

		_editor = new QTextEdit(this);

		QVBoxLayout *vBox = new QVBoxLayout;
		vBox->addWidget(new QLabel(tr("Description")));
		vBox->addWidget(_editor);

		setLayout(vBox);

		adjustSize();
	}

	void LocationDesc::LoadDesc()
	{
		_editor->setText(_controls->GetContainer()->GetLocationDesc(_locPage->GetLocationIndex()));
	}
}

