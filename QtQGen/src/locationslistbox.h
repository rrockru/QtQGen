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

	private:
		QListWidgetItem *GetFolderByName(const QString &name);
		bool IsFolderItem(const QTreeWidgetItem &id);

		IControls *_controls;

		private slots:
			void OnDoubleClicked(QTreeWidgetItem * item, int column);

	};
} // namespace Ui

#endif // _LOCATIONS_LIST_BOX_