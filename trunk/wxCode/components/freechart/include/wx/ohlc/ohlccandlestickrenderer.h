/////////////////////////////////////////////////////////////////////////////
// Name:	ohlccandlestickrenderer.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCCANDDLESTICKRENDERER_H_
#define OHLCCANDDLESTICKRENDERER_H_

#include <wx/ohlc/ohlcrenderer.h>

/**
 * OHLC renderer for displaying jananese candles.
 */
class WXDLLIMPEXP_FREECHART OHLCCandlestickRenderer : public OHLCRenderer
{
public:
	OHLCCandlestickRenderer();
	virtual ~OHLCCandlestickRenderer();

	void DrawItem(wxDC &dc, wxCoord x, wxCoord open, wxCoord high, wxCoord low, wxCoord close);

private:
	wxCoord m_candleRadius;

	wxPen m_outlinePen;
	wxBrush m_lowerBrush;
	wxBrush m_higherBrush;
};

#endif /*OHLCCANDDLESTICKRENDERER_H_*/
