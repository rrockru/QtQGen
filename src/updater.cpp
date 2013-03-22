#include "stdafx.h"
#include "updater.h"
#include "game.h"

#include "QtNetwork"


namespace Ui
{
    Updater::Updater(QString &appName) :
        QMainWindow()
    {
        _appName = appName;
        _remoteVersion = QString::fromWCharArray(QGEN_VER);

        QHBoxLayout *hBox = new QHBoxLayout;
        QPushButton *launchButton = new QPushButton(tr("Launch"), this);
        connect(launchButton, SIGNAL(clicked()), this, SLOT(OnLaunchButton()));
    }

    bool Updater::IsUpdateExist()
    {
        QString url = "http://dl.dropbox.com/u/16929037/QGen/" + _appName + ".ver";

        QNetworkAccessManager manager;
        QNetworkReply *download;
        QEventLoop loop;

        QTimer::singleShot(5 * 1000, &loop, SLOT(quit()));
        download = manager.get(QNetworkRequest(QUrl(url)));
        connect(download, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        if(download->isRunning() || download->error())
        {
            download->abort();
            return false;
        }

        if((_remoteVersion = download->readLine().trimmed()) != QString::fromWCharArray(QGEN_VER))
        {
            return true;
        }
            return false;
    }

    void Updater::OnLaunchButton()
    {
        QProcess::startDetached(_appName, QStringList("-update"));
        close();
    }
}
