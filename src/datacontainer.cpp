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

#include "datacontainer.h"

namespace Ui
{
    int CmpLocationsAsc(const QString &first, const QString &second)
    {
        return first.compare(second, Qt::CaseInsensitive);
    }

    int CmpLocationsDesc(const QString &first, const QString &second)
    {
        return second.compare(first, Qt::CaseInsensitive);
    }

    DataContainer::DataContainer()
    {
        _isSaved = true;
    }

    int DataContainer::FindFolderIndex( const QString &name ) const
    {
        QString lwrName(name.toLower());
        int i, count = _folders.count();
        for (i = 0; i < count; ++i)
            if (lwrName == _folders[i].name.toLower()) return i;
        return -1;
    }

    int DataContainer::FindLocationIndex(const QString & nameLocation) const
    {
        QString lwrName(nameLocation.toLower());
        int i, count = locationArray.count();
        for (i = 0; i < count; ++i)
            if (lwrName == locationArray[i].name.toLower()) return i;
        return -1;
    }

    int DataContainer::FindActionIndex(size_t indexLoc, const QString& actName) const
    {
        QString lwrName(actName.toLower());
        LocationData loc = locationArray[indexLoc];
        int i, count = loc.actionArray.count();
        for (i = 0; i < count; ++i)
            if (lwrName == loc.actionArray[i].description.toLower()) return i;
        return -1;
    }

    int DataContainer::AddLocation(const QString &name)
    {
        if (FindLocationIndex(name) >= 0) return -1;
        LocationData loc;
        loc.name = name;
        loc.folderIndex = -1;
        locationArray.append(loc);
        _isSaved = false;
        return locationArray.count() - 1;
    }

    bool DataContainer::RenameLocation(size_t locIndex, const QString& newName)
    {
        int index = FindLocationIndex(newName);
        if (index >= 0 && index != locIndex) return false;
        locationArray[locIndex].name = newName;
        _isSaved = false;
        return true;
    }

    void DataContainer::DeleteLocation( size_t locIndex )
    {
        locationArray.removeAt(locIndex);
        _isSaved = false;
    }

    void DataContainer::DeleteAction( size_t locIndex, size_t actIndex )
    {
        locationArray[locIndex].actionArray.removeAt(actIndex);
        _isSaved = false;
    }

    int DataContainer::AddAction(size_t indexLoc, const QString& actName)
    {
        if (FindActionIndex(indexLoc, actName) >= 0) return -1;
        ActionData act;
        act.description = actName;
        locationArray[indexLoc].actionArray.append(act);
        _isSaved = false;
        return locationArray[indexLoc].actionArray.count() - 1;
    }

    bool DataContainer::RenameAction(size_t locIndex, size_t actIndex, const QString& actNewName)
    {
        int index = FindActionIndex(locIndex, actNewName);
        if (index >= 0 && index != actIndex) return false;
        locationArray[locIndex].actionArray[actIndex].description = actNewName;
        _isSaved = false;
        return true;
    }

    void DataContainer::SetActionCode( size_t indexLoc,size_t indexAct, const QString& actCode )
    {
        locationArray[indexLoc].actionArray[indexAct].onPress = actCode;
        _isSaved = false;
    }

    QString DataContainer::GetActionCode(size_t locIndex, size_t actIndex) const
    {
        return locationArray[locIndex].actionArray[actIndex].onPress;
    }

    size_t DataContainer::GetActionsCount( size_t locIndex ) const
    {
        return locationArray[locIndex].actionArray.count();
    }

    QString DataContainer::GetActionName(size_t locIndex, size_t actIndex) const
    {
        return locationArray[locIndex].actionArray[actIndex].description;
    }

    void DataContainer::SetLocationDesc(size_t indexLoc, const QString& desc)
    {
        locationArray[indexLoc].description = desc;
        _isSaved = false;
    }

    void DataContainer::SetLocationCode(size_t indexLoc, const QString& code)
    {
        locationArray[indexLoc].onVisit = code;
        _isSaved = false;
    }

    QString DataContainer::GetLocationDesc(size_t indexLoc) const
    {
        return locationArray.at(indexLoc).description;
    }

    QString DataContainer::GetLocationCode(size_t indexLoc) const
    {
        return locationArray.at(indexLoc).onVisit;
    }

    void DataContainer::ClearLocation(size_t locIndex)
    {
        locationArray[locIndex].description.clear();
        locationArray[locIndex].onVisit.clear();
        locationArray[locIndex].actionArray.clear();
        _isSaved = false;
    }

    void DataContainer::DeleteAllActions( size_t locIndex )
    {
        locationArray[locIndex].actionArray.clear();
        _isSaved = false;
    }

    bool DataContainer::IsEmptyLoc(size_t locIndex) const
    {
        if (locationArray[locIndex].onVisit.isEmpty() &&
            locationArray[locIndex].description.isEmpty() &&
            locationArray[locIndex].actionArray.isEmpty()) return true;
        return false;
    }

