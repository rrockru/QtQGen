#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
}

void ColorWidget::SetBackColor(QColor color)
{
    QPalette pal;
    pal = palette();
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

QColor ColorWidget::GetBackColor()
{
    return palette().color(QPalette::Window);
}
