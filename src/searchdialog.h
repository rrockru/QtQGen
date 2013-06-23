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

#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "icontrols.h"

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(IControls *controls, QString& title, QWidget *parent = 0);

    bool Show(bool show = true);
    
private:
    IControls* _controls;
    QWidget* _parent;

    SearchDataStore* _searchDataStore;

    QComboBox* _textFind;
    QComboBox* _textRepl;
    QCheckBox* _chkMatchCase;
    QCheckBox* _chkWholeWord;
    QPushButton* _btnClose;
    QPushButton* _btnNextSearch;
    QPushButton* _btnSearchAgain;
    QPushButton* _btnReplace;
    QPushButton* _btnReplaceAll;
    QPushButton* _btnSkipLoc;

    void AddSearchText(const QString &text);
    void AddReplaceText(const QString &text);

private slots:
    void OnCancelButton();
    void OnFindAgain();
    void OnFindNext();
    void OnFindRepl();
    void OnFindReplAll();
    void OnSkipLoc();
    void OnUpdFindText(const QString & text);
};

#endif // SEARCHDIALOG_H
