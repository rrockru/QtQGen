#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include  "icontrols.h"

class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OptionsDialog(IControls *controls, QString caption, QWidget *parent = 0);

private:
    IControls *_controls;

    QWidget *_general;
    QWidget *_editor;
    QWidget *_sizes;
    QWidget *_colors;
    QWidget *_fonts;
    QWidget *_paths;
    QWidget *_hotkeys;
    
signals:
    
public slots:
    
};

#endif // OPTIONSDIALOG_H
