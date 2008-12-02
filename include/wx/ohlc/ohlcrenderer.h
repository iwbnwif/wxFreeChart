/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcrenderer.h
// Purpose: OHLC renderers base class declaration.
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCRENDERER_H_
#define OHLCRENDERER_H_

#include <wx/chartrenderer.h>

/**
 * Base class for displaying OHLC data.
 */
class WXDLLEXPORT OHLCRenderer : public Renderer
{
public:
	OHLCRenderer();
	virtual ~OHLCRenderer();

	/**
	 * Draws item.
	 * @param dc device context
	 * @param x coordinate
	 * @param open open value in graphical coordinates
	 * @param high high value in graphical coordinates
	 * @param low low value in graphical coordinates
	 * @param close close value in graphical coordinates
	 */
	virtual void DrawItem(wxDC &dc, wxCoord x, wxCoord open, wxCoord high, wxCoord low, wxCoord close) = 0;
};

#endif /*OHLCRENDERER_H_*/
