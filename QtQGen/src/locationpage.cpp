#include "stdafx.h"
#include "locationpage.h"

namespace Ui
{
	LocationPage::LocationPage(QWidget *parent, IControls *controls) : QWidget(parent)
	{
		_controls = controls;

		_locDesc = new LocationDesc(this, this, _controls);
		_locCode = new LocationCode(this, this, _controls);

		QHBoxLayout *hbox = new QHBoxLayout;
		QSplitter *topSplit = new QSplitter;
		QSplitter *bottomSplit = new QSplitter;
		QSplitter *vertSplit = new QSplitter(Qt::Vertical);

		topSplit->addWidget(_locDesc);
		topSplit->addWidget(_locCode);

		bottomSplit->addWidget(new ActionsList);
		bottomSplit->addWidget(new ActionCode(this, _controls));

		vertSplit->addWidget(topSplit);
		vertSplit->addWidget(bottomSplit);

		hbox->addWidget(vertSplit);
		setLayout(hbox);
	}

	void LocationPage::SetLocationIndex(size_t locIndex)
	{
		_locIndex = locIndex;
	}

	size_t LocationPage::GetLocationIndex()
	{
		return _locIndex;
	}

	void LocationPage::LoadPage()
	{
		_locDesc->LoadDesc();
		_locCode->LoadCode();
		//_locActs->LoadAllActions();
	}

	void LocationPage::ExpandCollapseAll(bool isExpanded)
	{

	}
}