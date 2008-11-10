
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

/**
 * Renderer for displaying XY data as histograms.
 */
class XYHistoRenderer : public XYRenderer
{
public:
	XYHistoRenderer(int _barWidth = 10, bool _vertical = true);
	virtual ~XYHistoRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset);

	virtual void Draw(wxDC &dc, wxRect rcData, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1);

	virtual void DrawLegendSymbol(wxDC &dc, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1);

	void SetBarArea(AreaBackground *_barArea)
	{
		SAFE_REPLACE(barArea, _barArea);
		FireNeedRedraw();
	}

private:
	void DrawBar(wxDC &dc, wxRect rcData, wxCoord x, wxCoord y);

	int barWidth;
	bool vertical;

	wxCoord serieShift;

	AreaBackground *barArea;
};

#endif /*XYHISTORENDERER_H_*/
