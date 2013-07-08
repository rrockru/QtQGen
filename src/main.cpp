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
#include "updaterthread.h"

int main(int argc, char **argv)
{
    setlocale (LC_CTYPE,"rus");

    QApplication application(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    application.installTranslator(&qtTranslator);

    application.setApplicationName("QGen");
    application.setApplicationVersion(QString::fromWCharArray(QGEN_VER));
    Controls *_controls = new Controls(application.applicationDirPath());

    if (_controls->UpdateLocale(_controls->GetSettings()->GetLangId()))
        application.installTranslator(_controls->GetTranslator());

#ifdef WIN32
    if ((argc == 2) && (!qstrcmp(argv[1], "-update")))
    {
        Updater *updater = new Updater(_controls);

        int res = updater->Show();
        if (res != QGEN_UPDMSG_TRUE)
        {
            if (res == QGEN_UPDMSG_ABORTED)
                return 0;
            _controls->ShowMessage(res);
            return 0;
        }
        return application.exec();
    }
    if (!((argc == 2) && (!qstrcmp(argv[1], "-noupdate"))))
    {
        UpdaterThread *updaterThread = new UpdaterThread(_controls);
        updaterThread->process();
    }
#endif

    MainWindow *window = new MainWindow(_controls);
    _controls->SetMainWindow(window);
    _controls->SetLocListBox(window->GetLocListBox());
    _controls->SetTabsWidget(window->GetTabsWidget());
    _controls->NewGame();
    window->UpdateTitle();
    window->Update();
    window->show();

    QFileInfo game;
    if (application.arguments().count() > 1)
        game.setFile(application.arguments().at(1));

    if ((game.isFile()) && game.exists() && (game.completeSuffix() == "qsp"))
    {
        window->Init(game.canonicalFilePath());
    }
    else
    {
        Settings *settings = _controls->GetSettings();
        if (settings->GetOpenLastGame())
        {
            QFileInfo game(settings->GetLastGamePath());
            if (game.exists())
                window->Init(game.canonicalFilePath());
        }
    }

    int r = application.exec();

    Settings* settings = _controls->GetSettings();
    settings->SetLastGamePath(_controls->GetGamePath());
    settings->SaveSettings();

    delete _controls;

    return r;
}




