// Copyright (C) 2013
// Shchannikov Dmitry (rrock DOT ru AT gmail DOT com)
// Nex (nex AT otaku DOT ru)
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QColorDialog>
#include <QDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "icontrols.h"

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(IControls *control, QWidget *parent = 0);
    ~OptionsDialog();

public slots:
    void OnFontSelect();
    void OnColorSelect();
    void OnPathSelect();
    void OnApplyButton();
    void OnResetButton();
    void OnOkButton();
    void OnSettingsChanged();

private:
    Ui::OptionsDialog *ui;

    void InitOptionsDialog();
    void ApplySettings();

    IControls *_control;
    Settings *_settings;
};

#endif // OPTIONSDIALOG_H
