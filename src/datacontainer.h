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

#ifndef _QGEN_DATA_CONTAINER_H_
    #define _QGEN_DATA_CONTAINER_H_

    namespace Ui
    {
        struct ActionData
        {
            QString pathPicture;            //Изображение для действия - относительный путь к файлу
            QString description;            //Описание действия
            QString onPress;                //Код события "выбор действия"
        };

        struct LocationData
        {
            QString        name;            //Название локации
            QString        description;    //Описание локации
            QString        onVisit;        //Код события "посещение локации"
            QList<ActionData>    actionArray;    //Массив действий
            int                folderIndex;    //Индекс секции
        };

        struct FolderData
        {
            QString    name;                //Имя секции
            int            pos;                //Позиция секции
        };

        class DataContainer
        {
        private:
            QList<LocationData>    locationArray;
            QList<FolderData>        _folders;
            bool                _isSaved;
        public:
            DataContainer();

            void Save() { _isSaved = true; }
            bool IsSaved() const { return _isSaved; }

            int AddLocation(const QString &name);
            bool RenameLocation(size_t locIndex, const QString& newName);
            void DeleteLocation(size_t locIndex);
            void ClearLocation(size_t locIndex);
            void DeleteAction(size_t locIndex, size_t actIndex);
            void DeleteAllActions(size_t locIndex);
            int AddAction(size_t indexLoc, const QString& actName);
            bool RenameAction(size_t locIndex, size_t actIndex, const QString& actNewName);
            void SetActionCode( size_t indexLoc,size_t indexAct, const QString& actCode );
            QString GetActionCode(size_t locIndex, size_t actIndex) const;
            int FindLocationIndex(const QString& locName) const;
            int FindActionIndex(size_t indexLoc, const QString& actName) const;
            size_t GetActionsCount(size_t locIndex) const;
            QString GetActionName(size_t locIndex, size_t actIndex) const;
            void SetLocationDesc(size_t indexLoc, const QString& desc);
            void SetLocationCode(size_t indexLoc, const QString& code);
            QString GetLocationDesc(size_t indexLoc) const;
            QString GetLocationCode(size_t indexLoc) const;
            void SortLocsInFolder(int folderIndex, bool isAscending);
            bool IsEmptyLoc(size_t locIndex) const;
            QString GetLocationName(const size_t &locIndex) const;
            bool SetActionPicturePath( size_t indexLoc, size_t indexAct, const QString &pathPict );
            QString GetActionPicturePath( size_t locIndex, size_t actIndex ) const;
            size_t GetLocationsCount() const;
            void Clear();
            bool IsEmpty() const;
            bool GetLocActions( size_t indexLoc, QStringList & actions ) const;
            void MoveLocationTo(size_t locIndex, size_t moveTo);
            void MoveActionTo(size_t locIndex, size_t actIndex, size_t moveTo);

            size_t GetFoldersCount() const;
            QString GetFolderName(size_t index) const;
            void SetLocFolder(size_t locIndex, int folderIndex);
            int GetLocFolder(size_t locIndex) const;
            int AddFolder(const QString &name);
            bool RenameFolder(size_t folderIndex, const QString &newName);
            void DeleteFolder(size_t folderIndex);
            int FindFolderIndex(const QString &name) const;
            void MoveFolder(size_t folderIndex, size_t moveToSecPos);
            void SetFolderPos(size_t folderIndex, long pos);
            int FindFolderForPos(size_t pos) const;
        };
    } // namespace Ui
#endif
