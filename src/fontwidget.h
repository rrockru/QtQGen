#ifndef FONTWIDGET_H
#define FONTWIDGET_H

#include <QLabel>

class FontWidget : public QLabel
{
    Q_OBJECT
public:
    explicit FontWidget(QWidget *parent = 0);

    void SetBackColor(QColor color);
    void SetFontColor(QColor color);

signals:

public slots:

};

#endif // FONTWIDGET_H
