/////////////////////////////////////////////////////////////////////////////
// Name:	xyhistorenderer.h
// Purpose: xy histogram renderer declarations
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYHISTORENDERER_H_
#define XYHISTORENDERER_H_

#include <wx/xy/xyrenderer.h>
#include <wx/areadraw.h>

/**
 * Renderer for displaying XY data as histograms.
 */
class WXDLLIMPEXP_FREECHART XYHistoRenderer : public XYRenderer, public DrawObserver
{
	DECLARE_CLASS(XYHistoRenderer)
public:
	/**
	 * Constructs new XYHistoRenderer.
	 * @param barWidth width to histogram bars
	 * @param vertical true to draw vertical bars, false - to horizontal
	 */
	XYHistoRenderer(int barWidth = 10, bool vertical = true);
	virtual ~XYHistoRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset);

	/**
	 * Set area fill to draw specified serie.
	 * XYHistoRenderer takes ownership of barArea.
	 * @param serie serie index
	 * @param barArea area background object to draw bars
	 */
	void SetBarArea(int serie, AreaDraw *barArea);

	/**
	 * Returns area draw for specified serie.
	 * @param serie serie index
	 * @return area draw for specified serie
	 */
	AreaDraw *GetBarArea(int serie);

	//
	// DrawObserver
	//
	virtual void NeedRedraw(DrawObject *obj);

private:
	void DrawBar(int serie, wxDC &dc, wxRect rcData, wxCoord x, wxCoord y);

	int m_barWidth;
	bool m_vertical;

	wxCoord m_serieShift;

	AreaDrawCollection m_barAreas;
};

#endif /*XYHISTORENDERER_H_*/
