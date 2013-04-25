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

#include "updateshow.h"

namespace Ui
{

    UpdateShow::UpdateShow(const QString &ver, const QString &desc, bool repair, QWidget *parent) :
        QDialog(parent)
    {
        QLabel *label;
        QVBoxLayout *vbox = new QVBoxLayout;
        setWindowTitle(tr("Update ") + ver);
        if (!repair)
        {
            label = new QLabel(tr("Available new version. Changes:"));
        }
        else
        {
            label = new QLabel(tr("Need to repair"));
        }
        QTextEdit *text = new QTextEdit(this);
        text->setHtml(desc);
        text->setReadOnly(true);
        QHBoxLayout *hbox = new QHBoxLayout;

        QPushButton *okButton = new QPushButton(tr("Install"), this);
        connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

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

}
