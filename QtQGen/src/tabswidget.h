#ifndef _TABS_WIDGET_
#define _TABS_WIDGET_

#include "locationpage.h"

namespace Ui
{
	class TabsWidget :
		public QTabWidget
	{
		Q_OBJECT

	public:
		TabsWidget(QWidget *parent, IControls *controls);

		void CloseAll();
		int FindPageIndex(const QString& pageName);
		LocationPage *OpenLocationPage(const QString& namePage, bool isSelect);

	private:
		IControls *_controls;

		private slots:
			void OnCloseTab(int);
	};
} // namespace Ui

#endif // _TABS_WIDGET_


