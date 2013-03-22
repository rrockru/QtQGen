#ifndef UPDATER_H
#define UPDATER_H

#include <QMainWindow>

namespace Ui
{

    class Updater : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit Updater(QString &appName);

        bool IsUpdateExist();
        QString GetRemoteVersion() { return _remoteVersion; }
        void SetAppName(QString appName) { _appName = appName; }

    signals:

    public slots:

    private slots:
        void OnLaunchButton();

    private:
        QString _remoteVersion;
        QString _appName;

    };
} // namespace Ui

#endif // UPDATER_H
