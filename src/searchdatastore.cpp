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

#include "searchdatastore.h"

SearchDataStore::SearchDataStore()
{
}

void SearchDataStore::SaveSearchData( QSettings &settings )
{
    size_t count = _searchStrings.size();
    settings.remove("SearchData");
    for (size_t i = 0; i < count; i++)
        settings.setValue(QString("SearchData/Search%1_Text").arg(i), _searchStrings[i]);
    count = _replaceStrings.size();
    for (size_t i = 0; i < count; i++)
        settings.setValue(QString("SearchData/Replace%1_Text").arg(i), _replaceStrings[i]);
}

void SearchDataStore::LoadSearchData( QSettings &settings )
{
    QString str;
    size_t i = 0;
    _searchStrings.clear();
    _replaceStrings.clear();
    while (1)
    {
        str = settings.value(QString("SearchData/Search%1_Text").arg(i)).toString();
        if (str.isEmpty()) break;
        _searchStrings << str;
        ++i;
    }
    i = 0;
    while (1)
    {
        str = settings.value(QString("SearchData/Replace%1_Text").arg(i)).toString();
        if (str.isEmpty()) break;
        _replaceStrings << str;
        ++i;
    }
}

void SearchDataStore::AddSearchString( const QString &text )
{
    if (_searchStrings.indexOf(text) == -1)
    {
        size_t count = _searchStrings.count();
        if (count >= 10) _searchStrings.removeAt(count - 1);
    }
    else
        _searchStrings.removeOne(text);
    _searchStrings.insert(0, text);
}

void SearchDataStore::AddReplaceString( const QString &text )
{
    if (_replaceStrings.indexOf(text) == -1)
    {
        size_t count = _replaceStrings.count();
        if (count >= 10) _replaceStrings.removeAt(count - 1);
    }
    else
        _replaceStrings.removeOne(text);
    _replaceStrings.insert(0, text);
}
