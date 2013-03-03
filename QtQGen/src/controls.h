#ifndef _CONTROLS_
#define _CONTROLS_

#include "IControls.h"
#include "mainwindow.h"

namespace Ui
{
	class Controls :
		public IControls
	{
	public:
		Controls();

		void SetMainWindow(MainWindow *);
		void SetStatusText(const QString &text);
		void CleanStatusText();

	private:
		QMainWindow *_mainWindow;
	};
} // namespace Ui

#endif // _CONTROLS_

