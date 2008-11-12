
/////////////////////////////////////////////////////////////////////////////
// Name:	xyhistorenderer.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYHISTORENDERER_H_
#define XYHISTORENDERER_H_

#include <wx/xy/xyrenderer.h>
#include <wx/areabackground.h>

#include <wx/hashmap.h>

WX_DECLARE_HASH_MAP(int, AreaBackground *, wxIntegerHash, wxIntegerEqual, AreaBackgroundMap);

/**
 * Renderer for displaying XY data as histograms.
 */
class XYHistoRenderer : public XYRenderer, public DrawObserver
{
public:
	XYHistoRenderer(int _barWidth = 10, bool _vertical = true);
	virtual ~XYHistoRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset);

	virtual void Draw(wxDC &dc, wxRect rcData, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1);

	virtual void DrawLegendSymbol(wxDC &dc, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1);

	/**
	 * Set area fill to draw specified serie.
	 * XYHistoRenderer takes ownership over barArea.
	 * @param serie serie index
	 * @param barArea area background object to draw bars
	 */
	void SetBarArea(int serie, AreaBackground *barArea);

	AreaBackground *GetBarArea(int serie);

	//
	// DrawObserver
	//
	virtual void NeedRedraw(DrawObject *obj);

private:
	void DrawBar(int serie, wxDC &dc, wxRect rcData, wxCoord x, wxCoord y);

	int m_barWidth;
	bool m_vertical;

	wxCoord m_serieShift;

	AreaBackgroundMap m_barAreas;

	FillAreaBackground m_defaultBarArea;
};

#endif /*XYHISTORENDERER_H_*/
