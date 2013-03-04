#include "stdafx.h"
#include "mainwindow.h"
#include "game.h"

namespace Ui
{

	MainWindow::MainWindow(IControls *controls) :
		QMainWindow()
	{
		_controls = controls;

		setMinimumSize(QSize(300, 200));
		setDockNestingEnabled(true);
		resize(850, 650);

		// Set QMainWindow in the center of desktop
		QRect _defRect = geometry();
		_defRect.moveCenter(QApplication::desktop()->availableGeometry().center());
		setGeometry(_defRect);

		setContextMenuPolicy(Qt::NoContextMenu);

		_tabWidget = new TabsWidget(this, _controls);
		setCentralWidget(_tabWidget);

		CreateDockWindows();
		CreateMenuBar();
		CreateToolBar();
		CreateStatusBar();
	}

	void MainWindow::CreateMenuBar()
	{
		QMenu *file_menu = menuBar()->addMenu(tr("&Game"));
		//QAction *tmpAct
		file_menu->addAction(QIcon(":/menu/game_new"), tr("&New\tCtrl+N"));
        file_menu->addAction(QIcon(":/menu/file_open"), tr("&Open...\tCtrl+O"), this, SLOT(OnLoadGame()));
        file_menu->addAction(tr("&Merge game...\tCtrl+M"));
        file_menu->addAction(QIcon(":/menu/file_save"), tr("&Save\tCtrl+S"));
        file_menu->addAction(tr("Save &as...\tCtrl+W"));
		file_menu->addSeparator();
        QMenu *file_sub_exp_menu = new QMenu(tr("&Export"));
        file_sub_exp_menu->addAction(tr("Text file..."));
        file_sub_exp_menu->addAction(tr("Text file in TXT2GAM format..."));
		file_menu->addMenu(file_sub_exp_menu);
        QMenu *file_sub_imp_menu = new QMenu(tr("&Import"));
        file_sub_imp_menu->addAction(tr("Text file in TXT2GAM format..."));
		file_menu->addMenu(file_sub_imp_menu);
		file_menu->addSeparator();
        file_menu->addAction(QIcon(":/menu/exit"), tr("&Exit\tAlt+X"));

        QMenu *util_menu = menuBar()->addMenu(tr("&Utilities"));
        util_menu->addAction(QIcon(":/menu/game_play"), tr("&Run game\tF5"));
        util_menu->addAction(QIcon(":/menu/text_search"), tr("&Find / Replace\tCtrl+F"));
        util_menu->addAction(QIcon(":/menu/game_info"), tr("&Game info\tCtrl+I"));
		util_menu->addSeparator();
        util_menu->addAction(tr("&Settings...\tCtrl+P"));

        QMenu *loc_menu = menuBar()->addMenu(tr("&Locations"));
        loc_menu->addAction(tr("&Create...\tF7"));
        loc_menu->addAction(tr("&Rename...\tF6"));
        loc_menu->addAction(tr("&Delete\tF8"));
		loc_menu->addSeparator();
        loc_menu->addAction(tr("Create folder..."));
		loc_menu->addAction(tr("Rename folder..."));
		loc_menu->addAction(tr("Delete folder"));
		loc_menu->addSeparator();
        loc_menu->addAction(tr("&Copy\tCtrl+Shift+C"));
        loc_menu->addAction(tr("&Paste\tCtrl+Shift+V"));
        loc_menu->addAction(tr("&Replace\tCtrl+Shift+R"));
        loc_menu->addAction(tr("P&aste in...\tCtrl+Shift+N"));
        loc_menu->addAction(tr("C&lear\tCtrl+Shift+D"));
		loc_menu->addSeparator();
        QMenu *loc_action_sub_menu = new QMenu("&Actions");
        loc_action_sub_menu->addAction(tr("&Create...\tAlt+F7"));
        loc_action_sub_menu->addAction(tr("&Rename...\tAlt+F6"));
        loc_action_sub_menu->addAction(tr("&Delete\tAlt+F8"));
		loc_action_sub_menu->addSeparator();
        loc_action_sub_menu->addAction(tr("D&elete all\tAlt+F10"));
		loc_menu->addMenu(loc_action_sub_menu);
		loc_menu->addSeparator();
        loc_menu->addAction(tr("So&rt ascending\tCtrl+Shift+O"));
        loc_menu->addAction(tr("Sor&t descending\tCtrl+Shift+P"));
		loc_menu->addSeparator();
        loc_menu->addAction(tr("G&o to selected location\tCtrl+G"));

        QMenu *text_menu = menuBar()->addMenu(tr("&Text"));
        text_menu->addAction(QIcon(":/menu/undo"), tr("&Undo\tCtrl+Z"));
        text_menu->addAction(QIcon(":/menu/redo"), tr("&Redo\tCtrl+Y"));
		text_menu->addSeparator();
        text_menu->addAction(QIcon(":/menu/text_cut"), tr("&Cut\tCtrl+X"));
        text_menu->addAction(QIcon(":/menu/text_copy"), tr("C&opy\tCtrl+C"));
        text_menu->addAction(QIcon(":/menu/text_paste"), tr("&Paste\tCtrl+V"));
        text_menu->addAction(QIcon(":/menu/text_delete"), tr("&Delete\tCtrl+D"));
		text_menu->addSeparator();
        text_menu->addAction(tr("S&elect all\tCtrl+A"));

        QMenu *view_menu = menuBar()->addMenu(tr("&View"));
        QMenu *list_controls = new QMenu(tr("&Windows list"));
        list_controls->addAction(tr("&Toolbar"));
        list_controls->addAction(tr("&Locations list"));
        list_controls->addAction(tr("&Statusbar"));
		view_menu->addMenu(list_controls);
		view_menu->addSeparator();
        view_menu->addAction(tr("&Close all tabs\tCtrl+Alt+F4"));
        view_menu->addAction(tr("Close all tabs &except current"));
        view_menu->addAction(tr("Close c&urrent tab\tCtrl+F4"));
		view_menu->addSeparator();
        view_menu->addAction(tr("Pin/Unpin &tab"));
		view_menu->addSeparator();
        view_menu->addAction(tr("Show/Hide location's &description\tCtrl+Alt+D"));
        view_menu->addAction(tr("Show/Hide location's &actions\tCtrl+Alt+A"));

        QMenu *help_menu = menuBar()->addMenu(tr("&Help"));
        help_menu->addAction(QIcon(":/menu/help"), tr("&Help\tF1"));
        help_menu->addAction(QIcon(":/menu/help_search"), tr("Help by &keyword\tCtrl+F1"));
		help_menu->addSeparator();
		help_menu->addAction(tr("&About..."));
	}

