#ifndef _LOCATIONS_LIST_BOX_
#define _LOCATIONS_LIST_BOX_

#include "IControls.h"
#include "locationpage.h"

namespace Ui
{
	enum
	{
		DRAG_ACTION,
		DRAG_LOCATION,
		DRAG_FOLDER,
	};

	class FolderItem : public QTreeWidgetItem
	{
	};

	class LocationsListBox :
		public QTreeWidget
	{
		Q_OBJECT

	public:
		LocationsListBox(QWidget *parent, IControls *controls);

		void AddFolder(QString &);
		void Insert(const QString &name, const QString &pos, const QString &folder);
		void Clear();

		void SetLocStatus(const QString &name, bool isOpened);
		void UpdateLocationActions(const QString &name);


	private:
		QTreeWidgetItem *GetFolderByName(const QString &name);
		bool IsFolderItem(QTreeWidgetItem *id);
		QTreeWidgetItem *GetLocByName(const QString &name);

		long GetItemType(QTreeWidgetItem *);
		long GetItemPos(QTreeWidgetItem *parent, QTreeWidgetItem *id);

		IControls *_controls;

		private slots:
			void OnDoubleClicked(QTreeWidgetItem * item, int column);

	};
} // namespace Ui

#endif // _LOCATIONS_LIST_BOX_