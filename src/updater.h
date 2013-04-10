#ifndef UPDATER_H
#define UPDATER_H

#include <QtCore>
#include <QMainWindow>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>

#include "IControls.h"

namespace Ui
{
    struct UpdateInfo
    {
        QString filename;
        uint filesize;
        QString sum;
    };

    class Updater : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit Updater();
        ~Updater();

        int CheckForUpdate();
        bool GenerateUpdateFile();
        int LaunchUpdater();

        int Show();

    signals:

    protected:
        void closeEvent(QCloseEvent * event);

    public slots:

    private slots:
        void OnLaunchButton();
        void OnDownloadProgress(qint64,qint64);
        void OnDownloadFinished();
        void OnDownloadReadyRead();
        //void OnCancelDownload();

    private:
        bool CleanFolder(const QString &directory);
        QStringList GetFileList(const QDir &directory);
        QString GetMD5Sum(const QString &fileName);
        QString ConvertSize(quint64);
        int StartUpdate();

        QString _appName;
        QString _remoteVersion;
        QString _appPath;
        QString _downloadPath;
        QString _updateUrl;
        QString _lastFile;

        QDomDocument _updateFile;
        QList<UpdateInfo> _filesToUpdate;
        QTextEdit *_textEdit;
        QProgressBar *_fileProgress;
        QProgressBar *_totalProgress;
        QFile *_downFile;

        QNetworkAccessManager manager;
        QNetworkReply *download;

        QPushButton *launchButton;

        quint32 _crc32table[256];
        bool downloadRequestAborted;
        bool networkError;
    };
} // namespace Ui

#endif // UPDATER_H
