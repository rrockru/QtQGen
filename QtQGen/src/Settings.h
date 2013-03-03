#ifndef _SETTINGS_
#define _SETTINGS_


namespace Ui
{
	class Settings
	{
	public:
		Settings(QString);

		void SetShowLocsIcons(bool status) { _isShowLocsIcons = status; }
		bool GetShowLocsIcons() { return _isShowLocsIcons; }

		void SetCollapseCode(bool status) { _isCollapseCode = status; }
		bool GetCollapseCode() { return _isCollapseCode; }

	private:
		bool			_isShowLocsIcons;
		bool			_isCollapseCode;
	};
} // namespace Ui

#endif // _SETTINGS_

