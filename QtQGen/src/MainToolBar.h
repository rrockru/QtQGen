#ifndef _MAIN_TOOLBAR_
#define _MAIN_TOOLBAR_

#include "IControls.h"
#include "toolbutton.h"

namespace Ui
{
	class MainToolBar :
		public QToolBar
	{
	public:
		MainToolBar(QString, QWidget *, IControls *);

	protected:
		void mouseMoveEvent(QMouseEvent* e);
		void leaveEvent(QEvent * event);

	private:
		IControls *_controls;
	};
}
#endif
