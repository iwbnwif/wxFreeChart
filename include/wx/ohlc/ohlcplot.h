
/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcplot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCPLOT_H_
#define OHLCPLOT_H_

#include <wx/axisplot.h>
#include <wx/ohlc/ohlcdataset.h>

#include <wx/axis/dateaxis.h>
#include <wx/axis/numberaxis.h>

/**
 * Open-High-Low-Close plot.
 */
class OHLCPlot : public AxisPlot
{
public:
	OHLCPlot();
	virtual ~OHLCPlot();

	//void AddDataset(OHLCDataset *dataset);

protected:
	virtual bool AcceptAxis(Axis *axis);

	virtual bool AcceptDataset(Dataset *dataset);

	virtual void DrawDatasets(wxDC &dc, wxRect rc);
};

#endif /*OHLCPLOT_H_*/
