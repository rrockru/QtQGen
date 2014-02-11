#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = 0);

    void SetBackColor(QColor color);
    QColor GetBackColor();

signals:

public slots:

};

#endif // COLORWIDGET_H
