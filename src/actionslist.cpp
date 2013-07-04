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

#include "actionslist.h"

ActionsList::ActionsList(QWidget *parent, ILocationPage *locPage, ActionCode *actCode, IControls *controls) : QListWidget(parent)
{
    _controls = controls;
    _locPage = locPage;
    _actCode = actCode;

    setSortingEnabled(false);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDragDropMode(QAbstractItemView::InternalMove);

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnRightMouseButton(QPoint)));
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
    setCurrentRow(index);
    _prevActionIndex = index;
}

void ActionsList::LoadActionData(size_t actIndex)
{
    //Settings *settings = _controls->GetSettings();
    _actCode->LoadAction(actIndex);
    /*if (settings->GetCollapseCode())
        _actCode->ExpandCollapseAll(false);*/
}

void ActionsList::SaveActionData()
{
    if (_prevActionIndex >= 0)
        _actCode->SaveAction(_prevActionIndex);
}

void ActionsList::OnItemChanged(QListWidgetItem * item)
{
    int index = row(item);
    if (index != _prevActionIndex) Select(index);
}

size_t ActionsList::AddAction(const QString &name)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setText(name);
    addItem(item);
    size_t idx = row(item);
    if (count() == 1)
    {
        Select(0);
        setCurrentRow(0);
    }
    return idx;
}

int ActionsList::GetSelection() const
{
    return _prevActionIndex;
}

QString ActionsList::GetString(size_t index) const
{
    return item(index)->text();
}

void ActionsList::SetString(size_t index, const QString & name)
{
    item(index)->setText(name);
}

void ActionsList::DeleteAction(size_t actIndex)
{
    delete item(actIndex);
    _actCode->ClearAction();
    _prevActionIndex = -1;
    size_t cnt = count();
    if (cnt > 0)
    {
        if (actIndex == cnt) actIndex = cnt - 1;
        Select(actIndex);
    }
}

void ActionsList::OnRightMouseButton(const QPoint &pos)
{
    QMenu *menu = new QMenu(this);
    long ind = -1;
    QListWidgetItem *id = itemAt(pos);
    if (id)
        ind = row(id);
    if (ind >= 0 && ind != _prevActionIndex)
    {
        setFocus();
        Select(ind);
    }
    menu->addAction(tr("Create action..."), _controls->GetParent(), SLOT(OnAddAction()));
    if (id)
    {
        menu->addAction(tr("Rename \"%1\"...").arg(id->text()), _controls->GetParent(), SLOT(OnRenAction()));
        menu->addAction(tr("Delete \"%1\"").arg(id->text()), _controls->GetParent(), SLOT(OnDelAction()));
    }
    if (count() > 0)
    {
        menu->addSeparator();
        menu->addAction(tr("Delete all"), _controls->GetParent(), SLOT(OnDelAllActions()));
    }
    //_controls->UpdateMenuItems(&menu);
    menu->popup(this->mapToGlobal(pos));
}

void ActionsList::MoveItemTo( size_t actIndex, size_t moveTo )
{
    QString label(GetString(actIndex));
    takeItem(actIndex);
    insertItem(moveTo, label);
    Select(moveTo);
}

void ActionsList::dragMoveEvent(QDragMoveEvent * event)
{
       event->acceptProposedAction();
}

void ActionsList::dragEnterEvent(QDragEnterEvent * event )
{
    event->acceptProposedAction();
}

void ActionsList::dropEvent(QDropEvent * event )
{
    QListWidgetItem *id = itemAt(event->pos());
    if(dynamic_cast<QListWidgetItem *>(id))
    {
        _controls->MoveActionTo(_locPage->GetLocationIndex(), row(draggingItem), row(id));
    }
}

void ActionsList::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton) {
        draggingItem = itemAt(event->pos());
    }
    QListWidget::mousePressEvent(event);
}
