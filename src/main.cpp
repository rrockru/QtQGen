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

#include "controls.h"
#include "mainwindow.h"
#include "updater.h"

int main(int argc, char **argv)
{
    int res;

    setlocale (LC_CTYPE,"rus");

    QApplication application(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    application.installTranslator(&qtTranslator);

    application.setApplicationName("QGen");
    application.setApplicationVersion("5.0.1");
    Ui::Controls *_controls = new Ui::Controls(application.applicationDirPath());

    if (_controls->UpdateLocale(_controls->GetSettings()->GetLangId()))
        application.installTranslator(_controls->GetTranslator());

#ifdef WIN32
    if (!((argc == 2) && (!qstrcmp(argv[1], "-noupdate"))))
    {
        Ui::Updater *updater = new Ui::Updater(_controls);

        if ((argc == 2) && (!qstrcmp(argv[1], "-update")))
        {
            res = updater->Show();
            if (res != Ui::QGEN_UPDMSG_TRUE)
            {
                if (res == Ui::QGEN_UPDMSG_ABORTED)
                    return 0;
                _controls->ShowMessage(res);
                return 0;
            }
            return application.exec();
        }

        if ((argc == 2) && (!qstrcmp(argv[1], "-generate")))
        {
            if (updater->GenerateUpdateFile())
                QMessageBox::information(0, QObject::tr("Updater"), QObject::tr("Success!"));
            else
                QMessageBox::critical(0, QObject::tr("Updater"), QObject::tr("Error!"));
            return 0;
        }

        res = updater->CheckForUpdate();
        if (res == Ui::QGEN_UPDMSG_TRUE)
        {
            res = updater->LaunchUpdater();
            if (res != Ui::QGEN_UPDMSG_TRUE)
            {
                _controls->ShowMessage(res);
            }
            return 0;
        }
        else if (res == Ui::QGEN_UPDMSG_CANCEL)
        {
            return 0;
        }

        delete updater;
    }
#endif

    Ui::MainWindow *window = new Ui::MainWindow(_controls);
    _controls->SetMainWindow(window);
    _controls->SetLocListBox(window->GetLocListBox());
    _controls->SetTabsWisget(window->GetTabsWidget());
    _controls->NewGame();
    window->UpdateTitle();
    window->show();

    return application.exec();
}




