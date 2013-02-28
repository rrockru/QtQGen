#include "stdafx.h"
#include "mainwindow.h"

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	application.setApplicationName("QGet");
	application.setApplicationVersion("0.0.1");

	Ui::MainWindow *window = new Ui::MainWindow();
	window->show();

	return application.exec();
}
