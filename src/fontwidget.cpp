#include "fontwidget.h"

FontWidget::FontWidget(QWidget *parent) :
    QLabel(parent)
{
}

void FontWidget::SetBackColor(QColor color)
{
    QPalette pal;
    pal = palette();
    pal.setColor(QPalette::Window, color);
    setPalette(pal);
}

void FontWidget::SetFontColor(QColor color)
{
    QPalette pal;
    pal = palette();
    pal.setColor(QPalette::WindowText, color);
    setPalette(pal);
}
