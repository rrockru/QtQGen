#include "stdafx.h"
#include "ActionsPanel.h"

namespace Ui
{
	ActionsPanel::ActionsPanel(QWidget *parent, ILocationPage *locPage, ActionCode *actCode, IControls *controls ) : QWidget(parent)
	{
		_controls = controls;

		QVBoxLayout *vBox = new QVBoxLayout;
		QHBoxLayout *hBox = new QHBoxLayout;

		_actsList = new ActionsList(this, locPage, actCode, _controls);

		newButton = new QToolButton;
		newButton->setIcon(QIcon(":/actions/new"));
		newButton->setFixedSize(32, 26);
		newButton->setIconSize(QSize(24, 24));
        connect(newButton, SIGNAL(clicked()), _controls->GetParent(), SLOT(OnAddAction()));

		renameButton = new QToolButton;
		renameButton->setIcon(QIcon(":/actions/rename"));
		renameButton->setFixedSize(32, 26);
		renameButton->setIconSize(QSize(24, 24));
        connect(renameButton, SIGNAL(clicked()), _controls->GetParent(), SLOT(OnRenAction()));

		deleteButton = new QToolButton;
		deleteButton->setIcon(QIcon(":/actions/delete"));
		deleteButton->setFixedSize(32, 26);
		deleteButton->setIconSize(QSize(24, 24));
        connect(deleteButton, SIGNAL(clicked()), _controls->GetParent(), SLOT(OnDelAction()));

		hBox->addWidget(newButton);
		hBox->addWidget(renameButton);
		hBox->addWidget(deleteButton);
		hBox->addStretch();

		vBox->addLayout(hBox);
		vBox->addWidget(_actsList);

		setLayout(vBox);
	}

	void ActionsPanel::EnableButtons()
	{
		bool isAnyAction = (_actsList->count() > 0);
		renameButton->setEnabled(isAnyAction);
		deleteButton->setEnabled(isAnyAction);
	}
}



