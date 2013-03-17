#ifndef _LOCATIONS_LIST_BOX_
#define _LOCATIONS_LIST_BOX_

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

		void AddFolder(QString &);
		void Insert(const QString &name, const QString &pos, const QString &folder);
		void Clear();
        void Update(bool isFromObservable = false);
        void Delete(const QString &name);

		void SetLocStatus(const QString &name, bool isOpened);
		void UpdateLocationActions(const QString &name);
        bool IsNeedForUpdate() const { return _needForUpdate; }

        void UpdateDataContainer();
        QString LocationsListBox::GetStringSelection();
        QString LocationsListBox::GetSelectedFolder();

        void SetLocName( const QString &name, const QString &newName );

	private:
		QTreeWidgetItem *GetFolderByName(const QString &name);
		bool IsFolderItem(QTreeWidgetItem *id);
        QTreeWidgetItem *GetLocByName(const QTreeWidgetItem *parent, const QString &name);

		long GetItemType(QTreeWidgetItem *);
		long GetItemPos(QTreeWidgetItem *parent, QTreeWidgetItem *id);

        void UpdateDataContainer(QTreeWidgetItem *parent, long folder, long *locPos, long *folderPos, long *pos);

		IControls *_controls;

        bool _needForUpdate;

		private slots:
			void OnDoubleClicked(QTreeWidgetItem * item, int column);

	};
} // namespace Ui

#endif // _LOCATIONS_LIST_BOX_
