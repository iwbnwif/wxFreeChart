/////////////////////////////////////////////////////////////////////////////
// Name:	xyzrenderer.h
// Purpose: xyz renderer declaration
// Author:	Moskvichev Andrey V.
// Created:	2009/04/04
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2009/04/04 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYZRENDERER_H_
#define XYZRENDERER_H_

#include <wx/chartrenderer.h>
#include <wx/axis/axis.h>
#include <wx/xyz/xyzdataset.h>

/**
 *
 */
class WXDLLIMPEXP_FREECHART XYZRenderer : public Renderer
{
	DECLARE_CLASS(XYZRenderer)
public:
	XYZRenderer(int minRad, int maxRad);
	virtual ~XYZRenderer();

	void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYZDataset *dataset);

	virtual void SetSerieColor(int serie, wxColour *color);

	virtual wxColour GetSerieColor(int serie);

	/**
	 * Sets pen to draw serie circles.
	 * @param serie serie index
	 * @param pen pen for serie
	 */
	void SetSeriePen(int serie, wxPen *pen);

	/**
	 * Returns pen, used to draw specified serie lines.
	 * @param serie serie index
	 * @return pen
	 */
	wxPen *GetSeriePen(int serie);

	/**
	 * Sets brush to fill serie circles.
	 * @param serie serie index
	 * @param brush brush for serie
	 */
	void SetSerieBrush(int serie, wxBrush *brush);

	/**
	 * Returns brush, used to fill specified serie circles.
	 * @param serie serie index
	 * @return brush
	 */
	wxBrush *GetSerieBrush(int serie);


private:
	int m_minRad;
	int m_maxRad;

	PenMap m_seriePens;
	int m_defaultPenWidth;
	int m_defaultPenStyle;

	BrushMap m_serieBrushs;
	int m_defaultBrushStyle;
};

#endif /* XYZRENDERER_H_ */
