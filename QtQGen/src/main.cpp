#include "stdafx.h"
#include "controls.h"
#include "mainwindow.h"

int main(int argc, char **argv)
{
	setlocale (LC_CTYPE,"rus");

	QApplication application(argc, argv);
	application.setApplicationName("QGen");
	application.setApplicationVersion("0.0.1");

	Ui::Controls *_controls = new Ui::Controls(application.applicationDirPath());
	Ui::MainWindow *window = new Ui::MainWindow(_controls);
	_controls->SetMainWindow(window);
	_controls->SetLocListBox(window->GetLocListBox());
	_controls->SetTabsWisget(window->GetTabsWidget());
	window->UpdateTitle();
	window->show();

	return application.exec();
}




