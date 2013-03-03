#include "stdafx.h"
#include "controls.h"
#include "mainwindow.h"

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	application.setApplicationName("QGen");
	application.setApplicationVersion("0.0.1");

	Ui::Controls *_controls = new Ui::Controls;
	Ui::MainWindow *window = new Ui::MainWindow(_controls);
	_controls->SetMainWindow(window);

	window->show();

	return application.exec();
}




