#ifndef _LOCATION_PAGE_
#define _LOCATION_PAGE_

#include "locationdesc.h"
#include "locationcode.h"
#include "actionslist.h"
#include "actioncode.h"

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

		void ExpandCollapseAll(bool isExpanded);

	private:
		IControls	*_controls;
		
		int			_locIndex;
		LocationDesc *_locDesc;
		LocationCode *_locCode;
	};
} // namespace Ui

#endif // _LOCATION_PAGE_