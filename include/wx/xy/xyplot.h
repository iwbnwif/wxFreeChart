/////////////////////////////////////////////////////////////////////////////
// Name:	xyplot.h
// Purpose: XY plot declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYPLOT_H_
#define XYPLOT_H_

#include <wx/array.h>

#include <wx/axisplot.h>
#include <wx/axis/numberaxis.h>

#include <wx/xy/xydataset.h>
#include <wx/xy/xyrenderer.h>

/**
 * An plot for displaying XY data values.
 */
class WXDLLEXPORT XYPlot : public AxisPlot
{
public:
	XYPlot();
	virtual ~XYPlot();

protected:
	//
	// AxisPlot
	//
	virtual bool AcceptAxis(Axis *axis);

	virtual bool AcceptDataset(Dataset *dataset);

	virtual void DrawDatasets(wxDC &dc, wxRect rc);
};

#endif /*XYPLOT_H_*/
