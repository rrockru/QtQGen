#ifndef _ACTIONS_LIST_
#define _ACTIONS_LIST_

#include "IControls.h"
#include "actioncode.h"
#include "ilocationpage.h"

namespace Ui
{
	class ActionsList :
		public QListWidget
	{
		Q_OBJECT

	public:
		ActionsList(QWidget *parent, ILocationPage *locPage, ActionCode *actCode, IControls *controls);

		void LoadAllActions();
		void DeleteAllActions();

		void Select(int);

		void LoadActionData(size_t actIndex);
		void SaveActionData();

        size_t AddAction(const QString& name);
        int GetSelection() const;
        QString GetString( size_t index ) const;
        void SetString( size_t index, const QString & name );
        void DeleteAction( size_t actIndex );

	private:
		IControls *_controls;
		ILocationPage *_locPage;
		ActionCode *_actCode;

		int _prevActionIndex;

		private slots:
            void OnItemChanged(QListWidgetItem * item);
            void OnRightMouseButton(const QPoint &pos);

	};
} // namespace Ui

#endif // _ACTIONS_LIST_
