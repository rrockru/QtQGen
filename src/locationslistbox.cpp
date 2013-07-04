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

#include "locationslistbox.h"

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
    connect(this, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(OnItemExpanded(QTreeWidgetItem *)));
    connect(this, SIGNAL(itemCollapsed(QTreeWidgetItem *)), this, SLOT(OnItemCollapsed(QTreeWidgetItem *)));
    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected()));

    setDragDropMode(QAbstractItemView::InternalMove);
//    setSelectionMode(QAbstractItemView::SingleSelection);
//    setDragEnabled(true);
//    setAcceptDrops(true);
}

void LocationsListBox::AddFolder(const QString &folderName)
{
    if (_controls->GetSettings()->GetShowLocsIcons())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(folderName), DRAG_FOLDER);
        item->setIcon(0, QIcon(":/locslist/folder_closed"));
        addTopLevelItem(item);
    }
    else
        addTopLevelItem(new QTreeWidgetItem(QStringList(folderName), DRAG_FOLDER));
    _needForUpdate = true;
}

void LocationsListBox::Insert(const QString &name, const QString &pos, const QString &folder)
{
    //int image = -1;
    QTreeWidgetItem *prnt;

    if (!folder.isEmpty())
        prnt = GetFolderByName(folder);
    else
        prnt = invisibleRootItem();

    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(name), DRAG_LOCATION);
    if (_controls->GetSettings()->GetShowLocsIcons())
    {
        item->setIcon(0, QIcon(":/locslist/location_ball_closed"));
    }
    prnt->addChild(item);

    //if (pos.Length() > 0)
        //InsertItem(parent, GetLocByName(GetRootItem(), pos), name, image);

    _needForUpdate = true;
}

QTreeWidgetItem * LocationsListBox::GetFolderByName(const QString &name)
{
    for (int i = 0; i < topLevelItemCount(); i++)
    {
        QTreeWidgetItem *idCur = topLevelItem(i);
        if (idCur->text(0) == name)
            return idCur;
    }
    return NULL;
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
    QTreeWidgetItem *item = GetLocByName(NULL, name);
    if (item->parent() && !item->parent()->isExpanded())
        item->parent()->setExpanded(true);
    setCurrentItem(item);
    if (_controls->GetSettings()->GetShowLocsIcons())
    {
        item->setIcon(0, isOpened ? QIcon(":/locslist/location_ball_opened") : QIcon(":/locslist/location_ball_closed"));
    }
}

QTreeWidgetItem * LocationsListBox::GetLocByName(const QTreeWidgetItem *parent,const QString &name)
{
    int count = parent ? parent->childCount() : topLevelItemCount();

    for (int i = 0; i < count; i++)
    {
        QTreeWidgetItem *idCur = parent ? parent->child(i) : topLevelItem(i);
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
    return NULL;
}

void LocationsListBox::UpdateLocationActions(const QString &locName)
{
    QStringList actions;
    long locIndex = _controls->GetContainer()->FindLocationIndex(locName);
    _controls->GetContainer()->GetLocActions(locIndex, actions);
    size_t i, count = actions.count();
    QTreeWidgetItem *id = GetLocByName(invisibleRootItem(), locName);
    id->takeChildren();
    if (_controls->GetSettings()->GetShowLocsIcons())
        for (i = 0; i < count; ++i)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(actions.at(i)), DRAG_ACTION);
            item->setIcon(0, QIcon(":/locslist/action_ball"));
            id->addChild(item);
        }
    else
    {
        for (i = 0; i < count; ++i)
            id->addChild(new QTreeWidgetItem(QStringList(actions.at(i)), DRAG_ACTION));
    }

}

long LocationsListBox::GetItemType(QTreeWidgetItem *id)
{
    return id->type();
}

long LocationsListBox::GetItemPos(QTreeWidgetItem *parent, QTreeWidgetItem *id)
{
    if (parent)
        return parent->indexOfChild(id);
    else
        return indexOfTopLevelItem(id);
}

