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

#include "controls.h"

Controls::Controls(const QString path)
{
    _mainWindow = NULL;
    _locListBox = NULL;
    _tabsWidget = NULL;

    _currentPath = path;

    _settings = new Settings(_currentPath);

    _container = new DataContainer();

    _translator = new QTranslator;

    _keywordsStore = new KeywordsStore();
    QString filename = QFileInfo(_currentPath, "keywords.xml").absoluteFilePath();
    _keywordsStore->Load(filename);

    _lastSaveState = false;

    InitData();
}

void Controls::SetStatusText(const QString &text)
{
    QStatusBar *_statusBar = _mainWindow->statusBar();
    if (_statusBar)
    {
        _statusBar->showMessage(text);
    }
}

void Controls::CleanStatusText()
{
    QStatusBar *_statusBar = _mainWindow->statusBar();
    if (_statusBar)
    {
        _statusBar->clearMessage();
    }
}

bool Controls::LoadGame(const QString &filename)
{
    _tabsWidget->CloseAll();
    if (qspOpenQuest(filename, GetParent(), this, _currentGamePass, false))
    {
        QFileInfo file(filename);
        OpenConfigFile(_container, file.path() + QDir::separator() + file.completeBaseName() + ".qproj");
        InitSearchData();
        _currentGamePath = filename;
        UpdateLocationsList();
        _container->Save();

        _lastSaveState = true;
        return true;
    }

    return false;
}

bool Controls::SaveGame(const QString &filename, const QString &password)
{
    SyncWithLocationsList();
    _tabsWidget->SaveOpenedPages();
    if (qspSaveQuest(filename, password, this))
    {
        QFileInfo file(filename);
        SaveConfigFile(_container, file.path() + QDir::separator() + file.completeBaseName() + ".qproj");
        _container->Save();
        _currentGamePath = filename;
        _currentGamePass = password;
        _lastSaveState = true;
        return true;
    }
    return false;
}

bool Controls::SaveGameWithCheck()
{
    if (!_lastSaveState) return false;
    if (!IsGameSaved())
        return SaveGame(_currentGamePath, _currentGamePass);
    else
        _lastSaveState = true;
    return true;
}

void Controls::UpdateLocationsList()
{
    size_t locsCount = _container->GetLocationsCount();
    _locListBox->Clear();
    QString folderName;
    QList<int> locs;
    long oldPos = -1, pos = 0, folderIndex;
    while (pos != oldPos)
    {
        oldPos = pos;
        folderIndex = _container->FindFolderForPos(pos);
        if (folderIndex >= 0)
        {
            _locListBox->AddFolder(_container->GetFolderName(folderIndex));
            ++pos;
        }
        if (locs.count() < (int)locsCount)
        {
            for (size_t i = 0; i < locsCount; ++i)
            {
                if (locs.indexOf(i) < 0 && _container->GetLocFolder(i) == folderIndex)
                {
                    if (folderIndex >= 0)
                        folderName = _container->GetFolderName(folderIndex);
                    else
                    {
                        if (_container->FindFolderForPos(pos) >= 0)
                            break;
                        folderName = "";
                    }
                    _locListBox->Insert(_container->GetLocationName(i), "", folderName);
                    locs << i;
                    ++pos;
                }
            }
        }
    }
    UpdateActionsOnAllLocs();
    ShowOpenedLocationsIcons();
}

void Controls::SyncWithLocationsList()
{
    if (_locListBox->IsNeedForUpdate())
    {
        _locListBox->UpdateDataContainer();
        UpdateOpenedLocationsIndexes();
        InitSearchData();
    }
}

bool Controls::IsGameSaved()
{
    SyncWithLocationsList();
    _tabsWidget->SaveOpenedPages();
    return _container->IsSaved();
}

bool Controls::IsCanSaveGame()
{
    return (_container->GetLocationsCount() != 0);
}

void Controls::ShowMessage(long errorNum)
{
    ShowMessage(GetMessageDesc(errorNum));
}

void Controls::ShowMessage(QString msg)
{
    QMessageBox *dlgMsg = new QMessageBox(QMessageBox::Information, "Info", msg, QMessageBox::Ok, GetParent());
    dlgMsg->exec();
}

