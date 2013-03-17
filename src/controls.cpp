#include "stdafx.h"
#include "controls.h"

namespace Ui
{
	Controls::Controls(const QString path)
	{
		_mainWindow = NULL;
		_locListBox = NULL;
		_tabsWidget = NULL;

		_currentPath = path;

		_settings = new Settings(_currentPath);

		_container = new DataContainer();

		_translator = new QTranslator;

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

	bool Controls::LoadGame(QString filename)
	{
		_tabsWidget->CloseAll();
		if (qspOpenQuest(filename.toStdWString().c_str(), GetParent(), this, _currentGamePass, false))
		{
			_currentGamePath = filename;
			UpdateLocationsList();
			_container->Save();
			return true;
		}
		
		return false;
	}

    bool Controls::SaveGame(const QString &path, const QString &password)
    {
        SyncWithLocationsList();
        _tabsWidget->SaveOpenedPages();
        if (qspSaveQuest(path.toStdWString().c_str(), password, this))
        {
            //wxFileName file(filename);
            //SaveConfigFile(_container, file.GetPathWithSep() + file.GetName() + wxT(".qproj"));
            _container->Save();
            //_lastSaveTime = wxGetLocalTimeMillis();
            _currentGamePath = path;
            _currentGamePass = password;
            return true;
        }
        return false;
    }

    bool Controls::SaveGameWithCheck()
    {
        //if (_lastSaveTime == 0) return false;
        if (!IsGameSaved())
            return SaveGame(_currentGamePath, _currentGamePass);
        //else
        //    _lastSaveTime = wxGetLocalTimeMillis();
        //return true;
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
			if (locs.count() < locsCount)
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
	}

    void Controls::SyncWithLocationsList()
    {
        if (_locListBox->IsNeedForUpdate())
        {
            _locListBox->UpdateDataContainer();
            UpdateOpenedLocationsIndexes();
            //InitSearchData();
        }
    }

	bool Controls::IsGameSaved()
	{
		return _container->IsSaved();
	}

	void Controls::ShowMessage( long errorNum )
	{
		QMessageBox *dlgMsg = new QMessageBox(QMessageBox::Information, "Info", GetMessageDesc(errorNum), QMessageBox::Ok, GetParent());
		dlgMsg->exec();
	}

	QString Controls::GetMessageDesc( long errorNum )
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
		case QGEN_MSG_CANTLOADGAME: str = QObject::tr("Can't load game. Locations with the same name are found!"); break;
		case QGEN_MSG_NOTFOUND: str = QObject::tr("The specified text was not found"); break;
		case QGEN_MSG_SEARCHENDED: str = QObject::tr("The specified text was not found anymore."); break;
		case QGEN_MSG_WRONGFORMAT: str = QObject::tr("Incorrect format!"); break;
		case QGEN_MSG_MAXACTIONSCOUNTREACHED: str = QString(QObject::tr("Can't add more than %1 actions.")).arg(QGEN_MAXACTIONS); break;
		case QGEN_MSG_TOOLONGLOCATIONNAME: str = QString(QObject::tr("Location's name can't contain more than %1 characters!")).arg(QGEN_MAXLOCATIONNAMELEN); break;
		case QGEN_MSG_TOOLONGACTIONNAME: str = QString(QObject::tr("Action's name can't contain more than %1 characters!")).arg(QGEN_MAXACTIONNAMELEN); break;
		case QGEN_MSG_TOOLONGFOLDERNAME: str = QString(QObject::tr("Folder's name can't contain more than %1 characters!")).arg(QGEN_MAXFOLDERNAMELEN); break;
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

	void Controls::NewGame()
	{
		if ( !_container->IsEmpty() )
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

	void Controls::InitData()
	{
		_currentGamePath = QFileInfo(_currentPath, "NoName.qsp").absoluteFilePath();
		_currentGamePass = QString::fromWCharArray(QGEN_PASSWD);
		//InitSearchData();
		//_lastSaveTime = 0;
	}

	void Controls::UpdateActionsOnAllLocs()
	{
		size_t count = _container->GetLocationsCount();
		for (size_t i = 0; i < count; ++i)
			_locListBox->UpdateLocationActions(_container->GetLocationName(i));
	}

	bool Controls::UpdateLocale(QLocale::Language lang)
	{
		if (_translator) delete _translator;
		_translator = new QTranslator();
        QString langName = "qgen_" + QLocale(lang).name();
		QString langPath = _currentPath + QDir::separator() + "langs" + QDir::separator();

		return _translator->load(langName, langPath);
	}

    void Controls::UpdateOpenedLocationsIndexes()
    {
        LocationPage *page;
        size_t count = _tabsWidget->count();
        for (size_t index = 0; index < count; ++index)
        {
            page = ( LocationPage * )_tabsWidget->widget(index);
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
        QString message = _mainWindow->tr("This game contains %1 location(s)\n").arg(totalLocsCount);
        message += _mainWindow->tr("Locations without base description: %1\n").arg(totalEmptyDesc);
        message += _mainWindow->tr("Locations without \"on visit\" code: %1\n").arg(totalEmptyCode);
        message += _mainWindow->tr("Average count of actions per location: %1\n").arg(avgActions);
        message += _mainWindow->tr("Actions without code: %1\n").arg(totalEmptyActsCode);
        message += _mainWindow->tr("Max location size: %1 characters\n").arg(maxLocSize);
        message += _mainWindow->tr("Average location size: %1 characters\n").arg(avgSize);
        message += _mainWindow->tr("Total game size: %1 characters").arg(totalLocsSize);
        return message;
    }
}


