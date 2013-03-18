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

#include "stdafx.h"
#include "mergedialog.h"

namespace Ui
{
	MergeDialog::MergeDialog(QWidget *parent, const QString& title, const QString &message) : QDialog(parent)
	{
		setWindowTitle(title);
		QVBoxLayout *topSizer = new QVBoxLayout;
		QHBoxLayout *msgSizer = new QHBoxLayout;
		QHBoxLayout *buttonSizer = new QHBoxLayout;

		QPixmap info_icon = style()->standardPixmap(QStyle::SP_MessageBoxInformation);
		QLabel *icon_label = new QLabel;
		icon_label->setPixmap(info_icon);

		QLabel *msgText = new QLabel(message, this);

		_replace = new QPushButton(tr("Replace"), this);
		connect(_replace, SIGNAL(clicked()), this, SLOT(OnReplace()));
		_skip = new QPushButton(tr("Skip"), this);
		connect(_skip, SIGNAL(clicked()), this, SLOT(OnSkip()));
		_cancel = new QPushButton(tr("Cancel"), this);
		connect(_cancel, SIGNAL(clicked()), this, SLOT(OnCancel()));

		_chkToAll= new QCheckBox(tr("for all"), this);

		msgSizer->addWidget(icon_label);
		msgSizer->addSpacing(8);
		msgSizer->addWidget(msgText);
		buttonSizer->addWidget(_replace);
		buttonSizer->addWidget(_skip);
		buttonSizer->addWidget(_cancel);
		buttonSizer->addWidget(_chkToAll);

		topSizer->addLayout(msgSizer);
		topSizer->addLayout(buttonSizer);
	}

	void MergeDialog::OnReplace()
	{
		int ret = MERGE_REPLACE;
		Done(ret);
	}
	void MergeDialog::OnSkip()
	{
		int ret = MERGE_SKIP;
		Done(ret);
	}
	void MergeDialog::OnCancel()
	{
		int ret = MERGE_CANCEL;
		Done(ret);
	}

	void MergeDialog::Done(int res)
	{
		if (_chkToAll->isChecked())
		{
			res |=MERGE_ALL;
		}
		done(res);
	}
}
