#include "stdafx.h"
#include "actionslist.h"

namespace Ui
{
	ActionsList::ActionsList() : QWidget()
	{
		QVBoxLayout *vBox = new QVBoxLayout;
		QHBoxLayout *hBox = new QHBoxLayout;


		QToolButton *newButton = new QToolButton;
		newButton->setIcon(QIcon(":/actions/new"));
		newButton->setFixedSize(32, 26);
		newButton->setIconSize(QSize(24, 24));

		QToolButton *renameButton = new QToolButton;
		renameButton->setIcon(QIcon(":/actions/rename"));
		renameButton->setFixedSize(32, 26);
		renameButton->setIconSize(QSize(24, 24));

		QToolButton *deleteButton = new QToolButton;
		deleteButton->setIcon(QIcon(":/actions/delete"));
		deleteButton->setFixedSize(32, 26);
		deleteButton->setIconSize(QSize(24, 24));

		hBox->addWidget(newButton);
		hBox->addWidget(renameButton);
		hBox->addWidget(deleteButton);
		hBox->addStretch();

		vBox->addLayout(hBox);
		vBox->addWidget(new QListWidget);

		setLayout(vBox);

		adjustSize();
	}
}
