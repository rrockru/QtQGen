#include "stdafx.h"
#include "locationslistbox.h"

namespace Ui
{
	LocationsListBox::LocationsListBox(QWidget *parent, IControls *controls) : QTreeWidget(parent)
	{
		_controls = controls;
		setSortingEnabled(false);
		setColumnCount(1);
		headerItem()->setHidden(true);
		connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(OnDoubleClicked(QTreeWidgetItem *, int)));
	}

	void LocationsListBox::AddFolder(QString &folderName)
	{
		if (_controls->GetSettings()->GetShowLocsIcons())
		{
			addTopLevelItem(new QTreeWidgetItem(this, QStringList(folderName)));
		}
		else
			addTopLevelItem(new QTreeWidgetItem(this, QStringList(folderName)));
	}

	void LocationsListBox::Insert(const QString &name, const QString &pos, const QString &folder)
	{
		/*
		int image = -1;
		QListWidgetItem *parent;
		if (folder.length() > 0)
			parent = GetFolderByName(folder);
		else
			parent = GetRootItem();
			*/
		if (_controls->GetSettings()->GetShowLocsIcons())
		{
			QTreeWidgetItem *item = new QTreeWidgetItem(this, QStringList(name));
			item->setIcon(0, QIcon(":/locslist/location_ball_closed"));
			addTopLevelItem(item);

		}
		//if (pos.Length() > 0)
			//InsertItem(parent, GetLocByName(GetRootItem(), pos), name, image);
		else
			addTopLevelItem(new QTreeWidgetItem(this, QStringList(name)));
	}

	QListWidgetItem * LocationsListBox::GetFolderByName(const QString &name)
	{
		return new QListWidgetItem;
	}

	void LocationsListBox::Clear()
	{
		clear();
	}


	bool LocationsListBox::IsFolderItem(const QTreeWidgetItem &id)
	{
// 		FolderItem *data = dynamic_cast<FolderItem *>(id);
// 		return (data != NULL);
		return true;
	}

	void LocationsListBox::OnDoubleClicked(QTreeWidgetItem * item, int column)
	{
// 		switch (GetItemType(id))
// 		{
// 		case DRAG_LOCATION:
// 			_controls->ShowLocation(GetItemText(id));
// 			break;
// 		case DRAG_ACTION:
// 			wxTreeItemId parent(GetItemParent(id));
// 			LocationPage *page = _controls->ShowLocation(GetItemText(parent));
// 			page->SelectAction(GetItemPos(parent, id));
// 			break;
		
//		}
		_controls->ShowLocation(item->text(0));
	}
}

