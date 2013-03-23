// Copyright (C) 2013
// Shchannikov Dmitry (rrock DOT ru AT gmail DOT com)
// Nex (nex AT otaku DOT ru)
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include <QApplication>

#include "controls.h"
#include "mainwindow.h"
#include "updater.h"

int main(int argc, char **argv)
{
	setlocale (LC_CTYPE,"rus");

    QApplication application(argc, argv);

    QString updaterAppName = application.applicationDirPath() + QDir::separator() + "updater.exe";

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
		QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	application.installTranslator(&qtTranslator);

	application.setApplicationName("QGen");
    application.setApplicationVersion("5.0.1");
	Ui::Controls *_controls = new Ui::Controls(application.applicationDirPath());

    if(_controls->UpdateLocale(_controls->GetSettings()->GetLangId()))
        application.installTranslator(_controls->GetTranslator());

    Ui::Updater *updater = new Ui::Updater();

    if ((argc == 2) && (!qstrcmp(argv[1], "-update")))
    {
        updater->show();
        return application.exec();
    }

    if ((argc == 2) && (!qstrcmp(argv[1], "-generate")))
    {
        if(updater->GenerateUpdateFile())
            QMessageBox::information(0, QObject::tr("Updater"), QObject::tr("Success!"));
        else
            QMessageBox::information(0, QObject::tr("Updater"), QObject::tr("Error!"));
        return 0;
    }

    if (QFile::exists(updaterAppName))
        QFile::remove(updaterAppName);

    if(updater->CheckForUpdate())
    {
        if (!updater->LaunchUpdater())
            QMessageBox::critical(0, QObject::tr("Updater"), QObject::tr("Error!"));
        else
        {
            return 0;
        }
    }
    delete updater;

	Ui::MainWindow *window = new Ui::MainWindow(_controls);
	_controls->SetMainWindow(window);
	_controls->SetLocListBox(window->GetLocListBox());
	_controls->SetTabsWisget(window->GetTabsWidget());
	_controls->NewGame();
	window->UpdateTitle();
	window->show();

	return application.exec();
}