    QString DataContainer::GetLocationName(const size_t &locIndex) const
    {
        return locationArray.at(locIndex).name;
    }

    QString DataContainer::GetActionPicturePath( size_t locIndex, size_t actIndex ) const
    {
        return locationArray.at(locIndex).actionArray.at(actIndex).pathPicture;
    }

    bool DataContainer::SetActionPicturePath( size_t indexLoc, size_t indexAct, const QString &pathPict )
    {
        locationArray[indexLoc].actionArray[indexAct].pathPicture = pathPict;
        _isSaved = false;
        return true;
    }

    size_t DataContainer::GetLocationsCount() const
    {
        return locationArray.count();
    }

    void DataContainer::Clear()
    {
        locationArray.clear();
        _folders.clear();
        _isSaved = false;
    }

    bool DataContainer::IsEmpty() const
    {
        return locationArray.isEmpty();
    }

    bool DataContainer::GetLocActions( size_t indexLoc, QStringList & actions ) const
    {
        actions.clear();
        for (size_t i = 0; i < locationArray[indexLoc].actionArray.count(); ++i)
            actions << locationArray[indexLoc].actionArray[i].description;
        return true;
    }

    void DataContainer::MoveLocationTo( size_t locIndex, size_t moveTo )
    {
        if (locIndex == moveTo) return;
        locationArray.move(locIndex, moveTo);
        _isSaved = false;
    }

    void DataContainer::MoveActionTo( size_t locIndex, size_t actIndex, size_t moveTo )
    {
        if (actIndex == moveTo) return;
        locationArray[locIndex].actionArray.move(actIndex, moveTo);
        _isSaved = false;
    }

    void DataContainer::SetLocFolder( size_t locIndex, int folderIndex )
    {
        if (locationArray[locIndex].folderIndex == folderIndex)
            return;
        locationArray[locIndex].folderIndex = folderIndex;
        _isSaved = false;
    }

    int DataContainer::GetLocFolder( size_t locIndex ) const
    {
        return locationArray[locIndex].folderIndex;
    }

    int DataContainer::AddFolder( const QString &name )
    {
        if (FindFolderIndex(name) >= 0) return -1;
        FolderData data;
        data.name = name;
        data.pos = -1;
        _folders.append(data);
        _isSaved = false;
        return _folders.count() - 1;
    }

    bool DataContainer::RenameFolder( size_t folderIndex, const QString &newName )
    {
        int index = FindFolderIndex(newName);
        if (index >= 0 && index != folderIndex) return false;
        _folders[folderIndex].name = newName;
        _isSaved = false;
        return true;
    }

    void DataContainer::DeleteFolder( size_t folderIndex )
    {
        long count = locationArray.count();
        for (long i = count - 1; i >= 0; --i)
        {
            if (locationArray[i].folderIndex == folderIndex)
                locationArray[i].folderIndex = -1;
            else if (locationArray[i].folderIndex > (int)folderIndex)
                locationArray[i].folderIndex--;
        }
        count = _folders.count();
        for (long i = count - 1; i >= 0; --i)
        {
            if ((size_t) i > folderIndex)
                _folders[i].pos--;
        }
        _folders.removeAt(folderIndex);
        _isSaved = false;
    }

    void DataContainer::MoveFolder( size_t folderIndex, size_t moveToSecPos )
    {
        if (folderIndex == moveToSecPos) return;
        _folders.move(folderIndex, moveToSecPos);
        _isSaved = false;
    }

    void DataContainer::SetFolderPos( size_t folderIndex, long pos )
    {
        if (_folders[folderIndex].pos == pos) return;
        _folders[folderIndex].pos = pos;
        _isSaved = false;
    }

    size_t DataContainer::GetFoldersCount() const
    {
        return _folders.count();
    }

    QString DataContainer::GetFolderName( size_t index ) const
    {
        return _folders[index].name;
    }

    int DataContainer::FindFolderForPos( size_t pos ) const
    {
        size_t count = _folders.count();
        for (size_t i = 0; i < count; ++i)
        {
            if (_folders[i].pos == pos)
                return i;
        }
        return -1;
    }

    void DataContainer::SortLocsInFolder( int folderIndex, bool isAscending )
    {
        QStringList names;
        QList<int> positions;
        LocationData data = locationArray.takeAt(0);
        size_t count = locationArray.count();
        long startIndex = -1;
        for (size_t i = 0; i < count; ++i)
        {
            if (locationArray[i].folderIndex == folderIndex)
            {
                if (startIndex < 0) startIndex = i;
                positions << startIndex;
                names << locationArray[i].name;
            }
            else
                startIndex = -1;
        }
        if (isAscending)
            names.sort();
        else
            names.sort();
        size_t namesCount = names.count();
        for (size_t i = 0; i < namesCount; ++i)
        {
            long index = FindLocationIndex(names[i]);
            long moveTo = i + positions[i];
            if (moveTo >= count)
                moveTo = count - 1;
            MoveLocationTo(index, moveTo);
        }
        locationArray.insert(0, data);
    }
}
