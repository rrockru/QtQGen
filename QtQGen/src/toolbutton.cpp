#include "stdafx.h"
#include "toolbutton.h"

namespace Ui
{
	ToolButton::ToolButton(QIcon icon, QString text, QObject *parent, IControls *controls) : QAction(icon, text, parent)
	{
		_controls = controls;
		connect(this, SIGNAL(hovered()), this, SLOT(OnHovered()));
	}

	void ToolButton::OnHovered()
	{
		_controls->SetStatusText(text());
	}
}

