#include "stdafx.h"
#include "locationpage.h"

namespace Ui
{
	LocationPage::LocationPage(QWidget *parent, IControls *controls) : QWidget(parent)
	{
		_controls = controls;

		_locDesc = new LocationDesc(this, this, _controls);
		_locCode = new LocationCode(this, this, _controls);
		_locActs = new LocationActions(this, this, _controls);

		QHBoxLayout *hbox = new QHBoxLayout;
		QSplitter *topSplit = new QSplitter(this);
		
		QSplitter *vertSplit = new QSplitter(Qt::Vertical, this);

		topSplit->addWidget(_locDesc);
		topSplit->addWidget(_locCode);
		

		vertSplit->addWidget(topSplit);
		vertSplit->addWidget(_locActs);

		hbox->addWidget(vertSplit);
		setLayout(hbox);
	}

	void LocationPage::SetLocationIndex(size_t locIndex)
	{
		_locIndex = locIndex;
	}

	size_t LocationPage::GetLocationIndex()
	{
		return _locIndex;
	}

	void LocationPage::LoadPage()
	{
		_locDesc->LoadDesc();
		_locCode->LoadCode();
		_locActs->LoadAllActions();
	}

	void LocationPage::ExpandCollapseAll(bool isExpanded)
	{

	}

	void LocationPage::SelectAction( size_t actIndex )
	{
		_locActs->SelectActionInList( actIndex );
	}

    void LocationPage::SavePage()
    {
        _locDesc->SaveDesc();
        _locCode->SaveCode();
        _locActs->SaveAction();
    }

    size_t LocationPage::AddAction(const QString &name)
    {
        return _locActs->AddActionToList(name);
    }

    void LocationPage::SetFocusOnActionCode()
    {
        _locActs->SetFocusOnActionCode();
    }

    long LocationPage::GetSelectedAction()
    {
        return _locActs->GetSelectedAction();
    }

    void LocationPage::RenameAction( size_t actIndex, const QString& name )
    {
        _locActs->RenameActionInList(actIndex, name);
    }

    void LocationPage::DeleteAction( size_t actIndex )
    {
        _locActs->DeleteActionFromList(actIndex);
    }
}
