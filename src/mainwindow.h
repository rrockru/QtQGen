#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#define QGEN_TITLE "Quest Generator"
#define QSP_CONFIG "qgen.cfg"

#include "locationslistbox.h"
#include "locationpage.h"
#include "tabswidget.h"
#include "IControls.h"
#include "MainToolBar.h"

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

namespace Ui
{

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

		public slots:
			void OnLoadGame();
            void OnSaveGame();
            void OnSaveGameAs();
            void OnInformationQuest();
            void OnNewGame();
	};
} // namespace Ui

#endif // _MAIN_WINDOW_H_
