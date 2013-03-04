#ifndef _CONTROLS_
#define _CONTROLS_

#include "IControls.h"
#include "mainwindow.h"

#include "game.h"
#include "mergedialog.h"
#include "Settings.h"

namespace Ui
{
	class Controls :
		public IControls
	{
	public:
		Controls(const QString);

		void SetMainWindow(MainWindow *wnd) { _mainWindow = wnd; }
		void SetLocListBox(LocationsListBox *loc) { _locListBox = loc; }
		void SetTabsWisget(TabsWidget *tabs) { _tabsWidget = tabs; }

		void SetStatusText(const QString &text);
		void CleanStatusText();
		bool LoadGame(QString);
		void NewGame();
		bool IsGameSaved();

		void ShowMessage(long errorNum);
		static QString GetMessageDesc(long errorNum);

		QString GetGamePath() const { return _currentGamePath; }

		QWidget *GetParent() { return _mainWindow; }

		Settings *GetSettings() const { return _settings; }
		DataContainer *GetContainer() const { return _container; }

		void UpdateLocationsList();

		LocationPage *ShowLocation(const QString & locName);

		void UpdateLocationIcon(size_t locIndex, bool isOpened);

	private:
		void InitData();

		QMainWindow *_mainWindow;
		LocationsListBox *_locListBox;
		TabsWidget *_tabsWidget;
		DataContainer *_container;
		Settings *_settings;

		QString		_currentPath;
		QString		_currentGamePath;
		QString		_currentGamePass;
	};
} // namespace Ui

#endif // _CONTROLS_

