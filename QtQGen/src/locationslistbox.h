#ifndef _LOCATIONS_LIST_BOX_
#define _LOCATIONS_LIST_BOX_

#include "IControls.h"

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


	private:
		QListWidgetItem *GetFolderByName(const QString &name);
		bool IsFolderItem(QTreeWidgetItem *id);
		QTreeWidgetItem *GetLocByName(const QString &name);

		IControls *_controls;

		private slots:
			void OnDoubleClicked(QTreeWidgetItem * item, int column);

	};
} // namespace Ui

#endif // _LOCATIONS_LIST_BOX_