QString Controls::GetMessageDesc(long errorNum)
{
    QString str;
    switch (errorNum)
    {
    case QGEN_MSG_EXISTS: str = QObject::tr("Such name already exists! Input another name."); break;
    case QGEN_MSG_EXISTS_HKEY: str = QObject::tr("This keys combination is used already! Select another combination."); break;
    case QGEN_MSG_EXISTS_S_HKEY: str = QObject::tr("This keys combination is used already by the system! Select another combination."); break;
    case QGEN_MSG_EMPTYDATA: str = QObject::tr("An empty field, input the value!"); break;
    case QGEN_MSG_WRONGPASSWORD: str = QObject::tr("Wrong password!"); break;
    case QGEN_MSG_CANTSAVEGAME: str = QObject::tr("Can't write file!"); break;
    case QGEN_MSG_CANTLOADGAME: str = QObject::tr("Can't load game. File is corrupted or in wrong format."); break;
    case QGEN_MSG_NOTFOUND: str = QObject::tr("The specified text was not found"); break;
    case QGEN_MSG_SEARCHENDED: str = QObject::tr("The specified text was not found anymore."); break;
    case QGEN_MSG_WRONGFORMAT: str = QObject::tr("Incorrect format!"); break;
    case QGEN_MSG_MAXACTIONSCOUNTREACHED: str = QString(QObject::tr("Can't add more than %1 actions.")).arg(QGEN_MAXACTIONS); break;
    case QGEN_MSG_TOOLONGLOCATIONNAME: str = QString(QObject::tr("Location's name can't contain more than %1 characters!")).arg(QGEN_MAXLOCATIONNAMELEN); break;
    case QGEN_MSG_TOOLONGACTIONNAME: str = QString(QObject::tr("Action's name can't contain more than %1 characters!")).arg(QGEN_MAXACTIONNAMELEN); break;
    case QGEN_MSG_TOOLONGFOLDERNAME: str = QString(QObject::tr("Folder's name can't contain more than %1 characters!")).arg(QGEN_MAXFOLDERNAMELEN); break;
    case QGEN_UPDMSG_FAILDOWNUPDFILE: str = QString(QObject::tr("Can't download update file from \"%1\". Check network connection!")).arg(_failedFiles.at(0)); break;
    case QGEN_UPDMSG_FAILPARSEUPDFILE: str = QString(QObject::tr("Can't parse update file \"%1\"!")).arg(_failedFiles.at(0)); break;
    case QGEN_UPDMSG_BADCHECKSUM: str = QString(QObject::tr("Bad file \"%1\" checksum!")).arg(_failedFiles.at(0)); break;
    case QGEN_UPDMSG_BADUPDATEVERSION: str = QObject::tr("Wrong version in update file!"); break;
    case QGEN_UPDMSG_BADUPDATEFILE: str = QObject::tr("Wrong update file!"); break;
    case QGEN_UPDMSG_FAILCOPYUPDATER: str = QString(QObject::tr("Can't copy updater file \"%1\" to TEMP dir!")).arg(_failedFiles.at(0)); break;
    case QGEN_UPDMSG_FAILWRITEUPDFILE: str = QObject::tr("Can't write update file to TEMP dir!"); break;
    case QGEN_UPDMSG_FAILREADUPDFILE: str = QObject::tr("Can't read update file from TEMP dir!"); break;
    case QGEN_UPDMSG_FAILWRITENEWFILE: str = QString(QObject::tr("Can't download \"%1\" into \"%2\"!")).arg(_failedFiles.at(0)).arg(_failedFiles.at(1)); break;
    case QGEN_UPDMSG_FAILDOWNNEWFILE: str = QString(QObject::tr("Can't download file \"%1\". Check network connection!")).arg(_failedFiles.at(0)); break;
    case QGEN_UPDMSG_FAILCOPYNEWFILE: str = QString(QObject::tr("Can't copy new file from \"%1\" to \"%2\"!")).arg(_failedFiles.at(0)).arg(_failedFiles.at(1)); break;
    default: str = QObject::tr("Unknown error!"); break;
    }
    return str;
}

LocationPage *Controls::ShowLocation(const QString & locName)
{
    int indexPage = _tabsWidget->FindPageIndex(locName);
    if (indexPage >= 0)
    {
        _tabsWidget->setCurrentIndex(indexPage);
        return (LocationPage *)_tabsWidget->widget(indexPage);
    }
    LocationPage *page = _tabsWidget->OpenLocationPage(locName, true);
    if (_settings->GetCollapseCode())
        page->ExpandCollapseAll(false);
    return page;
}

void Controls::UpdateLocationIcon(size_t locIndex, bool isOpened)
{
    _locListBox->SetLocStatus(_container->GetLocationName(locIndex), isOpened);
}

void Controls::ShowOpenedLocationsIcons()
{
    size_t index, count = _tabsWidget->count();
    for (index = 0; index < count; ++index)
        _locListBox->SetLocStatus(_tabsWidget->tabText(index), true);
}

