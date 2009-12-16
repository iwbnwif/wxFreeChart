/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcbarrenderer.h
// Purpose: OHLC bar renderer declarations
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCBARRENDERER_H_
#define OHLCBARRENDERER_H_

#include <wx/ohlc/ohlcrenderer.h>

/**
 * OHLC renderer for displaying bars.
 */
class WXDLLIMPEXP_FREECHART OHLCBarRenderer : public OHLCRenderer
{
public:
	OHLCBarRenderer();
	virtual ~OHLCBarRenderer();

	virtual void DrawItem(wxDC &dc, wxCoord x, wxCoord open, wxCoord high, wxCoord low, wxCoord close);

private:
	wxPen m_barPen;
};

#endif /*OHLCBARRENDERER_H_*/