	void MainWindow::CreateToolBar()
	{
		MainToolBar *_toolbar = new MainToolBar(tr("ToolBar"), this, _controls);
		addToolBar(_toolbar);
	}

	void MainWindow::CreateDockWindows()
	{
        QDockWidget* dock = new QDockWidget(tr("Locations"), this);
		_locListBox = new LocationsListBox(this, _controls);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		dock->setWidget(_locListBox);
		addDockWidget(Qt::LeftDockWidgetArea, dock);
	}

	void MainWindow::CreateStatusBar()
	{
		QStatusBar *statusBar = new QStatusBar(this);
		setStatusBar(statusBar);
	}

	void MainWindow::OnLoadGame()
	{
		QFileDialog *dlg = new QFileDialog(this);
		QString filename = dlg->getOpenFileName(this, NULL,/* _lastPath,*/"", "QSP games (*.qsp;*.gam)|*.qsp;*.gam");
		if (!filename.isEmpty())
		{
			qDebug() << filename;
			if (_controls->LoadGame(filename))
				UpdateTitle();
		}
	}

	void MainWindow::UpdateTitle()
	{
		QString title;
		if (_controls->IsGameSaved())
			title = QString("%1 - %2 %3").arg(_controls->GetGamePath(), QString(QGEN_TITLE), QString::fromWCharArray(QGEN_VER));
		else
			title = QString("* %1 - %2 %3").arg(_controls->GetGamePath(), QString(QGEN_TITLE), QString::fromWCharArray(QGEN_VER));
		setWindowTitle(title);
	}
}
