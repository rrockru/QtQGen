#include "stdafx.h"
#include "locationslistbox.h"

namespace Ui
{
	LocationsListBox::LocationsListBox(QWidget *parent, IControls *controls) : QTreeWidget(parent)
	{
		_controls = controls;
        _needForUpdate = false;

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
		int image = -1;
		QTreeWidgetItem *parent;
		if (folder.length() > 0)
			parent = GetFolderByName(folder);
		else
			parent = invisibleRootItem();
		if (_controls->GetSettings()->GetShowLocsIcons())
		{
			QTreeWidgetItem *item = new QTreeWidgetItem(parent, QStringList(name));
			item->setIcon(0, QIcon(":/locslist/location_ball_closed"));
			parent->addChild(item);
		}
		//if (pos.Length() > 0)
			//InsertItem(parent, GetLocByName(GetRootItem(), pos), name, image);
		else
			parent->addChild(new QTreeWidgetItem(parent, QStringList(name)));
	}

	QTreeWidgetItem * LocationsListBox::GetFolderByName(const QString &name)
	{
		QList<QTreeWidgetItem *> idCur = findItems(name, Qt::MatchExactly);
		if (!idCur.isEmpty() && IsFolderItem(idCur.at(0)))
		{
			return idCur.at(0);
		}
		return new QTreeWidgetItem;
	}

	void LocationsListBox::Clear()
	{
		clear();
	}


	bool LocationsListBox::IsFolderItem(QTreeWidgetItem *id)
	{
        if (id->childCount() > 0)
            return true;
        else
            return false;
	}

	void LocationsListBox::OnDoubleClicked(QTreeWidgetItem * item, int column)
	{
		switch (GetItemType(item))
		{
		case DRAG_LOCATION:
			_controls->ShowLocation(item->text(0));
			break;
		case DRAG_ACTION:
			QTreeWidgetItem *parent = item->parent();
			LocationPage *page = _controls->ShowLocation(parent->text(0));
			page->SelectAction(GetItemPos(parent, item));
			break;
		}
	}

	void LocationsListBox::SetLocStatus(const QString &name, bool isOpened)
	{
		if (_controls->GetSettings()->GetShowLocsIcons())
		{
			QTreeWidgetItem *item = GetLocByName(name);
			QIcon newIcon = isOpened ? QIcon(":/locslist/location_ball_opened") : QIcon(":/locslist/location_ball_closed");
			item->setIcon(0, newIcon);
		}
	}

	QTreeWidgetItem * LocationsListBox::GetLocByName(const QString &name)
	{
		QList<QTreeWidgetItem *> idCur = findItems(name, Qt::MatchExactly);
		/*while (idCur.IsOk())
		{
			if (IsFolderItem(idCur))
			{
				idCur = GetLocByName(idCur, name);
				if (idCur.IsOk()) return idCur;
			}
			else
			{
				if (GetItemText(idCur) == name) return idCur;
			}
			idCur = GetNextChild(parent, cookie);
		}*/
		if (!idCur.isEmpty())
		{
 			return idCur.at(0);
		}
		return new QTreeWidgetItem;
	}

	void LocationsListBox::UpdateLocationActions(const QString &name)
	{
		QStringList actions;
		long locIndex = _controls->GetContainer()->FindLocationIndex(name);
		_controls->GetContainer()->GetLocActions(locIndex, actions);
		size_t i, count = actions.count();
		QTreeWidgetItem *id = GetLocByName(name);
		for(i = 0; i < id->childCount(); i++)
			id->removeChild(id->child(i));
		if (_controls->GetSettings()->GetShowLocsIcons())
			for (i = 0; i < count; ++i) 
			{
				QTreeWidgetItem *item = new QTreeWidgetItem(id, QStringList(actions.at(i)));
				item->setIcon(0, QIcon(":/locslist/action_ball"));
				id->addChild(item);
			}
		else
		{
			for (i = 0; i < count; ++i) 
				id->addChild(new QTreeWidgetItem(id, QStringList(actions.at(i))));
		}
			
	}

	long LocationsListBox::GetItemType(QTreeWidgetItem *id)
	{
		if (!id->parent())
		{
			if (IsFolderItem(id))
				return DRAG_FOLDER;
			else
				return DRAG_LOCATION;
		}
		else
		{
			if (IsFolderItem(id->parent()))
				return DRAG_LOCATION;
			else
				return DRAG_ACTION;
		}
	}

	long LocationsListBox::GetItemPos(QTreeWidgetItem *parent, QTreeWidgetItem *id)
	{
		long pos = 0;

		for (pos; pos < parent->childCount(); pos++)
		{
			if (parent->child(pos) == id)
			{
				return pos;
			}
		}

		return -1;
	}


    void LocationsListBox::UpdateDataContainer()
    {
        long locPos = -1, folderPos = -1, pos = -1;
        UpdateDataContainer(invisibleRootItem(), -1, &locPos, &folderPos, &pos);
        _needForUpdate = false;
    }

    void LocationsListBox::UpdateDataContainer(QTreeWidgetItem *parent, long folder, long *locPos, long *folderPos, long *pos)
    {
        DataContainer *container = _controls->GetContainer();
        for (int i = 0; i < parent->childCount(); i++)
        {
            QTreeWidgetItem *curItem = parent->child(i);
            if (curItem->childCount() > 0)
            {
                ++(*folderPos);
                long curInd = container->FindFolderIndex(curItem->text(0));
                container->SetFolderPos(curInd, *pos);
                container->MoveFolder(curInd, *folderPos);
                UpdateDataContainer(curItem, *folderPos, locPos, folderPos, pos);
            }
            else
            {
                ++(*locPos);
                long curInd = container->FindLocationIndex(curItem->text(0));
                container->SetLocFolder(curInd, folder);
                container->MoveLocationTo(curInd, *locPos);
            }
        }
    }
}

