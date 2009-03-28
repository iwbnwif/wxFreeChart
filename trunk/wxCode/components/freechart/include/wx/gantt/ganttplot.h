/////////////////////////////////////////////////////////////////////////////
// Name:	ganttplot.h
// Purpose: gantt dataset implementation
// Author:	Moskvichev Andrey V.
// Created:	2009/03/23
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2009/03/23 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////


#ifndef GANTTPLOT_H_
#define GANTTPLOT_H_

#include <wx/axisplot.h>

class WXDLLEXPORT GanttPlot : public AxisPlot
{
public:
	GanttPlot();
	virtual ~GanttPlot();

protected:
	virtual bool AcceptAxis(Axis *axis);

	virtual bool AcceptDataset(Dataset *dataset);

	virtual void DrawDatasets(wxDC &dc, wxRect rc);
};

#endif /* GANTTPLOT_H_ */
