/////////////////////////////////////////////////////////////////////////////
// Name:	areadraw.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef AREADRAW_H_
#define AREADRAW_H_

#include <wx/wxfreechartdefs.h>
#include <wx/hashmap.h>

#include <wx/drawobject.h>

/**
 * Base class for drawing area background.
 * Areas can be data area in Plot, chart background, etc...
 */
class WXDLLIMPEXP_FREECHART AreaDraw : public DrawObject
{
public:
	AreaDraw();

	virtual ~AreaDraw();

	/**
	 * Draw area background.
	 * @param dc device context
	 * @param rc rectangle of area to draw
	 */
	virtual void Draw(wxDC &dc, wxRect rc) = 0;
};

/**
 * Doing nothing.
 */
class WXDLLIMPEXP_FREECHART NoAreaDraw : public AreaDraw
{
public:
	NoAreaDraw();

	virtual ~NoAreaDraw();

	virtual void Draw(wxDC &dc, wxRect rc);
};

/**
 * Fills area with specified brush and draw outline of area
 * with specified pen.
 */
class WXDLLIMPEXP_FREECHART FillAreaDraw : public AreaDraw
{
public:
	FillAreaDraw(wxPen borderPen = (wxPen) *wxBLACK_PEN, wxBrush fillBrush =  (wxBrush) *wxWHITE_BRUSH);

	virtual ~FillAreaDraw();

	virtual void Draw(wxDC &dc, wxRect rc);

	/**
	 * Sets border len.
	 * @param borderPen border pen
	 */
	void SetBorderPen(wxPen borderPen)
	{
		m_borderPen = borderPen;
		FireNeedRedraw();
	}

	/**
	 * Sets fill brush.
	 * @param fillBrush fill brush
	 */
	void SetFillBrush(wxBrush fillBrush)
	{
		m_fillBrush = fillBrush;
		FireNeedRedraw();
	}

private:
	wxBrush m_fillBrush;
	wxPen m_borderPen;
};

/**
 * Gradient fill area.
 */
class WXDLLIMPEXP_FREECHART GradientAreaDraw : public AreaDraw
{
public:
	/**
	 * Constructs new gradient area background.
	 * @param borderPen pen to draw border
	 * @param colour1 first gradient fill color
	 * @param colour2 second gradient fill color
	 * @param dir gradient fill direction
	 */
	GradientAreaDraw(wxPen borderPen = *wxBLACK_PEN,
			wxColour colour1 = wxColour(200, 220, 250),
			wxColour colour2 = wxColour(255, 255, 255),
			wxDirection dir = wxEAST);

	virtual ~GradientAreaDraw();

	virtual void Draw(wxDC &dc, wxRect rc);

	/**
	 * Sets gradient fill first color.
	 * @param colour1 first color
	 */
	void SetColour1(wxColour colour1)
	{
		m_colour1 = colour1;
		FireNeedRedraw();
	}

	/**
	 * Sets gradient fill second color.
	 * @param _colour2 second color
	 */
	void SetColour2(wxColour colour2)
	{
		m_colour2 = colour2;
		FireNeedRedraw();
	}

	/**
	 * Sets gradient fill direction.
	 * @param _dir direction
	 */
	void SetDirection(wxDirection dir)
	{
		m_dir = dir;
		FireNeedRedraw();
	}

private:
	wxPen m_borderPen;

	wxColour m_colour1;
	wxColour m_colour2;
	wxDirection m_dir;
};

WX_DECLARE_HASH_MAP(int, AreaDraw *, wxIntegerHash, wxIntegerEqual, AreaDrawMap);
class WXDLLIMPEXP_FREECHART AreaDrawMap;

/**
 * Collection of areadraws for series.
 * Used by bar charts, etc.
 */
class WXDLLIMPEXP_FREECHART AreaDrawCollection
{
public:
	AreaDrawCollection();
	virtual ~AreaDrawCollection();

	/**
	 * Set areadraw for serie.
	 * @param serie serie index
	 * @param areaDraw areadraw for serie
	 */
	void SetAreaDraw(int serie, AreaDraw *areaDraw);

	/**
	 * Returns areadraw, if any, for serie.
	 * @param serie serie index
	 * @return areadraw
	 */
	AreaDraw *GetAreaDraw(int serie);

private:
	AreaDrawMap m_areas;
};

#endif /*AREADRAW_H_*/