void Controls::NewGame()
{
    if (!_container->IsEmpty())
    {
        _tabsWidget->CloseAll();
        _locListBox->Clear();
        _container->Clear();
        _container->Save();
    }
    InitData();
    QString locName = _settings->GetFirstLocName().trimmed();
    if (_settings->GetCreateFirstLoc() && !locName.isEmpty())
    {
        _container->AddLocation(locName);
        _locListBox->Insert(locName, "", "");
        _container->Save();
    }
}

void Controls::InitSearchData()
{
    _dataSearch.foundAt = SEARCH_NONE;
    _dataSearch.findAt = SEARCH_LOCNAME;

    _dataSearch.idxLoc = 0;
    _dataSearch.idxAct = 0;
    _dataSearch.startPos = -1;
    _dataSearch.stringLen = 0;

    _dataSearch.countChecking = 0;
    _dataSearch.isFoundAny = false;
}

void Controls::InitData()
{
    _currentGamePath = QFileInfo(_currentPath, "NoName.qsp").absoluteFilePath();
    _currentGamePass = QString::fromWCharArray(QGEN_PASSWD);
    InitSearchData();
    //_lastSaveTime = 0;
}

void Controls::UpdateActionsOnAllLocs()
{
    size_t count = _container->GetLocationsCount();
    for (size_t i = 0; i < count; ++i)
        _locListBox->UpdateLocationActions(_container->GetLocationName(i));
}

void Controls::UpdateLocale(QLocale locale)
{
    if (_translator)
    {
        QApplication::removeTranslator(_translator);
        delete _translator;
    }
    _translator = new QTranslator();
    QString langName = "qgen_" + locale.name();
    QString langPath = _currentPath + QDir::separator() + "langs" + QDir::separator();
    _translator->load(langName, langPath);
    QApplication::installTranslator(_translator);
    _settings->NotifyAll();
}

void Controls::UpdateOpenedLocationsIndexes()
{
    LocationPage *page;
    size_t count = _tabsWidget->count();
    for (size_t index = 0; index < count; ++index)
    {
        page = (LocationPage *)_tabsWidget->widget(index);
        page->SetLocationIndex(_container->FindLocationIndex(_tabsWidget->tabText(index)));
    }
}

QString Controls::GetGameInfo() const
{
    int totalLocsCount,
        totalEmptyDesc = 0,
        totalEmptyCode = 0,
        totalEmptyActsCode = 0,
        totalLocsSize = 0,
        totalActs = 0,
        maxLocSize = 0,
        avgActions = 0,
        avgSize = 0,
        locSize,
        actsCount;
    QString locName, actName, data;

    totalLocsCount = _container->GetLocationsCount();
    if (totalLocsCount > 0)
    {
        for (int i = 0; i < totalLocsCount; ++i)
        {
            locName = _container->GetLocationName(i);
            locSize = locName.length();
            data = _container->GetLocationDesc(i);
            locSize += data.length();
            if (data.trimmed().isEmpty()) ++totalEmptyDesc;
            data = _container->GetLocationCode(i);
            locSize += data.length();
            if (data.trimmed().isEmpty()) ++totalEmptyCode;
            actsCount = _container->GetActionsCount(i);
            if (actsCount)
            {
                totalActs += actsCount;
                for (int j = 0; j < actsCount; ++j)
                {
                    actName = _container->GetActionName(i, j);
                    locSize += actName.length();
                    locSize += _container->GetActionPicturePath(i, j).length();
                    data = _container->GetActionCode(i, j);
                    locSize += data.length();
                    if (data.trimmed().isEmpty()) ++totalEmptyActsCode;
                }
            }
            if (locSize > maxLocSize) maxLocSize = locSize;
            totalLocsSize += locSize;
        }
        avgActions = (int)((float)totalActs / totalLocsCount + 0.5);
        avgSize = (int)((float)totalLocsSize / totalLocsCount + 0.5);
    }
    QString message = QObject::tr("This game contains %1 location(s)\n").arg(totalLocsCount);
    message += QObject::tr("Locations without base description: %1\n").arg(totalEmptyDesc);
    message += QObject::tr("Locations without \"on visit\" code: %1\n").arg(totalEmptyCode);
    message += QObject::tr("Average count of actions per location: %1\n").arg(avgActions);
    message += QObject::tr("Actions without code: %1\n").arg(totalEmptyActsCode);
    message += QObject::tr("Max location size: %1 characters\n").arg(maxLocSize);
    message += QObject::tr("Average location size: %1 characters\n").arg(avgSize);
    message += QObject::tr("Total game size: %1 characters").arg(totalLocsSize);
    return message;
}

