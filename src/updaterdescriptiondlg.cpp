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

#include "updaterdescriptiondlg.h"
#include "game.h"

UpdaterDescriptionDlg::UpdaterDescriptionDlg(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    setWindowTitle(tr("Update ") + QString::fromWCharArray(QGEN_VER));
    QLabel *label = new QLabel(tr("Input description for update:"));
    text = new QTextEdit(this);
    QHBoxLayout *hbox = new QHBoxLayout;

    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, SIGNAL(clicked()), this, SLOT(OnOkButton()));

    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    hbox->addWidget(okButton);
    hbox->addWidget(cancelButton);

    vbox->addWidget(label);
    vbox->addWidget(text);
    vbox->addLayout(hbox);

    setLayout(vbox);

    resize(300, 300);
    QRect _defRect = geometry();
    _defRect.moveCenter(QApplication::desktop()->availableGeometry().center());
    setGeometry(_defRect);
}

void UpdaterDescriptionDlg::OnOkButton()
{
    _resText = text->toPlainText().replace("\n", "<br/>");
    accept();
}
