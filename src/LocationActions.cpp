#include "stdafx.h"
#include "LocationActions.h"

namespace Ui
{
	LocationActions::LocationActions(QWidget *parent, ILocationPage *locPage, IControls *controls) : QWidget(parent)
	{
		_controls = controls;
		_locPage = locPage;
		QSplitter *bottomSplit = new QSplitter(this);

		QHBoxLayout *boxLayout = new QHBoxLayout;
		_actCode = new ActionCode(this, _locPage, _controls);
		_actPanel = new ActionsPanel(this, _locPage, _actCode, _controls);	

		QWidget *actCode = new QWidget;
		QVBoxLayout *vBox = new QVBoxLayout;
		vBox->addWidget(new QLabel(tr("Action code"), this));
		vBox->addWidget(_actCode);
		actCode->setLayout(vBox);

		bottomSplit->addWidget(_actPanel);
		bottomSplit->addWidget(actCode);

		boxLayout->addWidget(bottomSplit);
		setLayout(boxLayout);

		setContentsMargins(0, 0, 0, 0);
		boxLayout->setContentsMargins(0, 0, 0, 0);
	}

	void LocationActions::LoadAllActions()
	{
		_actPanel->GetActionsListBox()->LoadAllActions();
		_actPanel->EnableButtons();
	}

	void LocationActions::SelectActionInList( size_t actIndex )
	{
		_actPanel->GetActionsListBox()->setFocus();
		_actPanel->GetActionsListBox()->Select( actIndex );
	}

    void LocationActions::SaveAction()
    {
        _actPanel->GetActionsListBox()->SaveActionData();
    }

    size_t LocationActions::AddActionToList(const QString &name)
    {
        size_t index = _actPanel->GetActionsListBox()->AddAction(name);
        _actPanel->EnableButtons();
        return index;
    }

    void LocationActions::SetFocusOnActionCode()
    {
        _actCode->SetFocusOnActionCode();
    }

    long LocationActions::GetSelectedAction()
    {
        return _actPanel->GetActionsListBox()->GetSelection();
    }

    void LocationActions::RenameActionInList( size_t index, const QString& name )
    {
        _actPanel->GetActionsListBox()->SetString(index, name);
    }

    void LocationActions::DeleteActionFromList( size_t actIndex )
    {
        _actPanel->GetActionsListBox()->DeleteAction(actIndex);
        _actPanel->EnableButtons();
    }
}
