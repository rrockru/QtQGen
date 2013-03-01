#include "stdafx.h"
#include "locationpage.h"

namespace Ui
{
	LocationPage::LocationPage() : QWidget()
	{
		QHBoxLayout *hbox = new QHBoxLayout;
		QSplitter *topSplit = new QSplitter;
		QSplitter *bottomSplit = new QSplitter;
		QSplitter *vertSplit = new QSplitter(Qt::Vertical);

		topSplit->addWidget(new LocationDesc);
		topSplit->addWidget(new LocationCode);

		bottomSplit->addWidget(new ActionsList);
		bottomSplit->addWidget(new ActionCode);

		vertSplit->addWidget(topSplit);
		vertSplit->addWidget(bottomSplit);

		hbox->addWidget(vertSplit);
		setLayout(hbox);
	}
}