int Controls::AddLocation(const QString &name)
{
    QString locName(name);
    while (1)
    {
        bool ok;
        locName = QInputDialog::getText(_mainWindow, QObject::tr("Add location"),
            QObject::tr("Input name for a new location:"), QLineEdit::Normal,
            locName, &ok).trimmed();
        if (ok)
        {
            if (locName.isEmpty())
                ShowMessage(QGEN_MSG_EMPTYDATA);
            else if ((int)locName.length()>QGEN_MAXLOCATIONNAMELEN)
                ShowMessage(QGEN_MSG_TOOLONGLOCATIONNAME);
            else
            {
                int index = AddLocationByName(locName);
                if (index >= 0) return index;
            }
        }
        else
            return -1;
    }
}

int Controls::AddLocationByName(const QString &name)
{
    QString locName(_locListBox->GetStringSelection());
    QString folder(_locListBox->GetSelectedFolder());
    int locInd = _container->AddLocation(name);
    if (locInd >= 0)
    {
        _locListBox->Insert(name, locName, folder);
        if (_settings->GetOpenNewLoc()) ShowLocation(name);
        return locInd;
    }
    else
        ShowMessage(QGEN_MSG_EXISTS);
    return -1;
}

bool Controls::RenameSelectedLocation()
{
    int locIndex = GetSelectedLocationIndex();
    if (locIndex < 0) return false;

    QString name(_container->GetLocationName(locIndex));
    while (1)
    {
        bool ok;
        name = QInputDialog::getText(_mainWindow, QObject::tr("Rename location"),
            QObject::tr("Input new location's name:"), QLineEdit::Normal,
            name, &ok).trimmed();
        if (ok)
        {
            if (name.isEmpty())
                ShowMessage(QGEN_MSG_EMPTYDATA);
            else if ((int)name.length()>QGEN_MAXLOCATIONNAMELEN)
                ShowMessage(QGEN_MSG_TOOLONGLOCATIONNAME);
            else
            {
                if (RenameLocation(locIndex, name)) return true;
            }
        }
        else
            return false;
    }
}

int Controls::GetSelectedLocationIndex() const
{
    LocationPage *page = (LocationPage *)_tabsWidget->currentWidget();
    if (dynamic_cast<LocationPage *>(page) && !_locListBox->hasFocus()) return page->GetLocationIndex();

    QString locName(_locListBox->GetStringSelection());
    if (!locName.isEmpty()) return _container->FindLocationIndex(locName);

    return -1;
}

bool Controls::RenameLocation(size_t locIndex, const QString &name)
{
    QString oldName(_container->GetLocationName(locIndex));
    if (_container->RenameLocation(locIndex, name))
    {
        _locListBox->SetLocName(oldName, name);
        int pageIndex = _tabsWidget->FindPageIndex(oldName);
        if (pageIndex >= 0) _tabsWidget->setTabText(pageIndex, name);
        return true;
    }
    else
        ShowMessage(QGEN_MSG_EXISTS);
    return false;
}

bool Controls::DeleteSelectedLocation()
{
    int locIndex = GetSelectedLocationIndex();
    if (locIndex < 0) return false;

    QString locName(_container->GetLocationName(locIndex));
    int res = QMessageBox::question(_mainWindow,
        QObject::tr("Remove location"),
        QObject::tr("Remove \"%1\" location?").arg(locName));

    if (res == QMessageBox::Yes)
    {
        int index = _tabsWidget->FindPageIndex(locName);
        if (index >= 0) _tabsWidget->DeletePage(index);
        _locListBox->Delete(locName);
        _container->DeleteLocation(locIndex);
        UpdateOpenedLocationsIndexes();
        InitSearchData();
        return true;
    }
    return false;
}

bool Controls::AddFolder()
{
    QString name;
    while (1)
    {
        bool ok;
        name = QInputDialog::getText(_mainWindow, QObject::tr("Add folder"),
            QObject::tr("Input name for a new folder:"), QLineEdit::Normal,
            name, &ok).trimmed();
        if (ok)
        {
            if (name.isEmpty())
                ShowMessage( QGEN_MSG_EMPTYDATA );
            else if ((int)name.length() > QGEN_MAXFOLDERNAMELEN)
                ShowMessage( QGEN_MSG_TOOLONGFOLDERNAME );
            else
            {
                if (_container->AddFolder(name) >= 0)
                {
                    _locListBox->AddFolder(name);
                    break;
                }
                else
                    ShowMessage(QGEN_MSG_EXISTS);
            }
        }
        else
            return false;
    }
    return true;
}

