#ifndef _TABS_WIDGET_
#define _TABS_WIDGET_

namespace Ui
{
	class TabsWidget :
		public QTabWidget
	{
		Q_OBJECT

	public:
		TabsWidget();

	private slots:
		void OnCloseTab(int);
	};
} // namespace Ui

#endif // _TABS_WIDGET_


