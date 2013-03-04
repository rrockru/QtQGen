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