bool Controls::DeleteSelectedFolder()
{
    int folder = GetSelectedFolderIndex();
    if (folder < 0) return false;

    QString folderName(_container->GetFolderName(folder));
    int res = QMessageBox::question(_mainWindow,
        QObject::tr("Remove folder"),
        QObject::tr("Remove \"%1\" folder?").arg(folderName));

    if (res == QMessageBox::Yes)
    {
        SyncWithLocationsList();
        _container->DeleteFolder(_container->FindFolderIndex(folderName));
        UpdateLocationsList();
        return true;
    }
    return false;
}

bool Controls::RenameSelectedFolder()
{
    int folder = GetSelectedFolderIndex();
    if (folder < 0) return false;

    QString name(_container->GetFolderName(folder));
    while (1)
    {
        bool ok;
        name = QInputDialog::getText(_mainWindow, QObject::tr("Rename folder"),
            QObject::tr("Input new folder's name:"), QLineEdit::Normal,
            name, &ok).trimmed();
        if (ok)
        {
            if (name.isEmpty())
                ShowMessage( QGEN_MSG_EMPTYDATA );
            else if ((int)name.length() > QGEN_MAXFOLDERNAMELEN)
                ShowMessage( QGEN_MSG_TOOLONGFOLDERNAME );
            else
            {
                if (RenameFolder(folder, name)) break;
            }
        }
        else
            return false;
    }
    return true;
}

bool Controls::RenameFolder(size_t folderIndex, const QString &name )
{
    QString oldName(_container->GetFolderName(folderIndex));
    if (_container->RenameFolder(folderIndex, name))
    {
        _locListBox->SetFolderName(oldName, name);
        return true;
    }
    else
        ShowMessage( QGEN_MSG_EXISTS );
    return false;
}

int Controls::GetSelectedFolderIndex() const
{
    int locIndex = GetSelectedLocationIndex();
    if (locIndex >= 0)
        return _container->GetLocFolder(locIndex);
    else
        return _container->FindFolderIndex(_locListBox->GetSelectedFolder());
}

bool Controls::AddActionOnSelectedLoc()
{
    QString name = "";
    LocationPage *page = (LocationPage *)_tabsWidget->currentWidget();
    if (!page) return false;

    size_t locIndex = page->GetLocationIndex();
    if (_container->GetActionsCount(locIndex) >= QGEN_MAXACTIONS)
    {
        ShowMessage(QGEN_MSG_MAXACTIONSCOUNTREACHED);
        return false;
    }

    while (1)
    {
        bool ok;
        name = QInputDialog::getText(_mainWindow, QObject::tr("Add action"),
            QObject::tr("Input name for a new action:"), QLineEdit::Normal,
            name, &ok).trimmed();
        if (ok)
        {
            if (name.isEmpty())
                ShowMessage(QGEN_MSG_EMPTYDATA);
            else if ((int)name.length()>QGEN_MAXACTIONNAMELEN)
                ShowMessage(QGEN_MSG_TOOLONGACTIONNAME);
            else
            {
                if (_container->AddAction(locIndex, name) >= 0)
                {
                    size_t actIndex = page->AddAction(name);
                    if (_settings->GetOpenNewAct())
                    {
                        page->SelectAction(actIndex);
                        page->SetFocusOnActionCode();
                    }
                    _locListBox->UpdateLocationActions(_container->GetLocationName(locIndex));
                    return true;
                }
                else
                    ShowMessage(QGEN_MSG_EXISTS);
            }
        }
        else
            return false;
    }
}

bool Controls::RenameSelectedAction()
{
    LocationPage *page = (LocationPage *)_tabsWidget->currentWidget();
    if (!page) return false;

    size_t locIndex = page->GetLocationIndex();
    long actIndex = page->GetSelectedAction();
    if (actIndex < 0) return false;

    QString name(_container->GetActionName(locIndex, actIndex));
    while (1)
    {
        bool ok;
        name = QInputDialog::getText(_mainWindow, QObject::tr("Rename action"),
            QObject::tr("Input new action's name:"), QLineEdit::Normal,
            name, &ok).trimmed();
        if (ok)
        {
            if (name.isEmpty())
                ShowMessage(QGEN_MSG_EMPTYDATA);
            else if ((int)name.length()>QGEN_MAXACTIONNAMELEN)
                ShowMessage(QGEN_MSG_TOOLONGACTIONNAME);
            else
            {
                if (RenameAction(locIndex, actIndex, name)) return true;
            }
        }
        else
            return false;
    }
}

