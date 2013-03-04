#include "stdafx.h"
#include "locationpage.h"

namespace Ui
{
	LocationPage::LocationPage(QWidget *parent, IControls *controls) : QWidget(parent)
	{
		_controls = controls;

		_locDesc = new LocationDesc(this, this, _controls);
		_locCode = new LocationCode(this, this, _controls);
		_locActs = new LocationActions(this, this, _controls);

		QHBoxLayout *hbox = new QHBoxLayout;
		QSplitter *topSplit = new QSplitter(this);
		
		QSplitter *vertSplit = new QSplitter(Qt::Vertical, this);

		topSplit->addWidget(_locDesc);
		topSplit->addWidget(_locCode);
		

		vertSplit->addWidget(topSplit);
		vertSplit->addWidget(_locActs);

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
		_locActs->LoadAllActions();
	}

	void LocationPage::ExpandCollapseAll(bool isExpanded)
	{

	}
}