/////////////////////////////////////////////////////////////////////////////
// Name:	bubbleplot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef BUBBLEPLOT_H_
#define BUBBLEPLOT_H_

#include <wx/axisplot.h>

class WXDLLEXPORT BubblePlot : public AxisPlot
{
public:
	BubblePlot();
	virtual ~BubblePlot();

protected:
	virtual bool AcceptAxis(Axis *axis);

	virtual bool AcceptDataset(Dataset *dataset);

	virtual void DrawDatasets(wxDC &dc, wxRect rc);
};

#endif /*BUBBLEPLOT_H_*/
