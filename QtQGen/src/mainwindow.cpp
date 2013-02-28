#include "stdafx.h"
#include "mainwindow.h"

namespace Ui
{

	MainWindow::MainWindow() :
		QMainWindow()
	{
		setMinimumSize(QSize(300, 200));
		setWindowTitle(TITLE);
		setDockNestingEnabled(true);
		resize(850, 650);

		// Set QMainWindow in the center of desktop
		QRect _defRect = geometry();
		_defRect.moveCenter(QApplication::desktop()->availableGeometry().center());
		setGeometry(_defRect);

		setContextMenuPolicy(Qt::NoContextMenu);

		//CreateDockWindows();
		CreateMenuBar();
		CreateToolBar();
		CreateStatusBar();
	}

	void MainWindow::CreateMenuBar()
	{
		QMenu *file_menu = menuBar()->addMenu(tr("File"));
		file_menu->addAction(QIcon(":/menu/game_new"), tr("New"));
		file_menu->addAction(QIcon(":/menu/file_open"), tr("Open..."));
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
		QToolBar *toolBar = addToolBar(tr("ToolBar"));
		
		toolBar->addAction(QIcon(":/toolbar/location_new"), tr("New location..."));
		toolBar->addAction(QIcon(":/toolbar/location_rename"), tr("Rename selected location..."));
		toolBar->addAction(QIcon(":/toolbar/location_delete"), tr("Delete selected location"));
		toolBar->addSeparator();
		toolBar->addAction(QIcon(":/toolbar/file_open"), tr("Open game..."));
		toolBar->addAction(QIcon(":/toolbar/file_save"), tr("Save game"));
		toolBar->addAction(QIcon(":/toolbar/file_saveas"), tr("Save game as"));
		toolBar->addSeparator();
		toolBar->addAction(QIcon(":/toolbar/game_play"), tr("Run game"));
		toolBar->addAction(QIcon(":/toolbar/game_info"), tr("Save game"));
		toolBar->addSeparator();
		toolBar->addAction(QIcon(":/toolbar/undo"), tr("Undo"));
		toolBar->addAction(QIcon(":/toolbar/redo"), tr("Redo"));
		toolBar->addSeparator();
		toolBar->addAction(QIcon(":/toolbar/location_copy"), tr("Copy selected location"));
		toolBar->addAction(QIcon(":/toolbar/location_paste"), tr("Paste location"));
		toolBar->addAction(QIcon(":/toolbar/location_clear"), tr("Clear selected location"));
		toolBar->addSeparator();
		toolBar->addAction(QIcon(":/toolbar/text_search"), tr("Search/Replace"));
		toolBar->addAction(QIcon(":/toolbar/options"), tr("Settings"));
	}

	void MainWindow::CreateStatusBar()
	{
		statusBar()->showMessage(tr("Ready"));
	}

	void MainWindow::CreateDockWindows()
	{
		QDockWidget* dock = new QDockWidget(tr("Locations"), this);
		QTextEdit *txtEdit = new QTextEdit;
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		dock->setWidget(txtEdit);
		addDockWidget(Qt::RightDockWidgetArea, dock);
	}

}