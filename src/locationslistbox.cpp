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

        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnRightMouseButton(QPoint)));

        Update();

		connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(OnDoubleClicked(QTreeWidgetItem *, int)));
	}

	void LocationsListBox::AddFolder(QString &folderName)
	{
		if (_controls->GetSettings()->GetShowLocsIcons())
		{
            addTopLevelItem(new QTreeWidgetItem(invisibleRootItem(), QStringList(folderName), DRAG_FOLDER));
		}
		else
            addTopLevelItem(new QTreeWidgetItem(invisibleRootItem(), QStringList(folderName), DRAG_FOLDER));
	}

	void LocationsListBox::Insert(const QString &name, const QString &pos, const QString &folder)
	{
		int image = -1;
        QTreeWidgetItem *prnt;

        if (!folder.isEmpty())
            prnt = GetFolderByName(folder);
		else
            prnt = invisibleRootItem();
		if (_controls->GetSettings()->GetShowLocsIcons())
		{
            QTreeWidgetItem *item = new QTreeWidgetItem(prnt, QStringList(name), DRAG_LOCATION);
			item->setIcon(0, QIcon(":/locslist/location_ball_closed"));
            prnt->addChild(item);
		}
		//if (pos.Length() > 0)
			//InsertItem(parent, GetLocByName(GetRootItem(), pos), name, image);
		else
            prnt->addChild(new QTreeWidgetItem(prnt, QStringList(name), DRAG_LOCATION));
	}

	QTreeWidgetItem * LocationsListBox::GetFolderByName(const QString &name)
	{
        for (int i = 0; i < invisibleRootItem()->childCount(); i++)
        {
            QTreeWidgetItem *idCur = invisibleRootItem()->child(i);
            if (idCur->text(0) == name)
                return idCur;
        }
		return new QTreeWidgetItem;
	}

	void LocationsListBox::Clear()
	{
		clear();
	}


	bool LocationsListBox::IsFolderItem(QTreeWidgetItem *id)
	{
        if (id->type() == DRAG_FOLDER)
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
            QTreeWidgetItem *item = GetLocByName(invisibleRootItem(), name);
            item->setIcon(0, isOpened ? QIcon(":/locslist/location_ball_opened") : QIcon(":/locslist/location_ball_closed"));
		}
	}

    QTreeWidgetItem * LocationsListBox::GetLocByName(const QTreeWidgetItem *parent,const QString &name)
	{
        for (int i = 0; i < parent->childCount(); i++)
        {
            QTreeWidgetItem *idCur = parent->child(i);
            if (IsFolderItem(idCur))
            {
                idCur = GetLocByName(idCur, name);
                if (idCur != NULL) return idCur;
            }
            else
            {
                if (idCur->text(0) == name) return idCur;
            }
        }
        return new QTreeWidgetItem;
	}

	void LocationsListBox::UpdateLocationActions(const QString &name)
	{
		QStringList actions;
		long locIndex = _controls->GetContainer()->FindLocationIndex(name);
		_controls->GetContainer()->GetLocActions(locIndex, actions);
		size_t i, count = actions.count();
        QTreeWidgetItem *id = GetLocByName(invisibleRootItem(), name);
		for(i = 0; i < id->childCount(); i++)
			id->removeChild(id->child(i));
		if (_controls->GetSettings()->GetShowLocsIcons())
			for (i = 0; i < count; ++i) 
			{
                QTreeWidgetItem *item = new QTreeWidgetItem(id, QStringList(actions.at(i)), DRAG_ACTION);
				item->setIcon(0, QIcon(":/locslist/action_ball"));
				id->addChild(item);
			}
		else
		{
			for (i = 0; i < count; ++i) 
                id->addChild(new QTreeWidgetItem(id, QStringList(actions.at(i)), DRAG_ACTION));
		}
			
	}

	long LocationsListBox::GetItemType(QTreeWidgetItem *id)
	{
        return id->type();
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

    void LocationsListBox::Update(bool isFromObservable)
    {
        Settings *settings = _controls->GetSettings();
        //SetFont(settings->GetFont(SYNTAX_BASE));
        //SetForegroundColour(settings->GetColour(SYNTAX_BASE));
        QPalette p = palette();
        p.setColor(QPalette::Base, settings->GetBaseBackColor());
        setPalette(p);
        //ApplyStatesImageList();
        if (isFromObservable)
        {
            _controls->SyncWithLocationsList();
            _controls->UpdateLocationsList();
        }
    }

    QString LocationsListBox::GetStringSelection()
    {
        QTreeWidgetItem *id = currentItem();

        if (id)
        {
            if (id->parent() == 0)
            {
                if (!IsFolderItem(id))
                    return id->text(0);
            }
            else
            {
                QTreeWidgetItem *parent(id->parent());
                if (parent)
                {
                    if (IsFolderItem(parent))
                        return id->text(0);
                    else
                        return parent->text(0);
                }
            }
        }
        return "";
    }

    QString LocationsListBox::GetSelectedFolder()
    {
        QTreeWidgetItem *id = currentItem();
        if (id)
        {
            if (id->parent() == 0)
            {
                if (IsFolderItem(id))
                    return id->text(0);
            }
            else
            {
                QTreeWidgetItem *parent = id->parent();
                if (parent)
                {
                    if (IsFolderItem(parent))
                        return parent->text(0);
                    else
                        return parent->parent()->text(0);

                }
            }
        }
        return "";
    }

    void LocationsListBox::SetLocName( const QString &name, const QString &newName )
    {
        QTreeWidgetItem *id = GetLocByName(invisibleRootItem(), name);
        if (id)
            id->setText(0, newName);
    }

    void LocationsListBox::Delete(const QString &name)
    {
        QTreeWidgetItem *id = GetLocByName(invisibleRootItem(), name);
        if (id)
        {
            delete id;
            _needForUpdate = true;
        }
    }

    void LocationsListBox::OnRightMouseButton(const QPoint &pos)
    {
        QMenu *menu = new QMenu(this);
        int flags;
        QTreeWidgetItem *id = itemAt(pos);
        bool isOk = IsItemOk(id, flags);
        if (isOk)
        {
            setFocus();
            setCurrentItem(id);
        }
        menu->addAction(tr("Create location..."), _controls->GetParent(), SLOT(OnCreateLocation()));
        if(isOk && id->type() == DRAG_LOCATION)
        {
            menu->addAction(tr("Rename \"%1\"...").arg(id->text(0)), _controls->GetParent(), SLOT(OnRenameLocation()));
            menu->addAction(tr("Delete \"%1\"").arg(id->text(0)), _controls->GetParent(), SLOT(OnDeleteLocation()));
        }
        menu->addSeparator();
        menu->addAction(tr("Create folder..."));
        if(isOk && id->type() == DRAG_FOLDER)
        {
            menu->addAction(tr("Rename folder..."));
            menu->addAction(tr("Delete folder"));
        }
        menu->addSeparator();
        if(isOk)
            menu->addAction(tr("Copy"));
        menu->addAction(tr("Paste"));
        menu->addAction(tr("Replace"));
        menu->addAction(tr("Paste in..."));
        menu->addAction(tr("Clear"));
        menu->addSeparator();
        menu->addAction(tr("Sort ascending"));
        menu->addAction(tr("Sort descending"));
        menu->addSeparator();
        menu->addAction(tr("Expand all"));
        menu->addAction(tr("Collapse all"));
        //_controls->UpdateMenuItems(&menu);
        menu->popup(this->mapToGlobal(pos));
    }

    bool LocationsListBox::IsItemOk(QTreeWidgetItem *id, int flags)
    {
        if (id)
            return true;
        else
            return false;
    }
}

