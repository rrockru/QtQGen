#include "stdafx.h"
#include "MainToolBar.h"

namespace Ui
{
	MainToolBar::MainToolBar(QString name, QWidget *parent, IControls *controls) : QToolBar(name, parent)
	{
		_controls = controls;
		ToolButton *newButton = new ToolButton(QIcon(":/toolbar/location_new"), tr("New location..."), this, _controls);
		addAction(newButton);
		ToolButton *renameButton = new ToolButton(QIcon(":/toolbar/location_rename"), tr("Rename selected location..."), this, _controls);
		addAction(renameButton);
		ToolButton *delButton = new ToolButton(QIcon(":/toolbar/location_delete"), tr("Delete selected location"), this, _controls);
		addAction(delButton);
		addSeparator();

		ToolButton *openButton = new ToolButton(QIcon(":/toolbar/file_open"), tr("Open game..."), this, _controls);
		connect(openButton, SIGNAL(triggered()), parent, SLOT(OnLoadGame()));
		addAction(openButton);
		ToolButton *saveButton = new ToolButton(QIcon(":/toolbar/file_save"), tr("Save game"), this, _controls);
        connect(saveButton, SIGNAL(triggered()), parent, SLOT(OnSaveGame()));
		addAction(saveButton);
		ToolButton *saveasButton = new ToolButton(QIcon(":/toolbar/file_saveas"), tr("Save game as"), this, _controls);
        connect(saveasButton, SIGNAL(triggered()), parent, SLOT(OnSaveGameAs()));
		addAction(saveasButton);
		addSeparator();

		ToolButton *playButton = new ToolButton(QIcon(":/toolbar/game_play"), tr("Run game"), this, _controls);
		addAction(playButton);
		ToolButton *infoButton = new ToolButton(QIcon(":/toolbar/game_info"), tr("Save game"), this, _controls);
		addAction(infoButton);
		addSeparator();

		ToolButton *undoButton = new ToolButton(QIcon(":/toolbar/undo"), tr("Undo"), this, _controls);
		addAction(undoButton);
		ToolButton *redoButton = new ToolButton(QIcon(":/toolbar/redo"), tr("Redo"), this, _controls);
		addAction(redoButton);
		addSeparator();

		ToolButton *copyButton = new ToolButton(QIcon(":/toolbar/location_copy"), tr("Copy selected location"), this, _controls);
		addAction(copyButton);
		ToolButton *pasteButton = new ToolButton(QIcon(":/toolbar/location_paste"), tr("Paste location"), this, _controls);
		addAction(pasteButton);
		ToolButton *clearButton = new ToolButton(QIcon(":/toolbar/location_clear"), tr("Clear selected location"), this, _controls);
		addAction(clearButton);
		addSeparator();

		ToolButton *searchButton = new ToolButton(QIcon(":/toolbar/text_search"), tr("Search/Replace"), this, _controls);
		addAction(searchButton);
		ToolButton *settingsButton = new ToolButton(QIcon(":/toolbar/options"), tr("Settings"), this, _controls);
		addAction(settingsButton);

		setMouseTracking(true);
	}

	void MainToolBar::mouseMoveEvent(QMouseEvent* e)
	{
		_controls->CleanStatusText();
	}

	void MainToolBar::leaveEvent(QEvent * event)
	{
		_controls->CleanStatusText();
	}
}

