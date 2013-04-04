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

namespace Ui
{

    class Updater : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit Updater();
        ~Updater();

        bool CheckForUpdate();
        bool GenerateUpdateFile();
        bool LaunchUpdater();

        bool Show();

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
        bool StartUpdate();

        QString _appName;
        QString _remoteVersion;
        QString _appPath;
        QString _downloadPath;

        QDomDocument _updateFile;
        QMap<QString, quint64> _filesToUpdate;
        QTextEdit *_textEdit;
        QProgressBar *_fileProgress;
        QProgressBar *_totalProgress;
        QFile *_downFile;

        QNetworkAccessManager manager;
        QNetworkReply *download;

        QPushButton *launchButton;

        quint32 _crc32table[256];
        bool downloadRequestAborted;
    };
} // namespace Ui

#endif // UPDATER_H
