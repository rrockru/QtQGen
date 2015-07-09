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

#ifndef _QGEN_MERGE_DIALOG_H_
#define _QGEN_MERGE_DIALOG_H_

enum
{
    ID_MERGE_REPLACE = 10600,
    ID_MERGE_SKIP,
    ID_MERGE_CANCEL
};

enum
{
    MERGE_ALL = 1 << 0,
    MERGE_REPLACE = 1 << 1,
    MERGE_SKIP = 1 << 2,
    MERGE_CANCEL = 1 << 30
};

class MergeDialog : public QDialog
{
    Q_OBJECT

    QPushButton    *_replace;
    QPushButton    *_skip;
    QPushButton    *_cancel;
    QCheckBox    *_chkToAll;

    //void OnButton(wxCommandEvent &event);

public:
    MergeDialog(QWidget *parent, const QString& title, const QString &message);

private:
    void Done(int);

private slots:
    void OnReplace();
    void OnSkip();
    void OnCancel();
};

#endif
