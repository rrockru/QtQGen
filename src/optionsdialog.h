#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

#include "icontrols.h"

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(IControls *_control, QWidget *parent = 0);
    ~OptionsDialog();

private:
    Ui::OptionsDialog *ui;

    void UpdateColors();

    IControls *m_control;
};

#endif // OPTIONSDIALOG_H
