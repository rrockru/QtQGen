// Copyright (C) 2013
// Shchannikov Dmitry (rrock DOT ru AT gmail DOT com)
// Nex (nex AT otaku DOT ru)
/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#ifndef _ICONTROLS_
#define _ICONTROLS_

#include "datacontainer.h"
#include "keywordsstore.h"
#include "settings.h"

class LocationPage;

enum SearchPlace
{
    SEARCH_NONE,
    SEARCH_LOCNAME,
    SEARCH_LOCDESC,
    SEARCH_LOCCODE,
    SEARCH_ACTNAME,
    SEARCH_PATHPICT,
    SEARCH_ACTCODE
};

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
    QGEN_MSG_TOOLONGACTIONNAME,
    QGEN_UPDMSG_BADCHECKSUM,
    QGEN_UPDMSG_ABORTED,
    QGEN_UPDMSG_BADUPDATEVERSION,
    QGEN_UPDMSG_BADUPDATEFILE,
    QGEN_UPDMSG_TRUE,
    QGEN_UPDMSG_FALSE,
    QGEN_UPDMSG_CANCEL,
    QGEN_UPDMSG_FAILDOWNUPDFILE,
    QGEN_UPDMSG_FAILPARSEUPDFILE,
    QGEN_UPDMSG_FAILCOPYUPDATER,
    QGEN_UPDMSG_FAILWRITEUPDFILE,
    QGEN_UPDMSG_FAILREADUPDFILE,
    QGEN_UPDMSG_FAILWRITENEWFILE,
    QGEN_UPDMSG_FAILDOWNNEWFILE,
    QGEN_UPDMSG_FAILCOPYNEWFILE
};

class IControls
{


public:
    virtual void SetStatusText(const QString &text) = 0;
    virtual void CleanStatusText() = 0;
    virtual bool LoadGame(const QString &filename) = 0;
    virtual bool SaveGame(const QString &filename, const QString &password) = 0;
    virtual bool SaveGameWithCheck() = 0;
    virtual bool SearchString(const QString &str, bool findAgain, bool isMatchCase = false, bool isWholeString = false) = 0;
    virtual void ReplaceSearchString(const QString & replaceString) = 0;
    virtual bool SearchNextLoc() = 0;
    virtual bool IsGameSaved() = 0;
    virtual bool IsCanSaveGame() = 0;
    virtual QString GetGamePath() const = 0;
    virtual void ShowMessage(long errorNum) = 0;
    virtual void InitSearchData() = 0;
    virtual DataContainer *GetContainer() const = 0;
    virtual void UpdateLocationsList() = 0;
    virtual void ShowOpenedLocationsIcons() = 0;
    virtual Settings *GetSettings() const = 0;
    virtual LocationPage *ShowLocation(const QString & locName) = 0;
    virtual void UpdateLocationIcon(size_t locIndex, bool isOpened) = 0;
    virtual void NewGame() = 0;
    virtual bool UpdateLocale(QLocale::Language lang) = 0;

    virtual void SyncWithLocationsList() = 0;

    virtual QTranslator * GetTranslator() = 0;

    virtual KeywordsStore *GetKeywordsStore() const = 0;

    virtual QString GetGameInfo() const = 0;

    virtual int AddLocation(const QString &name = "") = 0;
    virtual bool RenameSelectedLocation() = 0;
    virtual int GetSelectedLocationIndex() const = 0;
    virtual bool RenameLocation(size_t locIndex, const QString &name) = 0;
    virtual bool DeleteSelectedLocation() = 0;

    virtual bool AddFolder() = 0;
    virtual bool DeleteSelectedFolder() = 0;
    virtual bool RenameSelectedFolder() = 0;
    virtual int GetSelectedFolderIndex() const = 0;

    virtual bool AddActionOnSelectedLoc() = 0;
    virtual bool DeleteSelectedAction() = 0;
    virtual bool RenameSelectedAction() = 0;
    virtual bool RenameAction(size_t locIndex, size_t actIndex, const QString &name) = 0;    
    virtual void MoveActionTo(size_t locIndex, size_t actIndex, size_t moveTo) = 0;
    virtual bool DeleteAllActions() = 0;

    virtual int GetSelectionCount() const = 0;
    virtual void DeleteSelectedItems() = 0;

    virtual bool IsActionsOnSelectedLocEmpty() const = 0;

    virtual QWidget *GetParent() = 0;
    virtual void Update() = 0;

    virtual void SetFailedFilesList(const QStringList files) = 0;
};

#endif // _ICONTROLS_

