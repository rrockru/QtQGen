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

#ifndef _TABS_WIDGET_
#define _TABS_WIDGET_

#include "locationpage.h"

namespace Ui
{
    class TabsWidget :
        public QTabWidget
    {
        Q_OBJECT

    public:
        TabsWidget(QWidget *parent, IControls *controls);

        void CloseAll();
        void Update(bool isFromObservable = false);
        int FindPageIndex(const QString& pageName);
        LocationPage *GetPageByLocName( const QString &name );
        LocationPage *OpenLocationPage(const QString& namePage, bool isSelect);
        void SaveOpenedPages();

        void DeletePage(size_t page);
        void NotifyClosePage(int index);

    private:
        IControls *_controls;

        private slots:
            void OnCloseTab(int);
    };
} // namespace Ui

#endif // _TABS_WIDGET_


