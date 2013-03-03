#include "stdafx.h"
#include "controls.h"

namespace Ui
{
	Controls::Controls()
	{
	}

	void Controls::SetMainWindow(MainWindow *wnd)
	{
		_mainWindow = wnd;
	}

	void Controls::SetStatusText(const QString &text)
	{
		QStatusBar *_statusBar = _mainWindow->statusBar();
		if (_statusBar)
		{
			_statusBar->showMessage(text);
		}
	}

	void Controls::CleanStatusText()
	{
		QStatusBar *_statusBar = _mainWindow->statusBar();
		if (_statusBar)
		{
			_statusBar->clearMessage();
		}
	}
}


