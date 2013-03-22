#ifndef UPDATESHOW_H
#define UPDATESHOW_H

#include <QDialog>

namespace Ui
{

    class UpdateShow : public QDialog
    {
        Q_OBJECT
    public:
        explicit UpdateShow(const QString &ver, const QString &desc, QWidget *parent = 0);

    signals:

    public slots:

    };

} // namespace Ui

#endif // UPDATESHOW_H
