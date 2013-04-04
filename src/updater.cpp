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

        QWidget *widget = new QWidget(this);
        QVBoxLayout *vbox = new QVBoxLayout;

        _textEdit = new QTextEdit(this);
        _textEdit->setReadOnly(true);
        _fileProgress = new QProgressBar(this);
        _fileProgress->setTextVisible(false);
        _totalProgress = new QProgressBar(this);
        //_totalProgress->setTextVisible(false);

        launchButton = new QPushButton("Launch", this);
        launchButton->setEnabled(false);
        connect(launchButton, SIGNAL(clicked()), this, SLOT(OnLaunchButton()));

        vbox->addWidget(_textEdit);
        vbox->addWidget(_fileProgress);
        vbox->addWidget(_totalProgress);
        vbox->addWidget(launchButton);

        widget->setLayout(vbox);
        setCentralWidget(widget);
    }

    Updater::~Updater()
    {
        delete download;
    }

    bool Updater::CheckForUpdate()
    {
        QString url = "http://dl.dropbox.com/u/16929037/QGen/" + _appName + ".ver";

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
            QDomElement fileToUpdate = qgen.firstChildElement("File");
            while (!fileToUpdate.isNull()) {
                QString fileName = fileToUpdate.attribute("name");
                QString fileSum = fileToUpdate.attribute("sum");
                if (!QFileInfo(QApplication::applicationDirPath() + QDir::separator() + fileName).exists())
                {
                    _filesToUpdate[fileName] = fileToUpdate.attribute("size").toUInt();
                } else if (fileSum != GetMD5Sum(QApplication::applicationDirPath() + QDir::separator() + fileName))
                {
                    _filesToUpdate[fileName] = fileToUpdate.attribute("size").toUInt();
                }
                fileToUpdate = fileToUpdate.nextSiblingElement("File");
            }

            quint64 sizeToDownload = 0;

            QMapIterator<QString, quint64> iter(_filesToUpdate);
            while (iter.hasNext()) {
                iter.next();
                sizeToDownload += iter.value();
            }

            desc += tr("<br/>Need to download %1").arg(ConvertSize(sizeToDownload));

            UpdateShow *dlg  = new UpdateShow(_remoteVersion, desc, this);
            if(dlg->exec())
            {
                return true;
            }
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
            file.setAttribute("sum", GetMD5Sum(list.at(i)));

            QFileInfo fileInfo(list.at(i));
            file.setAttribute("size", fileInfo.size());
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
        QDirIterator dirIt(directory, QDirIterator::Subdirectories);

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
            if (!QFile::copy(list.at(i), tmpDir.absolutePath() + QDir::separator() + filePath))
                return false;
        }

        QDomElement root = _updateFile.documentElement();

        QDomElement qgen = _updateFile.createElement("QGen");
        qgen.setAttribute("version", QString::fromWCharArray(QGEN_VER));
        qgen.setAttribute("path", QApplication::applicationDirPath());
        root.appendChild(qgen);

        QMapIterator<QString, quint64> iter(_filesToUpdate);
        while (iter.hasNext()) {
            iter.next();
            QDomElement file = _updateFile.createElement("File");
            file.setAttribute("name", iter.key());
            file.setAttribute("size", iter.value());
            qgen.appendChild(file);
        }

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
        QDomElement qgen = root.firstChildElement("QGen");
        while (!qgen.isNull()) {
            if (qgen.attribute("version") == QString::fromWCharArray(QGEN_VER))
            {
                _appPath = qgen.attribute("path");
                break;
            }
            qgen = qgen.nextSiblingElement("QGen");
        }

        QDomElement fileElement = qgen.firstChildElement("File");
        while (!fileElement.isNull()) {
            _filesToUpdate[fileElement.attribute("name")] = fileElement.attribute("size").toUInt();
            fileElement = fileElement.nextSiblingElement("File");
        }

        if(_filesToUpdate.isEmpty())
            return false;

        if(_appPath.isEmpty())
            return false;

        this->show();

        return StartUpdate();
    }

    QString Updater::ConvertSize(quint64 size)
    {
        const quint64 kb = 1024;
        const quint64 mb = 1024 * kb;
        const quint64 gb = 1024 * mb;
        const quint64 tb = 1024 * gb;

        if (size >= tb)
            return tr("%1 TB").arg(QLocale().toString(qreal(size) / tb, 'f', 3));
        if (size >= gb)
            return tr("%1 GB").arg(QLocale().toString(qreal(size) / gb, 'f', 2));
        if (size >= mb)
            return tr("%1 MB").arg(QLocale().toString(qreal(size) / mb, 'f', 1));
        if (size >= kb)
            return tr("%1 KB").arg(QLocale().toString(size / kb));
        return tr("%1 byte(s)").arg(QLocale().toString(size));
    }

    bool Updater::StartUpdate()
    {
        int fileNum = 0;
        downloadRequestAborted = false;

        _totalProgress->setMaximum(_filesToUpdate.count());
        _totalProgress->setValue(fileNum);
        _totalProgress->setFormat(QString("%1/%2").arg(_totalProgress->value()).arg(_filesToUpdate.count()));
        _downloadPath = QDir::tempPath() + QDir::separator() + _appName + "Upd";
        QDir tmpDir(_downloadPath);
        CleanFolder(tmpDir.absolutePath());

        QMapIterator<QString, quint64> iter(_filesToUpdate);
        while (iter.hasNext()) {
            iter.next();

            if(downloadRequestAborted)
                return false;

            QString filePath = iter.key();
            if(filePath.contains("/"))
            {
                QString fileDir = filePath.left(filePath.lastIndexOf("/"));
                if(!QDir(fileDir).exists())
                    tmpDir.mkpath(tmpDir.absolutePath() + QDir::separator() + fileDir);
            }
            else
                if(!QDir(tmpDir.absolutePath()).exists())
                    tmpDir.mkpath(tmpDir.absolutePath());

            filePath = _downloadPath + QDir::separator() + filePath;

            qDebug() << filePath;

            if(QFile::exists(filePath))
            {
                QFile::remove(filePath);
            }

            _downFile = new QFile(filePath);
            if(!_downFile->open(QIODevice::WriteOnly))
            {
                return false;
            }

            QString url = "http://dl.dropbox.com/u/16929037/QGen/" + iter.key();

            _textEdit->append(tr("Downloading %1 (%2)...<br/>").arg(iter.key(), ConvertSize(iter.value())));

            QEventLoop loop;

            download = manager.get(QNetworkRequest(QUrl(url)));
            connect(download, SIGNAL(finished()), this, SLOT(OnDownloadFinished()));
            connect(download, SIGNAL(readyRead()), this, SLOT(OnDownloadReadyRead()));
            connect(download, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(OnDownloadProgress(qint64,qint64)));
            connect(download, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            _totalProgress->setValue(++fileNum);
            _totalProgress->setFormat(QString("%1/%2").arg(_totalProgress->value()).arg(_filesToUpdate.count()));
        }
        if (!downloadRequestAborted)
        {
            QMapIterator<QString, quint64> iter(_filesToUpdate);
            while (iter.hasNext()) {
                iter.next();
                QFile::remove(_appPath + QDir::separator() + iter.key());
                QFile::copy(_downloadPath + QDir::separator() + iter.key(), _appPath + QDir::separator() + iter.key());
            }
            launchButton->setEnabled(true);
            return true;
        }
        return false;
    }

    void Updater::OnDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
    {
        if(downloadRequestAborted)
            return;
        _fileProgress->setMaximum(bytesTotal);
        _fileProgress->setValue(bytesReceived);
    }

    void Updater::OnDownloadReadyRead()
    {
        if(_downFile)
            _downFile->write(download->readAll());
    }

    void Updater::OnDownloadFinished()
    {
        if(downloadRequestAborted)
        {
            if(_downFile)
            {
                _downFile->close();
                _downFile->remove();
                delete _downFile;
                _downFile = NULL;
            }
            download->deleteLater();
            return;
        }

        OnDownloadReadyRead();
        _downFile->flush();
        _downFile->close();

        if(download->error())
        {
            _textEdit->append(tr("<font color=\"red\">Failed: %1</font>").arg(download->errorString()));
            _downFile->remove();
            downloadRequestAborted = true;
        }

        download->deleteLater();
        download = NULL;
        delete _downFile;
        _downFile = NULL;
    }

    void Updater::closeEvent(QCloseEvent *event)
    {
        downloadRequestAborted = true;
        download->abort();

        QMainWindow::closeEvent(event);
    }
}
