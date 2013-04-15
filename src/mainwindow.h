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

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#define QGEN_TITLE "QGen"
#define QSP_CONFIG "qgen.cfg"

#include "locationslistbox.h"
#include "locationpage.h"
#include "tabswidget.h"
#include "IControls.h"
#include "MainToolBar.h"

namespace Ui
{

    enum
    {
        ID_MAINDESC,
        ID_VARSDESC,
        ID_OBJECTS,
        ID_ACTIONS,
        ID_VIEWPIC,
        ID_INPUT,
        ID_TIMER,

        ID_DUMMY
    };

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow(IControls *controls);
		//~MainWindow();

		LocationsListBox *GetLocListBox() const { return _locListBox; }
		TabsWidget *GetTabsWidget() const { return _tabWidget; }

		void UpdateTitle();

	private:
		void CreateMenuBar();
		void CreateToolBar();
		void CreateDockWindows();
		void CreateStatusBar();

        bool QuestChange();

		LocationsListBox		*_locListBox;
		TabsWidget				*_tabWidget;
		IControls				*_controls;

		private slots:
            void OnAbout();

		public slots:
			void OnLoadGame();
            void OnSaveGame();
            void OnSaveGameAs();
            void OnInformationQuest();
            void OnNewGame();
            void OnCreateLocation();
            void OnRenameLocation();
            void OnDeleteLocation();

            void OnAddAction();
            void OnRenAction();
            void OnDelAction();

    protected:
            void closeEvent(QCloseEvent *event);
	};
} // namespace Ui

#endif // _MAIN_WINDOW_H_
