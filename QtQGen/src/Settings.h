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

		void SetFirstLocName(const QString &name) { _firstLocName = name; }
		QString GetFirstLocName() { return _firstLocName; }

		void SetCreateFirstLoc(bool status) { _isCreateFirstLoc = status; }
		bool GetCreateFirstLoc() { return _isCreateFirstLoc; }

	private:
		QString _firstLocName;

		bool			_isCreateFirstLoc;
		bool			_isShowLocsIcons;
		bool			_isCollapseCode;
	};
} // namespace Ui

#endif // _SETTINGS_

