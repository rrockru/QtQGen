#pragma once
#ifndef _ICONTROLS_
#define _ICONTROLS_

namespace Ui
{
	class IControls
	{
	public:
		virtual void SetStatusText(const QString &text) = 0;
		virtual void CleanStatusText() = 0;
	};
} // namespace Ui

#endif // _ICONTROLS_

