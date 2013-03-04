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
}


