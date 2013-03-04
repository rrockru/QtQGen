#ifndef _TOOL_BUTTON_
#define _TOOL_BUTTON_

#include "IControls.h"

namespace Ui
{
	class ToolButton :
		public QAction
	{
		Q_OBJECT

	public:
		ToolButton(QIcon icon, QString text, QObject *parent, IControls *controls);

	private:
		IControls *_controls;

	private slots:
		void OnHovered();
	};
} // namespace Ui

#endif // _TOOL_BUTTON_


