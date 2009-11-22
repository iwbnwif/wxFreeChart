/////////////////////////////////////////////////////////////////////////////
// Name:	barplot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef BARPLOT_H_
#define BARPLOT_H_

//#include <wx/axisplot.h>
#include <wx/xy/xyplot.h>

#include <wx/category/categorydataset.h>

/**
 * Plot for displaying histograms with values at one axis and
 * category names at other.
 */
class WXDLLIMPEXP_FREECHART BarPlot : public XYPlot//AxisPlot
{
public:
	BarPlot();
	virtual ~BarPlot();

protected:
	virtual bool AcceptAxis(Axis *axis);

	virtual bool AcceptDataset(Dataset *dataset);

	virtual void DrawDatasets(wxDC &dc, wxRect rc);
};

#endif /*BARPLOT_H_*/
