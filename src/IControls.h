#ifndef _ICONTROLS_
#define _ICONTROLS_

#include "datacontainer.h"
#include "Settings.h"

namespace Ui
{
	class LocationPage;

	enum MessageType
	{
		QGEN_MSG_EXISTS,
		QGEN_MSG_EXISTS_HKEY,
		QGEN_MSG_EXISTS_S_HKEY,
		QGEN_MSG_EMPTYDATA,
		QGEN_MSG_WRONGPASSWORD,
		QGEN_MSG_CANTSAVEGAME,
		QGEN_MSG_CANTLOADGAME,
		QGEN_MSG_NOTFOUND,
		QGEN_MSG_SEARCHENDED,
		QGEN_MSG_WRONGFORMAT,
		QGEN_MSG_MAXACTIONSCOUNTREACHED,
		QGEN_MSG_TOOLONGFOLDERNAME,
		QGEN_MSG_TOOLONGLOCATIONNAME,
		QGEN_MSG_TOOLONGACTIONNAME
	};

	class IControls
	{
	public:
		virtual void SetStatusText(const QString &text) = 0;
		virtual void CleanStatusText() = 0;
		virtual bool LoadGame(QString) = 0;
        virtual bool SaveGame(const QString &path, const QString &password) = 0;
        virtual bool SaveGameWithCheck() = 0;
		virtual bool IsGameSaved() = 0;
		virtual QString GetGamePath() const = 0;
		virtual void ShowMessage(long errorNum) = 0;
		virtual DataContainer *GetContainer() const = 0;
		virtual void UpdateLocationsList() = 0;
		virtual Settings *GetSettings() const = 0;
		virtual LocationPage *ShowLocation(const QString & locName) = 0;
		virtual void UpdateLocationIcon(size_t locIndex, bool isOpened) = 0;
		virtual void NewGame() = 0;
		virtual bool UpdateLocale(QLocale::Language lang) = 0;

        virtual void SyncWithLocationsList() = 0;

		virtual QTranslator * GetTranslator() = 0;

        virtual QString GetGameInfo() const = 0;

        virtual int AddLocation(const QString &name = "") = 0;
        virtual bool RenameSelectedLocation() = 0;
        virtual int GetSelectedLocationIndex() const = 0;
        virtual bool RenameLocation(size_t locIndex, const QString &name) = 0;
        virtual bool DeleteSelectedLocation() = 0;

        virtual bool AddActionOnSelectedLoc() = 0;
        virtual bool DeleteSelectedAction() = 0;
        virtual bool RenameSelectedAction() = 0;
        virtual bool RenameAction(size_t locIndex, size_t actIndex, const QString &name) = 0;

        virtual QWidget *GetParent() = 0;

	};
} // namespace Ui

#endif // _ICONTROLS_

