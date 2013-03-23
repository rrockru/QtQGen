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

        QVBoxLayout *vbox = new QVBoxLayout;
        QPushButton *button = new QPushButton("Launch", this);
        connect(button, SIGNAL(clicked()), this, SLOT(OnLaunchButton()));
        vbox->addWidget(button);

        setLayout(vbox);
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

        _updateFile = dom;

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
        QString path;
#ifdef WIN32
        path = _appPath + QDir::separator() + _appName + ".exe";
#else
        path = _appPath + QDir::separator() + _appName;
#endif
        qDebug() << path;
        QProcess::startDetached(path);
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

        QDir directory(QApplication::applicationDirPath());

        QStringList list = GetFileList(directory);
        for (int i = 0; i < list.size(); ++i) {
            QDomElement file = doc.createElement("File");
            file.setAttribute("name", directory.relativeFilePath(list.at(i)));
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
                tmpList << dirIt.filePath();
        }
        return tmpList;
    }

    bool Updater::LaunchUpdater()
    {
        QDir directory(QApplication::applicationDirPath());

        QDir tmpDir(QDir::tempPath() + QDir::separator() + _appName);
        CleanFolder(tmpDir.absolutePath());

        QStringList list = GetFileList(QApplication::applicationDirPath());
        for (int i = 0; i < list.size(); ++i) {
            QString filePath = directory.relativeFilePath(list.at(i));
            if(filePath.contains("/"))
            {
                QString fileDir = filePath.left(filePath.lastIndexOf("/"));
                tmpDir.mkpath(tmpDir.absolutePath() + QDir::separator() + fileDir);
            }
            else
                tmpDir.mkpath(tmpDir.absolutePath());
            qDebug() << tmpDir.absolutePath() + QDir::separator() + filePath;
            if (!QFile::copy(list.at(i), tmpDir.absolutePath() + QDir::separator() + filePath))
                return false;
        }

        QDomElement root = _updateFile.documentElement();

        QDomElement qgen = _updateFile.createElement("QGen");
        qgen.setAttribute("version", QString::fromWCharArray(QGEN_VER));
        qgen.setAttribute("path", QApplication::applicationDirPath());
        root.appendChild(qgen);

        QFile file(tmpDir.absolutePath() + QDir::separator() + _appName + ".ver");
        if (!file.open(QIODevice::WriteOnly))
            return false;
        if (!file.write(_updateFile.toByteArray())) {
            file.close();
            return false;
        }
        file.close();

#ifdef WIN32
        QProcess::startDetached(tmpDir.absolutePath() + QDir::separator() + _appName + ".exe", QStringList("-update"));
#else
        QProcess::startDetached(tmpDir.absolutePath() + QDir::separator() + _appName, QStringList("-update"));
#endif

        return true;
    }

    bool Updater::CleanFolder(const QString &directory)
    {
       int res = false;
       QDir dir(directory);
       QStringList lstDirs  = dir.entryList(QDir::Dirs  |
                                       QDir::AllDirs |
                                       QDir::NoDotAndDotDot);

       QStringList lstFiles = dir.entryList(QDir::Files);
       foreach (QString entry, lstFiles)
       {
          QString entryAbsPath = dir.absolutePath() + "/" + entry;
          QFile::remove(entryAbsPath);
       }

       foreach (QString entry, lstDirs)
       {
          QString entryAbsPath = dir.absolutePath() + "/" + entry;
          CleanFolder(entryAbsPath);
       }

       if (!QDir().rmdir(dir.absolutePath()))
       {
          res = true;
       }
       return res;
    }

    bool Updater::Show()
    {
        QFile file(QApplication::applicationDirPath() + QDir::separator() + _appName + ".ver");
        if (!file.open(QIODevice::ReadOnly))
            return false ;
        if (!_updateFile.setContent(file.readAll())) {
            file.close();
            return false;
        }
        file.close();

        QDomElement root = _updateFile.documentElement();
        QDomNode n = root.firstChild();
        while (!n.isNull()) {
            if (n.isElement()) {
                QDomElement e = n.toElement();
                if (e.attribute("version") == QString::fromWCharArray(QGEN_VER))
                {
                    _appPath = e.attribute("path");
                    break;
                }
            }
            n = n.nextSibling();
        }

        if(_appPath.isEmpty())
            return false;

        this->show();

        return true;
    }
}
