#include "stdafx.h"
#include "tabswidget.h"

namespace Ui
{
	TabsWidget::TabsWidget(QWidget *parent, IControls *controls) : QTabWidget(parent)
	{
		_controls = controls;

		setTabsClosable(true);
        Update();

		connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(OnCloseTab(int)));
		//setStyleSheet("QTabBar::close-button {image: url(:/images/tab_close);}");
	}

	void TabsWidget::OnCloseTab(int tab)
	{
        DeletePage(tab);
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
		if (isSelect)
		{
			setCurrentWidget(page);
		}
		return page;
	}

    void TabsWidget::SaveOpenedPages()
    {
        for (int i = 0; i < count(); ++i)
            ((LocationPage *)widget(i))->SavePage();
    }

    void TabsWidget::Update(bool isFromObservable)
    {
        Settings *settings = _controls->GetSettings();
        QColor backColor= settings->GetBaseBackColor();
        setStyleSheet(QString::fromUtf8("background-color: rgb(%1, %2, %3);").arg(backColor.red()).arg(backColor.green()).arg(backColor.blue()));
    }

    void TabsWidget::DeletePage(size_t page)
    {
        NotifyClosePage(page);
        removeTab(page);
    }

    void TabsWidget::NotifyClosePage( int index )
    {
        LocationPage *page = (LocationPage *)widget(index);
        page->SavePage();
        _controls->UpdateLocationIcon(page->GetLocationIndex(), false);
    }
}


