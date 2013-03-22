#ifndef UPDATER_H
#define UPDATER_H

#include <QtCore>
#include <QMainWindow>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>

namespace Ui
{

    class Updater : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit Updater();

        bool CheckForUpdate();
        bool GenerateUpdateFile();

    signals:

    public slots:

    private slots:
        void OnLaunchButton();

    private:
        QStringList GetFileList(const QDir &directory);
        QString GetMD5Sum(const QString &fileName);

        QString _appName;
        QString _remoteVersion;

        quint32 _crc32table[256];
    };
} // namespace Ui

#endif // UPDATER_H
