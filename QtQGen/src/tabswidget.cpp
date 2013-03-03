#include "stdafx.h"
#include "tabswidget.h"

namespace Ui
{
	TabsWidget::TabsWidget(QWidget *parent, IControls *controls) : QTabWidget(parent)
	{
		_controls = controls;

		setTabsClosable(true);
		connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(OnCloseTab(int)));
		//setStyleSheet("QTabBar::close-button {image: url(:/images/tab_close);}");
	}

	void TabsWidget::OnCloseTab(int tab)
	{
		removeTab(tab);
	}

	void TabsWidget::CloseAll()
	{
		for (int i = count(); i > -1 ; i-- )
		{
			removeTab(i);
		}
	}

	int TabsWidget::FindPageIndex(const QString& pageName)
	{
		for (int i = 0; i < count(); ++i)
			if (pageName == tabText(i)) return (int)i;
		return -1;
	}

	LocationPage *TabsWidget::OpenLocationPage(const QString& namePage, bool isSelect)
	{
		size_t locIndex = _controls->GetContainer()->FindLocationIndex(namePage);
		LocationPage *page = new LocationPage(this, _controls);
		page->SetLocationIndex(locIndex);
		addTab(page, namePage/*, isSelect*/);
		page->LoadPage();
		_controls->UpdateLocationIcon(locIndex, true);
		return page;
	}
}