bool Controls::RenameAction(size_t locIndex, size_t actIndex, const QString &name)
{
    if (_container->RenameAction(locIndex, actIndex, name))
    {
        LocationPage *page = _tabsWidget->GetPageByLocName(_container->GetLocationName(locIndex));
        if (page) page->RenameAction(actIndex, name);
        _locListBox->UpdateLocationActions(_container->GetLocationName(locIndex));
        return true;
    }
    else
        ShowMessage(QGEN_MSG_EXISTS);
    return false;
}

bool Controls::DeleteSelectedAction()
{
    LocationPage *page = (LocationPage *)_tabsWidget->currentWidget();
    if (!page) return false;

    size_t locIndex = page->GetLocationIndex();
    long actIndex = page->GetSelectedAction();
    if (actIndex < 0) return false;

    _container->DeleteAction(locIndex, actIndex);
    page->DeleteAction(actIndex);
    _locListBox->UpdateLocationActions(_container->GetLocationName(locIndex));
    InitSearchData();
    return true;
}

bool Controls::DeleteAllActions()
{
    LocationPage *page = (LocationPage *)_tabsWidget->currentWidget();
    if (!page) return false;

    size_t locIndex = page->GetLocationIndex();
    QString locName(_container->GetLocationName(locIndex));

    int res = QMessageBox::question(_mainWindow,
        QObject::tr("Remove all actions"),
        QObject::tr("Remove all actions on \"%1\" location?").arg(locName));

    if (res == QMessageBox::Yes)
    {
        _container->DeleteAllActions(locIndex);
        page->DeleteAllActions();
        _locListBox->UpdateLocationActions(locName);
        InitSearchData();
        return true;
    }

    return false;
}

QString Controls::ConvertSearchString(const QString &s, bool isMatchCase)
{
    return (isMatchCase ? s : s.toLower());
}

