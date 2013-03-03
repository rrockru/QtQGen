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
		QMenu *file_menu = menuBar()->addMenu(tr("File"));
		//QAction *tmpAct
		file_menu->addAction(QIcon(":/menu/game_new"), tr("New"));
		file_menu->addAction(QIcon(":/menu/file_open"), tr("Open..."), this, SLOT(OnLoadGame()));
		file_menu->addAction(tr("Join game..."));
		file_menu->addAction(QIcon(":/menu/file_save"), tr("Save"));
		file_menu->addAction(tr("Save as..."));
		file_menu->addSeparator();
		QMenu *file_sub_exp_menu = new QMenu(tr("Export"));
		file_sub_exp_menu->addAction(tr("Text file..."));
		file_sub_exp_menu->addAction(tr("Text TXT2GAM..."));
		file_menu->addMenu(file_sub_exp_menu);
		QMenu *file_sub_imp_menu = new QMenu(tr("Import"));
		file_sub_imp_menu->addAction(tr("Import TXT2GAM..."));
		file_menu->addMenu(file_sub_imp_menu);
		file_menu->addSeparator();
		file_menu->addAction(QIcon(":/menu/exit"), tr("Exit"));

		QMenu *util_menu = menuBar()->addMenu(tr("Utils"));
		util_menu->addAction(QIcon(":/menu/game_play"), tr("Run game"));
		util_menu->addAction(QIcon(":/menu/text_search"), tr("Search/Replace"));
		util_menu->addAction(QIcon(":/menu/game_info"), tr("Game info"));
		util_menu->addSeparator();
		util_menu->addAction(tr("Settings..."));

		QMenu *loc_menu = menuBar()->addMenu(tr("Locations"));
		loc_menu->addAction(tr("Create..."));
		loc_menu->addAction(tr("Rename..."));
		loc_menu->addAction(tr("Delete"));
		loc_menu->addSeparator();
		loc_menu->addAction(tr("Create folder..."));
		loc_menu->addAction(tr("Rename folder..."));
		loc_menu->addAction(tr("Delete folder"));
		loc_menu->addSeparator();
		loc_menu->addAction(tr("Copy"));
		loc_menu->addAction(tr("Paste"));
		loc_menu->addAction(tr("Replace"));
		loc_menu->addAction(tr("Paste new..."));
		loc_menu->addAction(tr("Clear"));
		loc_menu->addSeparator();
		QMenu *loc_action_sub_menu = new QMenu("Actions");
		loc_action_sub_menu->addAction(tr("Create..."));
		loc_action_sub_menu->addAction(tr("Rename..."));
		loc_action_sub_menu->addAction(tr("Delete"));
		loc_action_sub_menu->addSeparator();
		loc_action_sub_menu->addAction(tr("Delete all"));
		loc_menu->addMenu(loc_action_sub_menu);
		loc_menu->addSeparator();
		loc_menu->addAction(tr("Sort ASC"));
		loc_menu->addAction(tr("Sort DESC"));
		loc_menu->addSeparator();
		loc_menu->addAction(tr("Jump to location"));

		QMenu *text_menu = menuBar()->addMenu(tr("Text"));
		text_menu->addAction(QIcon(":/menu/undo"), tr("Undo"));
		text_menu->addAction(QIcon(":/menu/redo"), tr("Redo"));
		text_menu->addSeparator();
		text_menu->addAction(QIcon(":/menu/text_cut"), tr("Cut"));
		text_menu->addAction(QIcon(":/menu/text_copy"), tr("Copy"));
		text_menu->addAction(QIcon(":/menu/text_paste"), tr("Paste"));
		text_menu->addAction(QIcon(":/menu/text_delete"), tr("Delete"));
		text_menu->addSeparator();
		text_menu->addAction(tr("Select all"));

		QMenu *view_menu = menuBar()->addMenu(tr("View"));
		QMenu *list_controls = new QMenu(tr("Windows"));
		list_controls->addAction(tr("Toolbar"));
		list_controls->addAction(tr("Locations"));
		list_controls->addAction(tr("Status"));
		view_menu->addMenu(list_controls);
		view_menu->addSeparator();
		view_menu->addAction(tr("Close all tabs"));
		view_menu->addAction(tr("Close excet current"));
		view_menu->addAction(tr("Close curret tab"));
		view_menu->addSeparator();
		view_menu->addAction(tr("Fix/Unfix"));
		view_menu->addSeparator();
		view_menu->addAction(tr("Toggle description"));
		view_menu->addAction(tr("Toggle actions"));

		QMenu *help_menu = menuBar()->addMenu(tr("Help"));
		help_menu->addAction(QIcon(":/menu/help"), tr("Help"));
		help_menu->addAction(QIcon(":/menu/help_search"), tr("Search help"));
		help_menu->addSeparator();
		help_menu->addAction(tr("About"));
	}

	void MainWindow::CreateToolBar()
	{
		MainToolBar *_toolbar = new MainToolBar(tr("ToolBar"), this, _controls);
		connect(_toolbar, SIGNAL(actionTriggered(QAction *)), this, SLOT(OnToolbarAction(QAction *)));
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