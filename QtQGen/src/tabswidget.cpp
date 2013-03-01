#include "stdafx.h"
#include "tabswidget.h"

namespace Ui
{
	TabsWidget::TabsWidget() : QTabWidget()
	{
		setTabsClosable(true);
		connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(OnCloseTab(int)));
		//setStyleSheet("QTabBar::close-button {image: url(:/images/tab_close);}");
	}

	void TabsWidget::OnCloseTab(int tab)
	{
		removeTab(tab);
	}
}