bool Controls::SearchString(const QString &str, bool findAgain, bool isMatchCase, bool isWholeString)
{
    QString data;
    QString locName;
    QString actName;
    LocationPage *page = NULL;
    int startPos = -1;
    int lastPos;
    int locIndex, countLocs = _container->GetLocationsCount();
    if (!countLocs) return false;
    SyncWithLocationsList();

    QString lwrStr = ConvertSearchString(str, isMatchCase);

    _tabsWidget->SaveOpenedPages();

    if (findAgain || _dataSearch.idxLoc >= countLocs || _dataSearch.countChecking >= countLocs)
    {
        InitSearchData();
        locIndex = GetSelectedLocationIndex();
        if (locIndex < 0) locIndex = 0;
        _dataSearch.idxLoc = locIndex;
    }

    _dataSearch.foundAt = SEARCH_NONE;
    _dataSearch.stringLen = str.length();

    while (_dataSearch.idxLoc < countLocs)
    {
        locName = _container->GetLocationName(_dataSearch.idxLoc);
        if (_dataSearch.findAt == SEARCH_LOCNAME)
        {
            _dataSearch.findAt = SEARCH_LOCDESC;
            _dataSearch.startPos = -1;
            if (FindSubString(ConvertSearchString(locName, isMatchCase), lwrStr, isWholeString) != -1)
            {
                _locListBox->Select(locName);
                ShowLocation(locName);
                _locListBox->setFocus();
                _dataSearch.foundAt = SEARCH_LOCNAME;
                _dataSearch.isFoundAny = true;
                return true;
            }
        }
        if (_dataSearch.findAt == SEARCH_LOCDESC)
        {
            data = _container->GetLocationDesc(_dataSearch.idxLoc);
            startPos = FindSubString(ConvertSearchString(data, isMatchCase), lwrStr, isWholeString, _dataSearch.startPos + 1);
            if (startPos != -1)
            {
                lastPos = lwrStr.length();
                lastPos += startPos;
                _locListBox->Select(locName);
                page = ShowLocation(locName);
                page->SelectLocDescString(startPos, lastPos);
                _dataSearch.startPos = startPos;
                _dataSearch.foundAt = SEARCH_LOCDESC;
                _dataSearch.isFoundAny = true;
                return true;
            }
            else
            {
                _dataSearch.findAt = SEARCH_LOCCODE;
                _dataSearch.startPos = -1;
            }
        }

        if (_dataSearch.findAt == SEARCH_LOCCODE)
        {
            data = _container->GetLocationCode(_dataSearch.idxLoc);
            startPos = FindSubString(ConvertSearchString(data, isMatchCase), lwrStr, isWholeString, _dataSearch.startPos + 1);
            if (startPos != -1)
            {
                lastPos = lwrStr.length();
                lastPos += startPos;
                _locListBox->Select(locName);
                page = ShowLocation(locName);
                page->SelectLocCodeString(startPos, lastPos);
                _dataSearch.startPos = startPos;
                _dataSearch.foundAt = SEARCH_LOCCODE;
                _dataSearch.isFoundAny = true;
                return true;
            }
            else
            {
                _dataSearch.findAt = SEARCH_ACTNAME;
                _dataSearch.startPos = -1;
                _dataSearch.idxAct = 0;
            }
        }

        int countActs = _container->GetActionsCount(_dataSearch.idxLoc);

        for(; _dataSearch.idxAct < countActs; ++_dataSearch.idxAct)
        {
            if (_dataSearch.findAt == SEARCH_ACTNAME)
            {
                _dataSearch.findAt = SEARCH_PATHPICT;
                _dataSearch.startPos = -1;
                actName = _container->GetActionName(_dataSearch.idxLoc, _dataSearch.idxAct);
                if (FindSubString(ConvertSearchString(actName, isMatchCase), lwrStr, isWholeString) != -1)
                {
                    _locListBox->Select(locName);
                    page = ShowLocation(locName);
                    page->SelectAction(_dataSearch.idxAct);
                    _dataSearch.foundAt = SEARCH_ACTNAME;
                    _dataSearch.isFoundAny = true;
                    return true;
                }
            }
            if (_dataSearch.findAt == SEARCH_PATHPICT)
            {
                data = _container->GetActionPicturePath(_dataSearch.idxLoc, _dataSearch.idxAct);
                startPos = FindSubString(ConvertSearchString(data, isMatchCase), lwrStr, isWholeString, _dataSearch.startPos + 1);
                if (startPos != -1)
                {
                    lastPos = lwrStr.length();
                    lastPos += startPos;
                    _locListBox->Select(locName);
                    page = ShowLocation(locName);
                    page->SelectAction(_dataSearch.idxAct);
                    page->SelectPicturePathString(startPos, lastPos);
                    _dataSearch.startPos = startPos;
                    _dataSearch.foundAt = SEARCH_PATHPICT;
                    _dataSearch.isFoundAny = true;
                    return true;
                }
                else
                {
                    _dataSearch.findAt = SEARCH_ACTCODE;
                    _dataSearch.startPos = -1;
                }
            }
            if (_dataSearch.findAt == SEARCH_ACTCODE)
            {
                data = _container->GetActionCode(_dataSearch.idxLoc, _dataSearch.idxAct);
                startPos = FindSubString(ConvertSearchString(data, isMatchCase), lwrStr, isWholeString, _dataSearch.startPos + 1);
                if (startPos != -1)
                {
                    lastPos = lwrStr.length();
                    lastPos += startPos;
                    _locListBox->Select(locName);
                    page = ShowLocation(locName);
                    page->SelectAction( _dataSearch.idxAct );
                    page->SelectActionCodeString(startPos, lastPos);
                    _dataSearch.startPos = startPos;
                    _dataSearch.foundAt = SEARCH_ACTCODE;
                    _dataSearch.isFoundAny = true;
                    return true;
                }
                else
                {
                    _dataSearch.findAt = SEARCH_ACTNAME;
                    _dataSearch.startPos = -1;
                }
            }
        }
        if (!SearchNextLoc()) return false;
    }
    ShowMessage(QGEN_MSG_NOTFOUND);
    return false;
}

int Controls::FindSubString(const QString &s, const QString &sub, bool isWholeString, int ind)
{
    if (isWholeString)
    {
        int length = s.length(), subLen = sub.length(), ind2;
        --ind;
        do
        {
            ind = s.indexOf(sub, ind + 1);
            if (ind < 0) break;
            ind2 = ind + subLen;
        } while (!(
            (ind == 0 || QGEN_STRCHR(QGEN_DELIMS, s.toStdWString().c_str()[ind - 1])) &&
            (ind2 >= length || QGEN_STRCHR(QGEN_DELIMS, s.toStdWString().c_str()[ind2]))
            ));
        return ind;
    }
    else
        return s.indexOf(sub, ind);
}

bool Controls::SearchNextLoc()
{
    int countLocs = _container->GetLocationsCount();
    _dataSearch.findAt = SEARCH_LOCNAME;
    _dataSearch.startPos = -1;
    if (++_dataSearch.idxLoc >= countLocs) _dataSearch.idxLoc = 0;
    if (++_dataSearch.countChecking >= countLocs)
    {
        ShowMessage(_dataSearch.isFoundAny ? QGEN_MSG_SEARCHENDED : QGEN_MSG_NOTFOUND);
        return false;
    }
    return true;
}

