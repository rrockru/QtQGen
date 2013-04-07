#ifndef UPDATESHOW_H
#define UPDATESHOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QApplication>
#include <QDesktopWidget>

namespace Ui
{

    class UpdateShow : public QDialog
    {
        Q_OBJECT
    public:
        explicit UpdateShow(const QString &ver, const QString &desc, bool repair = false, QWidget *parent = 0);

    signals:

    public slots:

    };

} // namespace Ui

#endif // UPDATESHOW_H
