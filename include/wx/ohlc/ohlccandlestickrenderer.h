
/////////////////////////////////////////////////////////////////////////////
// Name:	ohlccandlestickrenderer.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCCANDDLESTICKRENDERER_H_
#define OHLCCANDDLESTICKRENDERER_H_

#include <wx/ohlc/ohlcrenderer.h>

/**
 * OHLC renderer for displaying jananese candles.
 */
class OHLCCandlestickRenderer : public OHLCRenderer
{
public:
	OHLCCandlestickRenderer();
	virtual ~OHLCCandlestickRenderer();

	void DrawItem(wxDC &dc, wxCoord x, wxCoord open, wxCoord high, wxCoord low, wxCoord close);

private:
	wxCoord candleWidth;

	wxPen pen;
	wxBrush lowerBrush;
	wxBrush higherBrush;
};

#endif /*OHLCCANDDLESTICKRENDERER_H_*/