void Controls::ReplaceSearchString(const QString & replaceString)
{
    QString temp;
    if (_dataSearch.foundAt == SEARCH_NONE) return;
    LocationPage *page = _tabsWidget->GetPageByLocName(_container->GetLocationName(_dataSearch.idxLoc));
    switch (_dataSearch.foundAt)
    {
    case SEARCH_LOCDESC:
        temp = _container->GetLocationDesc(_dataSearch.idxLoc);
        temp.replace(_dataSearch.startPos, _dataSearch.stringLen, replaceString);
        _container->SetLocationDesc(_dataSearch.idxLoc, temp);
        if (page)
            page->ReplaceLocDescString(_dataSearch.startPos, _dataSearch.startPos + _dataSearch.stringLen, replaceString);
        break;
    case SEARCH_LOCCODE:
        temp = _container->GetLocationCode(_dataSearch.idxLoc);
        temp.replace(_dataSearch.startPos, _dataSearch.stringLen, replaceString);
        _container->SetLocationCode(_dataSearch.idxLoc, temp);
        if (page)
            page->ReplaceLocCodeString(_dataSearch.startPos, _dataSearch.startPos + _dataSearch.stringLen, replaceString);
        break;
    case SEARCH_PATHPICT:
        temp = _container->GetActionPicturePath(_dataSearch.idxLoc, _dataSearch.idxAct);
        temp.replace(_dataSearch.startPos, _dataSearch.stringLen, replaceString);
        _container->SetActionPicturePath(_dataSearch.idxLoc, _dataSearch.idxAct, temp);
        if (page)
            page->ReplacePicturePathString(_dataSearch.startPos, _dataSearch.startPos + _dataSearch.stringLen, replaceString);
        break;
    case SEARCH_ACTCODE:
        temp = _container->GetActionCode(_dataSearch.idxLoc, _dataSearch.idxAct);
        temp.replace(_dataSearch.startPos, _dataSearch.stringLen, replaceString);
        _container->SetActionCode(_dataSearch.idxLoc, _dataSearch.idxAct, temp);
        if (page)
            page->ReplaceActionCodeString(_dataSearch.startPos, _dataSearch.startPos + _dataSearch.stringLen, replaceString);
        break;
    }
    _dataSearch.startPos += replaceString.length() - 1;
    _dataSearch.foundAt = SEARCH_NONE;
}

void Controls::MoveActionTo( size_t locIndex, size_t actIndex, size_t moveTo )
{
    _container->MoveActionTo(locIndex, actIndex, moveTo);
    QString locName(_container->GetLocationName(locIndex));
    LocationPage *page = _tabsWidget->GetPageByLocName(locName);
    if (page) page->MoveActionTo(actIndex, moveTo);
    _locListBox->UpdateLocationActions(locName);
    InitSearchData();
}

void Controls::GameUpdate()
{
    emit _mainWindow->gameUpdate();
}

bool Controls::IsActionsOnSelectedLocEmpty() const
{
    LocationPage *page = (LocationPage *)_tabsWidget->currentWidget();
    return (!dynamic_cast<LocationPage *>(page) || page->IsActionsEmpty());
}

int Controls::GetSelectionCount() const
{
    return _locListBox->GetSelectionCount();
}

void Controls::DeleteSelectedItems()
{
    SyncWithLocationsList();

    int res = QMessageBox::question(_mainWindow,
        QObject::tr("Remove items"),
        QObject::tr("Remove selected items?"));
    if (res != QMessageBox::Yes)
        return;

    QListIterator<QTreeWidgetItem *> items(_locListBox->GetSelectedItems());
    while (items.hasNext())
    {
        QTreeWidgetItem *curItem = items.next();
        QString name = curItem->text(0);
        switch (_locListBox->GetItemType(curItem)) {
        case DRAG_LOCATION:
        {
            int index = _tabsWidget->FindPageIndex(name);
            if (index >= 0) _tabsWidget->DeletePage(index);
            _locListBox->Delete(name);
            _container->DeleteLocation(_container->FindLocationIndex(name));
            UpdateOpenedLocationsIndexes();
            break;
        }
        case DRAG_FOLDER:
            _container->DeleteFolder(_container->FindFolderIndex(name));
            break;
        }
    }
    UpdateLocationsList();
    InitSearchData();
}

void Controls::SwitchLocDesc()
{
    LocationPage *page = (LocationPage *)_tabsWidget->currentWidget();
    if(dynamic_cast<LocationPage *>(page)) page->LocDescVisible(!page->IsDescShown());
}

void Controls::SwitchLocActs()
{
    LocationPage *page = (LocationPage *)_tabsWidget->currentWidget();
    if(dynamic_cast<LocationPage *>(page)) page->LocActsVisible(!page->IsActsShown());
}
