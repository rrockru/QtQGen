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

#include "updater.h"
#include "game.h"
#include "updaterdescriptiondlg.h"
#include "updateshow.h"

Updater::Updater(IControls *controls) :
    QMainWindow()
{
    _controls = controls;
    _appName = QApplication::applicationName();
    _remoteVersion = QString::fromWCharArray(QGEN_VER);
    _updateUrl = controls->GetSettings()->GetUpdateURL();
    _lastFile = "";

    _isUpdateAvailable = false;

    QWidget *widget = new QWidget(this);
    QVBoxLayout *vbox = new QVBoxLayout;

    _textEdit = new QTextEdit(this);
    _textEdit->setReadOnly(true);
    _fileProgress = new QProgressBar(this);
    _fileProgress->setTextVisible(false);
    _totalProgress = new QProgressBar(this);
    //_totalProgress->setTextVisible(false);

    launchButton = new QPushButton(tr("Launch"), this);
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
}

void Updater::CheckForUpdate()
{
    QString desc;

    QDir tmpDir(QDir::tempPath() + QDir::separator() + _appName);
    CleanFolder(tmpDir.absolutePath());
    tmpDir = QDir(QDir::tempPath() + QDir::separator() + _appName + "Upd");
    CleanFolder(tmpDir.absolutePath());

    QString url = _updateUrl + _appName + ".php";

    QEventLoop loop;

    QTimer::singleShot(5 * 1000, &loop, SLOT(quit()));
    download = manager.get(QNetworkRequest(QUrl(url)));
    connect(download, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (download->isRunning() || download->error())
    {
        download->abort();
        // Показ сообщения при невозможности получить файл описания обновления.
        //_controls->SetFailedFilesList(QStringList() << url);
        //_controls->ShowMessage(QGEN_UPDMSG_FAILDOWNUPDFILE);
        return;
    }

    QDomDocument dom;
    if (!dom.setContent(download->readAll()))
    {
        _controls->SetFailedFilesList(QStringList() << url);
        _controls->ShowMessage(QGEN_UPDMSG_FAILPARSEUPDFILE);
        return;
    }

    _updateFile = dom;

    QDomElement docElem = dom.documentElement();

    QDomElement qgen = docElem.firstChildElement("QGen");
    if (!qgen.isNull())
        _remoteVersion = qgen.attribute("version");

    if (_remoteVersion.isEmpty())
    {
        _controls->ShowMessage(QGEN_UPDMSG_BADUPDATEVERSION);
        return;
    }

    if (_remoteVersion  != QString::fromWCharArray(QGEN_VER))
    {
        desc = qgen.firstChildElement("Desc").text();
    }

    QDomElement fileToUpdate = qgen.firstChildElement("File");
    while (!fileToUpdate.isNull()) {
        UpdateInfo tmpInfo;
        QString fileName = fileToUpdate.attribute("name");
        uint fileSize = fileToUpdate.attribute("size").toUInt();
        QString fileSum = fileToUpdate.attribute("sum");
        if (!QFileInfo(QApplication::applicationDirPath() + QDir::separator() + fileName).exists())
        {
            tmpInfo.filename = fileName;
            tmpInfo.filesize = fileSize;
            tmpInfo.sum = fileSum;
            _filesToUpdate << tmpInfo;
        }
        else if (fileSum != GetMD5Sum(QApplication::applicationDirPath() + QDir::separator() + fileName))
        {
            tmpInfo.filename = fileName;
            tmpInfo.filesize = fileSize;
            tmpInfo.sum = fileSum;
            _filesToUpdate << tmpInfo;
        }
        fileToUpdate = fileToUpdate.nextSiblingElement("File");
    }

    if (_filesToUpdate.isEmpty())
    {
        return;
    }

    quint64 sizeToDownload = 0;

    QListIterator<UpdateInfo> iter(_filesToUpdate);
    while (iter.hasNext()) {
        sizeToDownload += iter.next().filesize;
    }

    if (sizeToDownload == 0)
    {
        _controls->ShowMessage(QGEN_UPDMSG_BADUPDATEFILE);
        return;
    }

    desc += tr("<br/><br/>--------------------<br/>Need to download %1").arg(ConvertSize(sizeToDownload));

    UpdateShow *dlg;
    if (_remoteVersion  != QString::fromWCharArray(QGEN_VER))
    {
        dlg = new UpdateShow(_remoteVersion, desc, false, this);
    }
    else
    {
        dlg = new UpdateShow(_remoteVersion, desc, true, this);
    }
    if (dlg->exec())
    {
        _isUpdateAvailable = true;
    }

    emit finished();
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

int Updater::LaunchUpdater()
{
    QDir directory(QApplication::applicationDirPath());
    QDir tmpDir(QDir::tempPath() + QDir::separator() + _appName);

    QStringList list = GetFileList(QApplication::applicationDirPath());
    for (int i = 0; i < list.size(); ++i) {
        QString filePath = directory.relativeFilePath(list.at(i));
        _lastFile = filePath;
        if (filePath.contains("/"))
        {
            QString fileDir = filePath.left(filePath.lastIndexOf("/"));
            tmpDir.mkpath(tmpDir.absolutePath() + QDir::separator() + fileDir);
        }
        else
            tmpDir.mkpath(tmpDir.absolutePath());
        if (!QFile::copy(list.at(i), tmpDir.absolutePath() + QDir::separator() + filePath))
        {
            _controls->SetFailedFilesList(QStringList() << QDir::toNativeSeparators(list.at(i)));
            return QGEN_UPDMSG_FAILCOPYUPDATER;
        }
    }

    QDomElement root = _updateFile.documentElement();

    QDomElement qgen = _updateFile.createElement("QGen");
    qgen.setAttribute("version", "old");
    qgen.setAttribute("path", QApplication::applicationDirPath());
    root.appendChild(qgen);

    QListIterator<UpdateInfo> iter(_filesToUpdate);
    while (iter.hasNext()) {
        UpdateInfo tmpInfo = iter.next();
        QDomElement file = _updateFile.createElement("File");
        file.setAttribute("name", tmpInfo.filename);
        file.setAttribute("size", tmpInfo.filesize);
        file.setAttribute("sum", tmpInfo.sum);
        qgen.appendChild(file);
    }

    QFile file(tmpDir.absolutePath() + QDir::separator() + _appName + ".ver");
    if (!file.open(QIODevice::WriteOnly))
        return QGEN_UPDMSG_FAILWRITEUPDFILE;
    if (!file.write(_updateFile.toByteArray())) {
        file.close();
        return QGEN_UPDMSG_FAILWRITEUPDFILE;
    }
    file.close();

#ifdef WIN32
    QProcess::startDetached(tmpDir.absolutePath() + QDir::separator() + _appName + ".exe", QStringList("-update"));
#else
    QProcess::startDetached(tmpDir.absolutePath() + QDir::separator() + _appName, QStringList("-update"));
#endif

    return QGEN_UPDMSG_TRUE;
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

int Updater::Show()
{
    QString updFile = QApplication::applicationDirPath() + QDir::separator() + _appName + ".ver";
    QFile file(updFile);
    if (!file.open(QIODevice::ReadOnly))
        return QGEN_UPDMSG_FAILREADUPDFILE;
    if (!_updateFile.setContent(file.readAll())) {
        file.close();
        return QGEN_UPDMSG_FAILREADUPDFILE;
    }
    file.close();

    QDomElement root = _updateFile.documentElement();
    QDomElement qgen = root.firstChildElement("QGen");
    while (!qgen.isNull()) {
        if (qgen.attribute("version") == "old")
        {
            _appPath = qgen.attribute("path");
            break;
        }
        qgen = qgen.nextSiblingElement("QGen");
    }

    QDomElement fileElement = qgen.firstChildElement("File");
    while (!fileElement.isNull()) {
        UpdateInfo tmpInfo;
        tmpInfo.filename = fileElement.attribute("name");
        tmpInfo.filesize = fileElement.attribute("size").toUInt();
        tmpInfo.sum = fileElement.attribute("sum");
        _filesToUpdate << tmpInfo;
        fileElement = fileElement.nextSiblingElement("File");
    }

    if (_filesToUpdate.isEmpty())
    {
        _controls->SetFailedFilesList(QStringList() << updFile);
        return QGEN_UPDMSG_FAILPARSEUPDFILE;
    }

    if (_appPath.isEmpty())
        return QGEN_UPDMSG_BADUPDATEFILE;

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

int Updater::StartUpdate()
{
    int fileNum = 0;
    downloadRequestAborted = false;
    networkError = false;

    _totalProgress->setMaximum(_filesToUpdate.count());
    _totalProgress->setValue(fileNum);
    _totalProgress->setFormat(QString("%1/%2").arg(_totalProgress->value()).arg(_filesToUpdate.count()));

    _downloadPath = QDir::tempPath() + QDir::separator() + _appName + "Upd";
    QDir tmpDir(_downloadPath);

    QListIterator<UpdateInfo> iter(_filesToUpdate);
    while (iter.hasNext()) {
        UpdateInfo tmpInfo = iter.next();

        QString filePath = tmpInfo.filename;
        if (filePath.contains("/"))
        {
            QString fileDir = filePath.left(filePath.lastIndexOf("/"));
            if (!QDir(tmpDir.absolutePath() + QDir::separator() + fileDir).exists())
                tmpDir.mkpath(tmpDir.absolutePath() + QDir::separator() + fileDir);
        }
        else
            if (!QDir(tmpDir.absolutePath()).exists())
                tmpDir.mkpath(tmpDir.absolutePath());

        filePath = _downloadPath + QDir::separator() + filePath;

        if (QFile::exists(filePath))
        {
            QFile::remove(filePath);
        }

        _downFile = new QFile(filePath);
        if (!_downFile->open(QIODevice::WriteOnly))
        {
            _controls->SetFailedFilesList(QStringList() << tmpInfo.filename << QDir::toNativeSeparators(filePath));
            return QGEN_UPDMSG_FAILWRITENEWFILE;
        }

        QString url = _updateUrl + tmpInfo.filename;

        _textEdit->append(tr("Downloading %1 (%2)...").arg(tmpInfo.filename, ConvertSize(tmpInfo.filesize)));

        QEventLoop loop;

        download = manager.get(QNetworkRequest(QUrl(url)));
        connect(download, SIGNAL(finished()), this, SLOT(OnDownloadFinished()));
        connect(download, SIGNAL(readyRead()), this, SLOT(OnDownloadReadyRead()));
        connect(download, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(OnDownloadProgress(qint64,qint64)));
        connect(download, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        if (downloadRequestAborted)
            return QGEN_UPDMSG_ABORTED;

        if (networkError)
        {
            _controls->SetFailedFilesList(QStringList() << url);
            return QGEN_UPDMSG_FAILDOWNNEWFILE;
        }

        _totalProgress->setValue(++fileNum);
        _totalProgress->setFormat(QString("%1/%2").arg(_totalProgress->value()).arg(_filesToUpdate.count()));

        _textEdit->append(tr("Checking %1... ").arg(tmpInfo.filename));
        if (tmpInfo.sum != GetMD5Sum(filePath))
        {
            _textEdit->insertHtml("<font color=\"red\">BAD</font>");
            _controls->SetFailedFilesList(QStringList() << QDir::toNativeSeparators(filePath));
            return QGEN_UPDMSG_BADCHECKSUM;
        }
        else
        {
            _textEdit->insertHtml("OK");
        }
    }
    if (!downloadRequestAborted)
    {
        QListIterator<UpdateInfo> iter(_filesToUpdate);
        while (iter.hasNext()) {
            UpdateInfo tmpInfo = iter.next();
            _lastFile = tmpInfo.filename;
            QFile::remove(_appPath + QDir::separator() + tmpInfo.filename);
            if (tmpInfo.filename.contains("/"))
            {
                QString fileDir = tmpInfo.filename.left(tmpInfo.filename.lastIndexOf("/"));
                if (!QDir(fileDir).exists())
                    tmpDir.mkpath(_appPath + QDir::separator() + fileDir);
            }
            QString from = _downloadPath + QDir::separator() + tmpInfo.filename;
            QString to = _appPath + QDir::separator() + tmpInfo.filename;
            if (!QFile::copy(from, to))
            {
                _controls->SetFailedFilesList(QStringList() << QDir::toNativeSeparators(from) << QDir::toNativeSeparators(to));
                return QGEN_UPDMSG_FAILCOPYNEWFILE;
            }
        }
        launchButton->setEnabled(true);
        return QGEN_UPDMSG_TRUE;
    }
    return QGEN_UPDMSG_FALSE;
}

void Updater::OnDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (downloadRequestAborted)
        return;
    _fileProgress->setMaximum(bytesTotal);
    _fileProgress->setValue(bytesReceived);
}

void Updater::OnDownloadReadyRead()
{
    if (_downFile)
        _downFile->write(download->readAll());
}

void Updater::OnDownloadFinished()
{
    if (downloadRequestAborted || networkError)
    {
        if (_downFile)
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

    if (download->error())
    {
        _textEdit->append(tr("<font color=\"red\">Failed: %1</font>").arg(download->errorString()));
        _downFile->remove();
        networkError = true;
    }

    download->deleteLater();
    download = NULL;
    delete _downFile;
    _downFile = NULL;
}

void Updater::closeEvent(QCloseEvent *event)
{
    if (download != NULL)
    {
        downloadRequestAborted = true;
        download->abort();
    }

    QMainWindow::closeEvent(event);
}
