#include "stdafx.h"
#include "actionslist.h"

namespace Ui
{
	ActionsList::ActionsList(QWidget *parent, ILocationPage *locPage, ActionCode *actCode, IControls *controls) : QListWidget(parent)
	{
		_controls = controls;
		_locPage = locPage;
		_actCode = actCode;

		setSortingEnabled(false);

		connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(OnItemChanged(QListWidgetItem *)));
	}

	void ActionsList::LoadAllActions()
	{
		DataContainer *container = _controls->GetContainer();
		size_t actionsCount, locIndex = _locPage->GetLocationIndex();
		DeleteAllActions();
		actionsCount = container->GetActionsCount(locIndex);
		for (size_t i = 0; i < actionsCount; ++i)
			addItem(container->GetActionName(locIndex, i));
		if (actionsCount)
		{
			Select(0);
			setCurrentRow(0);
		}
	}

	void ActionsList::DeleteAllActions()
	{
		clear();
		_actCode->ClearAction();
		_prevActionIndex = -1;
	}

	void ActionsList::Select(int index)
	{
		SaveActionData();
		LoadActionData(index);
		_prevActionIndex = index;
	}

	void ActionsList::LoadActionData(size_t actIndex)
	{
		Settings *settings = _controls->GetSettings();
		_actCode->LoadAction(actIndex);
		/*if (settings->GetCollapseCode())
			_actCode->ExpandCollapseAll(false);*/
	}

	void ActionsList::SaveActionData()
	{
		/*if (_prevActionIndex >= 0)
			_actCode->SaveAction(_prevActionIndex);*/
	}

	void ActionsList::OnItemChanged(QListWidgetItem * item)
	{
		int index = row(item);
		if (index != _prevActionIndex) Select(index);
	}
}
