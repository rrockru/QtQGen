#include "QtNetwork"

#include "stdafx.h"
#include "updater.h"
#include "game.h"
#include "updaterdescriptiondlg.h"
#include "updateshow.h"


namespace Ui
{
    Updater::Updater() :
        QMainWindow()
    {
        _appName = QApplication::applicationName();
        _remoteVersion = QString::fromWCharArray(QGEN_VER);
    }

    bool Updater::CheckForUpdate()
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

        QDomDocument dom;
        if (!dom.setContent(download->readAll()))
            return false;

        QDomElement docElem = dom.documentElement();

        QDomElement qgen = docElem.firstChildElement("QGen");
        if (!qgen.isNull())
            _remoteVersion = qgen.attribute("version");

        if (_remoteVersion.isEmpty())
            return false;

        if(_remoteVersion  != QString::fromWCharArray(QGEN_VER))
        {
            QString desc = qgen.firstChildElement("Desc").text();
            UpdateShow *dlg  = new UpdateShow(_remoteVersion, desc, this);
            return dlg->exec();
        }
        return false;
    }

    void Updater::OnLaunchButton()
    {
        QProcess::startDetached(_appName, QStringList("-update"));
        close();
    }

    QString Updater::GetMD5Sum(const QString &fileName)
    {
        QCryptographicHash hash(QCryptographicHash::Md5);
        QFile file(fileName);
        QFileInfo fileInfo(fileName);
        qint64 fileSize = fileInfo.size();

        const qint64 bufferSize = 10000;
        if (file.open(QIODevice::ReadOnly))
        {
            char buf[bufferSize];
            int bytesRead;

            int readSize = qMin(fileSize, bufferSize);
            while (readSize > 0 && (bytesRead = file.read(buf, readSize)) > 0)
            {
                fileSize -= bytesRead;
                hash.addData(buf, bytesRead);
                readSize = qMin(fileSize, bufferSize);
            }

            file.close();
            return hash.result().toHex();
        }
        else {
            return "";
        }
    }

    bool Updater::GenerateUpdateFile()
    {
        UpdaterDescriptionDlg *dlg = new UpdaterDescriptionDlg(this);
        dlg->exec();

        QDomDocument doc("QGenUpd");
        QDomElement root = doc.createElement("QGenUpd");
        doc.appendChild(root);

        QDomElement qgen = doc.createElement("QGen");
        qgen.setAttribute("version", QString::fromWCharArray(QGEN_VER));
        root.appendChild(qgen);

        QDomElement desc = doc.createElement("Desc");
        qgen.appendChild(desc);

        QDomText t = doc.createTextNode(dlg->GetText().trimmed());
        desc.appendChild(t);

        QStringList list = GetFileList(QApplication::applicationDirPath());
        for (int i = 0; i < list.size(); ++i) {
            QDomElement file = doc.createElement("File");
            file.setAttribute("name", list.at(i));
            file.setAttribute("sum", GetMD5Sum(QApplication::applicationDirPath() + QDir::separator() + list.at(i)));
            qgen.appendChild(file);
        }

        QFile file(_appName + ".ver");
        if (!file.open(QIODevice::WriteOnly))
            return false;
        if (!file.write(doc.toByteArray())) {
            file.close();
            return false;
        }
        file.close();

        return true;
    }

    QStringList Updater::GetFileList(const QDir &directory)
    {
        QStringList tmpList;
        QDirIterator dirIt(directory,QDirIterator::Subdirectories);

        while (dirIt.hasNext()) {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
                tmpList << directory.relativeFilePath(dirIt.filePath());
        }
        return tmpList;
    }
}
