// Copyright (C) 2013
// Shchannikov Dmitry (rrock DOT ru AT gmail DOT com)
// Nex (nex AT otaku DOT ru)
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "tabswidget.h"

TabsWidget::TabsWidget(QWidget *parent, IControls *controls) : QTabWidget(parent)
{
    _controls = controls;

    setTabsClosable(true);
    Update();

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(OnCloseTab(int)));

    _controls->GetSettings()->AddObserver(this);
}

void TabsWidget::OnCloseTab(int tab)
{
    DeletePage(tab);
}

void TabsWidget::CloseAll()
{
    for (int i = count(); i > -1 ; i--)
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
    // TODO
    setStyleSheet(
        QString("QTabWidget::pane {\
            background-color: %1;\
            };")
        .arg(_controls->GetSettings()->GetBaseBackColor().name()));
}

void TabsWidget::DeletePage(size_t page)
{
    NotifyClosePage(page);
    removeTab(page);
}

void TabsWidget::NotifyClosePage(int index)
{
    LocationPage *page = (LocationPage *)widget(index);
    page->SavePage();
    _controls->UpdateLocationIcon(page->GetLocationIndex(), false);
}

LocationPage * TabsWidget::GetPageByLocName(const QString &name)
{
    int idx = FindPageIndex(name);
    return (idx >= 0 ? (LocationPage *)widget(idx) : NULL);
}