void LocationsListBox::UpdateDataContainer()
{
    long locPos = -1, folderPos = -1, pos = -1;
    UpdateDataContainer(NULL, -1, &locPos, &folderPos, &pos);
    _needForUpdate = false;
}

void LocationsListBox::UpdateDataContainer(QTreeWidgetItem *parent, long folder, long *locPos, long *folderPos, long *pos)
{
    DataContainer *container = _controls->GetContainer();
    int count = (parent == NULL ? topLevelItemCount(): parent->childCount());
    for (int i = 0; i < count; i++)
    {
        ++(*pos);
        QTreeWidgetItem *curItem = (parent == NULL ? topLevelItem(i) : parent->child(i));
        if (IsFolderItem(curItem))
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

    // TODO Уточнить, нужен ли цвет.
    //QPalette p = palette();
    //p.setColor(QPalette::Base, settings->GetBaseBackColor());
    //setPalette(p);

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
        if (!id->parent())
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

void LocationsListBox::SetLocName(const QString &name, const QString &newName)
{
    QTreeWidgetItem *id = GetLocByName(invisibleRootItem(), name);
    if (id)
        id->setText(0, newName);
}

void LocationsListBox::SetFolderName( const QString &name, const QString &newName )
{
    QTreeWidgetItem *id = GetFolderByName(name);
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
    int flags = 0;
    QTreeWidgetItem *id = itemAt(pos);
    bool isOk = IsItemOk(id, flags);
    if (isOk)
    {
        setFocus();
        setCurrentItem(id);
    }
    menu->addAction(tr("Create location..."), _controls->GetParent(), SLOT(OnCreateLocation()));
    if (isOk && id->type() == DRAG_LOCATION)
    {
        menu->addAction(tr("Rename \"%1\"...").arg(id->text(0)), _controls->GetParent(), SLOT(OnRenameLocation()));
        menu->addAction(tr("Delete \"%1\"").arg(id->text(0)), _controls->GetParent(), SLOT(OnDeleteLocation()));
    }
    menu->addSeparator();
    menu->addAction(tr("Create folder..."), _controls->GetParent(), SLOT(OnCreateFolder()));
    if (isOk && id->type() == DRAG_FOLDER)
    {
        menu->addAction(tr("Rename folder \"%1\"...").arg(id->text(0)), _controls->GetParent(), SLOT(OnRenameFolder()));
        menu->addAction(tr("Delete folder \"%1\"").arg(id->text(0)), _controls->GetParent(), SLOT(OnDeleteFolder()));
    }
//        menu->addSeparator();
//        if (isOk)
//            menu->addAction(tr("Copy"));
//        menu->addAction(tr("Paste"));
//        menu->addAction(tr("Replace"));
//        menu->addAction(tr("Paste in..."));
//        menu->addAction(tr("Clear"));
//        menu->addSeparator();
//        menu->addAction(tr("Sort ascending"));
//        menu->addAction(tr("Sort descending"));
//        menu->addSeparator();
//        menu->addAction(tr("Expand all"));
//        menu->addAction(tr("Collapse all"));
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

void LocationsListBox::Select(const QString &name)
{
    setCurrentItem(GetLocByName(invisibleRootItem(), name));
}

void LocationsListBox::OnItemExpanded(QTreeWidgetItem *item)
{
    if (IsFolderItem(item))
        item->setIcon(0, QIcon(":/locslist/folder_opened"));
}

void LocationsListBox::OnItemCollapsed(QTreeWidgetItem *item)
{
    if (IsFolderItem(item))
        item->setIcon(0, QIcon(":/locslist/folder_closed"));
}

void LocationsListBox::dragMoveEvent(QDragMoveEvent * event)
{
       event->acceptProposedAction();
}

void LocationsListBox::dragEnterEvent(QDragEnterEvent * event )
{
    event->acceptProposedAction();
}

void LocationsListBox::dropEvent(QDropEvent * event )
{
    //ApplyStatesImageList();
    QTreeWidgetItem *id = itemAt(event->pos());
    QString name = draggingItem->text(0);
    QIcon image = draggingItem->icon(0);
    if (!dynamic_cast<QTreeWidgetItem *>(id))
    {
        if (draggingItemType == DRAG_LOCATION)
        {
            QPoint p = event->pos();
            QSize size = this->size();
            if (p.x() >= 0 && p.y() >= 0 && p.x() < size.width() && p.y() < size.height())
            {
                delete draggingItem;
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(name), DRAG_LOCATION);
                item->setIcon(0, image);
                addTopLevelItem(item);
                setCurrentItem(item);
                UpdateLocationActions(name);
                _needForUpdate = true;
            }
        }
        return;
    }
    long pos;
    QTreeWidgetItem *parent = id->parent();
    long dropOnType = GetItemType(id);
    switch (draggingItemType)
    {
    case DRAG_FOLDER:
        switch (dropOnType)
        {
        case DRAG_LOCATION:
            if (parent) break;
        case DRAG_FOLDER:
            {
                _controls->SyncWithLocationsList();
                pos = GetItemPos(parent, id);
                delete draggingItem;
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(name), DRAG_FOLDER);
                item->setIcon(0, image);
                insertTopLevelItem(pos, item);
                setCurrentItem(item);
                UpdateFolderLocations(name);
                _needForUpdate = true;
                break;
            }
        }
        break;
    case DRAG_LOCATION:
        switch (dropOnType)
        {
        case DRAG_FOLDER:
            {
                delete draggingItem;
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(name), DRAG_LOCATION);
                item->setIcon(0, image);
                id->addChild(item);
                setCurrentItem(item);
                UpdateLocationActions(name);
                _needForUpdate = true;
                break;
            }
        case DRAG_LOCATION:
            {
                pos = GetItemPos(parent, id);
                delete draggingItem;
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(name), DRAG_LOCATION);
                item->setIcon(0, image);
                if (parent)
                    parent->insertChild(pos, item);
                else
                    insertTopLevelItem(pos, item);
                setCurrentItem(item);
                UpdateLocationActions(name);
                _needForUpdate = true;
                break;
            }
        }
        break;
    case DRAG_ACTION:
        switch (dropOnType)
        {
        case DRAG_ACTION:
            if (parent == draggingItem->parent())
            {
                long locIndex = _controls->GetContainer()->FindLocationIndex(parent->text(0));
                _controls->MoveActionTo(locIndex, GetItemPos(parent, draggingItem), GetItemPos(parent, id));
            }
            break;
        }
        break;
    }

}

void LocationsListBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) {
        draggingItem = itemAt(event->pos());
        if(dynamic_cast<QTreeWidgetItem *>(draggingItem))
        {
            draggingItemType = GetItemType(draggingItem);
//            QDrag *drag = new QDrag(this);
//            QMimeData *mimeData = new QMimeData;
//            drag->setMimeData(mimeData);
//            //drag->exec(Qt::CopyAction);
        }
    }
    QTreeWidget::mousePressEvent(event);
}

void LocationsListBox::UpdateFolderLocations( const QString &foldName )
{
    QString locName;
    QTreeWidgetItem *parent = GetFolderByName(foldName);
    parent->takeChildren();
    DataContainer *container = _controls->GetContainer();
    long folderIndex = container->FindFolderIndex(foldName);
    for (size_t i = 0; i < container->GetLocationsCount(); ++i)
    {
        if (container->GetLocFolder(i) == folderIndex)
        {
            locName = container->GetLocationName(i);
            if (_controls->GetSettings()->GetShowLocsIcons())
            {
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(locName), DRAG_LOCATION);
                item->setIcon(0, QIcon(":/locslist/location_ball_closed"));
                parent->addChild(item);
            }
            else
                parent->addChild(new QTreeWidgetItem(QStringList(locName), DRAG_LOCATION));
            UpdateLocationActions(locName);
        }
    }
    _controls->ShowOpenedLocationsIcons();
}

void LocationsListBox::OnItemSelected()
{
    _controls->Update();
}
