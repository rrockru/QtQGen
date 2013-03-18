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

#ifndef _LOCATION_PAGE_
#define _LOCATION_PAGE_

#include "locationdesc.h"
#include "locationcode.h"
#include "LocationActions.h"

namespace Ui
{
	class LocationPage :
		public QWidget,
		public ILocationPage
	{
	public:
		LocationPage(QWidget *parent, IControls *controls);
		
		void SetLocationIndex(size_t locIndex);
		size_t GetLocationIndex();

		void LoadPage();
        void SavePage();

		void ExpandCollapseAll(bool isExpanded);

		void SelectAction( size_t actIndex );
        size_t AddAction(const QString& name);
        long GetSelectedAction();
        void RenameAction( size_t actIndex, const QString& name );
        void DeleteAction( size_t actIndex );

        void SetFocusOnActionCode();

	private:
		IControls	*_controls;
		
		int			_locIndex;
		LocationDesc *_locDesc;
		LocationCode *_locCode;
		LocationActions *_locActs;
	};
} // namespace Ui

#endif // _LOCATION_PAGE_
