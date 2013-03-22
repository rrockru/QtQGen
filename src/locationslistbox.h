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

#ifndef _LOCATIONS_LIST_BOX_
#define _LOCATIONS_LIST_BOX_

#include <QTreeWidget>

#include "IControls.h"
#include "locationpage.h"

namespace Ui
{
	enum
	{
        DRAG_ACTION = 1000,
		DRAG_LOCATION,
		DRAG_FOLDER,
	};

	class LocationsListBox :
		public QTreeWidget
	{
		Q_OBJECT

	public:
		LocationsListBox(QWidget *parent, IControls *controls);

        void AddFolder(const QString &);
		void Insert(const QString &name, const QString &pos, const QString &folder);
		void Clear();
        void Update(bool isFromObservable = false);
        void Delete(const QString &name);

		void SetLocStatus(const QString &name, bool isOpened);
		void UpdateLocationActions(const QString &name);
        bool IsNeedForUpdate() const { return _needForUpdate; }

        void UpdateDataContainer();
        QString GetStringSelection();
        QString GetSelectedFolder();

        void SetLocName( const QString &name, const QString &newName );

	private:
		QTreeWidgetItem *GetFolderByName(const QString &name);
		bool IsFolderItem(QTreeWidgetItem *id);
        QTreeWidgetItem *GetLocByName(const QTreeWidgetItem *parent, const QString &name);

		long GetItemType(QTreeWidgetItem *);
		long GetItemPos(QTreeWidgetItem *parent, QTreeWidgetItem *id);

        void UpdateDataContainer(QTreeWidgetItem *parent, long folder, long *locPos, long *folderPos, long *pos);

        bool IsItemOk(QTreeWidgetItem *id, int flags);

		IControls *_controls;

        bool _needForUpdate;

		private slots:
			void OnDoubleClicked(QTreeWidgetItem * item, int column);
            void OnRightMouseButton(const QPoint & pos);

	};
} // namespace Ui

#endif // _LOCATIONS_LIST_BOX_
