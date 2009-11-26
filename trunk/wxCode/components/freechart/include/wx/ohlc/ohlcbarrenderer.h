/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcbarrenderer.h
// Purpose: OHLC bar renderer declarations
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
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
};

#endif /*OHLCBARRENDERER_H_*/
