/////////////////////////////////////////////////////////////////////////////
// Name:    ohlcplot.h
// Purpose: OHLC plot declaration.
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCPLOT_H_
#define OHLCPLOT_H_

#include <wx/xy/xyplot.h>
#include <wx/ohlc/ohlcdataset.h>

struct OHLCItem
{
    OHLCItem() {}
    OHLCItem(double o, double h, double l, double c, size_t v = 0) :
    open(o), high(h), low(l), close(c), volume(v)
    { }
    
	double open;
	double high;
	double low;
	double close;

	size_t volume;
};

/**
 * Open-High-Low-Close plot.
 *
 * TODO:
 *  - technical indicators support
 *  - grapical objects support, like levels, fibo-retracements, fractals, etc.
 */
class WXDLLIMPEXP_FREECHART OHLCPlot : public XYPlot
{
public:
    OHLCPlot();
    virtual ~OHLCPlot();

protected:
    virtual bool AcceptAxis(Axis *axis);

    virtual bool AcceptDataset(Dataset *dataset);

    virtual void DrawDatasets(wxDC &dc, wxRect rc);

    /**
     * Draw single OHLC dataset.
     * @param dc device context
     * @param rc rectangle where to draw
     * @param dataset OHLC dataset to draw
     */
    virtual void DrawOHLCData(wxDC &dc, wxRect rc, BiDataSet* dataset);
};

#endif /*OHLCPLOT_H_*/
