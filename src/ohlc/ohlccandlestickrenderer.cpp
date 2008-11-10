
/////////////////////////////////////////////////////////////////////////////
// Name:	ohlccandlestickrenderer.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/ohlc/ohlccandlestickrenderer.h>

OHLCCandlestickRenderer::OHLCCandlestickRenderer()
{
	pen = *wxBLACK_PEN;

	lowerBrush = *wxBLACK_BRUSH;
	higherBrush = *wxWHITE_BRUSH;

	candleWidth = 5;
}

OHLCCandlestickRenderer::~OHLCCandlestickRenderer()
{
}

void OHLCCandlestickRenderer::DrawItem(wxDC &dc, wxCoord x, wxCoord open, wxCoord high, wxCoord low, wxCoord close)
{
	wxCoord leftX = x - candleWidth;
	wxCoord centerX = x;

	dc.SetPen(pen);
	dc.DrawLine(centerX, low, centerX, high);

	wxCoord height;
	wxCoord y;

	if (open > close) {
		height = open - close;
		y = close;
		dc.SetBrush(higherBrush);
	}
	else {
		height = close - open;
		y = open;
		dc.SetBrush(lowerBrush);
	}

	dc.DrawRectangle(leftX, y, 2 * candleWidth, height);
}
