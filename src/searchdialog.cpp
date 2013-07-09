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

#include "searchdialog.h"

SearchDialog::SearchDialog(IControls *controls, QString title, QWidget *parent) :
    QDialog(parent)
{
    _controls = controls;
    _parent = parent;

    setWindowTitle(title);

    Settings *settings = _controls->GetSettings();
    _searchDataStore = settings->GetSearchDataStore();

    QVBoxLayout* leftLayout = new QVBoxLayout;
    QVBoxLayout* rightLayout = new QVBoxLayout;
    QHBoxLayout* topLayout = new QHBoxLayout;

    _textFind = new QComboBox(this);
    _textFind->setEditable(true);
    _textFind->addItems(_searchDataStore->GetSearchStrings());
    connect(_textFind, SIGNAL(currentTextChanged(QString)), this, SLOT(OnUpdFindText(QString)));
    connect(_textFind->lineEdit(), SIGNAL(returnPressed()), this, SLOT(OnFindNext()));
    _textRepl = new QComboBox(this);
    _textRepl->setEditable(true);
    _textRepl->addItems(_searchDataStore->GetReplaceStrings());
    connect(_textRepl->lineEdit(), SIGNAL(returnPressed()), this, SLOT(OnFindRepl()));
    if (_textFind->count()) _textFind->setCurrentIndex(0);
    if (_textRepl->count()) _textRepl->setCurrentIndex(0);
    _chkMatchCase = new QCheckBox(tr("Match case"), this);
    _chkWholeWord = new QCheckBox(tr("Search only word"), this);

    leftLayout->addWidget(_textFind);
    leftLayout->addWidget(_textRepl);
    leftLayout->addWidget(_chkMatchCase);
    leftLayout->addWidget(_chkWholeWord);
    leftLayout->addStretch();

    _btnSearchAgain = new QPushButton(tr("New search"), this);
    connect(_btnSearchAgain, SIGNAL(clicked()), this, SLOT(OnFindAgain()));
    _btnNextSearch = new QPushButton(tr("Continue search"), this);
    connect(_btnNextSearch, SIGNAL(clicked()), this, SLOT(OnFindNext()));
    _btnSkipLoc = new QPushButton(tr("Skip location"), this);
    connect(_btnSkipLoc, SIGNAL(clicked()), this, SLOT(OnSkipLoc()));
    _btnReplace = new QPushButton(tr("Replace"), this);
    connect(_btnReplace, SIGNAL(clicked()), this, SLOT(OnFindRepl()));
    _btnReplaceAll = new QPushButton(tr("Replace all"), this);
    connect(_btnReplaceAll, SIGNAL(clicked()), this, SLOT(OnFindReplAll()));
    _btnClose = new QPushButton(tr("Cancel"), this);
    connect(_btnClose, SIGNAL(clicked()), this, SLOT(OnCancelButton()));

    rightLayout->addWidget(_btnNextSearch);
    rightLayout->addWidget(_btnSearchAgain);
    rightLayout->addWidget(_btnReplace);
    rightLayout->addWidget(_btnReplaceAll);
    rightLayout->addWidget(_btnSkipLoc);
    rightLayout->addSpacing(10);
    rightLayout->addWidget(_btnClose);

    topLayout->addLayout(leftLayout, 1);
    topLayout->addLayout(rightLayout);

    setLayout(topLayout);

    setMaximumSize(2048, 200);
    setMinimumSize(350, 200);

    OnUpdFindText(_textFind->currentText());
    _btnNextSearch->setDefault(true);
}

bool SearchDialog::Show(bool show)
{
    setVisible(show);
    if (show)
            _textFind->setFocus();
        else
            _parent->setFocus();
    return true;
}

void SearchDialog::OnCancelButton()
{
    Show(false);
}

void SearchDialog::OnFindAgain()
{
    QString str = _textFind->currentText();
    _controls->SearchString(str, true,
        _chkMatchCase->isChecked(),
        _chkWholeWord->isChecked());
    AddSearchText(str);
    _textFind->setFocus();
    _btnNextSearch->setDefault(true);
}

void SearchDialog::OnFindNext()
{
    QString str = _textFind->currentText();
    _controls->SearchString(str, false,
        _chkMatchCase->isChecked(),
        _chkWholeWord->isChecked());
    AddSearchText(str);
    _textFind->setFocus();
    _btnNextSearch->setDefault(true);
}

void SearchDialog::AddSearchText(const QString &text)
{
    _searchDataStore->AddSearchString(text);
    if (_textFind->count() && _textFind->itemText(0) == text)
        return;
    _textFind->insertItem(0, text);
}

void SearchDialog::AddReplaceText(const QString &text)
{
    _searchDataStore->AddReplaceString(text);
    if (_textRepl->count() && _textRepl->itemText(0) == text)
        return;
    _textRepl->insertItem(0, text);
}

void SearchDialog::OnSkipLoc()
{
    QString str = _textFind->currentText();
    if (_controls->SearchNextLoc())
        _controls->SearchString(str, false,
            _chkMatchCase->isChecked(),
            _chkWholeWord->isChecked());
    AddSearchText(str);
    _textFind->setFocus();
    _btnNextSearch->setDefault(true);
}

void SearchDialog::OnFindRepl()
{
    QString str = _textRepl->currentText();
    _controls->ReplaceSearchString(str);
    OnFindNext();
    AddReplaceText(str);
    _textRepl->setFocus();
    _btnNextSearch->setDefault(true);
}

void SearchDialog::OnFindReplAll()
{
    QString str = _textRepl->currentText();
    _controls->ReplaceSearchString(str);
    QString str1 = _textFind->currentText();
    bool flag = _controls->SearchString(str1, true,
        _chkMatchCase->isChecked(),
        _chkWholeWord->isChecked());
    AddSearchText(str1);
    AddReplaceText(str);
    while (flag)
    {
        _controls->ReplaceSearchString(str);
        flag = _controls->SearchString(str1, false,
                _chkMatchCase->isChecked(),
                _chkWholeWord->isChecked());
    }
    _textRepl->setFocus();
    _btnNextSearch->setDefault(true);
}

void SearchDialog::OnUpdFindText(const QString &text)
{
    bool status = !_textFind->currentText().isEmpty();
    _btnNextSearch->setEnabled(status);
    _btnSearchAgain->setEnabled(status);
    _btnSkipLoc->setEnabled(status);
    _btnReplace->setEnabled(status);
    _btnReplaceAll->setEnabled(status);
}
