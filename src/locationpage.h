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
