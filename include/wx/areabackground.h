/////////////////////////////////////////////////////////////////////////////
// Name:	areabackground.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef AREABACKGROUND_H_
#define AREABACKGROUND_H_

#include <wx/wxfreechartdefs.h>
#include <wx/hashmap.h>

#include <wx/drawobject.h>

/**
 * Base class for drawing area background.
 * Areas can be data area in Plot, chart background, etc...
 */
class WXDLLEXPORT AreaBackground : public DrawObject
{
public:
	AreaBackground();

	virtual ~AreaBackground();

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
class WXDLLEXPORT NoAreaBackground : public AreaBackground
{
public:
	NoAreaBackground();

	virtual ~NoAreaBackground();

	virtual void Draw(wxDC &dc, wxRect rc);
};

/**
 * Fills area with specified brush and draw outline of area
 * with specified pen.
 */
class WXDLLEXPORT FillAreaBackground : public AreaBackground
{
public:
	FillAreaBackground(wxPen borderPen = (wxPen) *wxBLACK_PEN, wxBrush fillBrush =  (wxBrush) *wxWHITE_BRUSH);

	virtual ~FillAreaBackground();

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
class WXDLLEXPORT GradientAreaBackground : public AreaBackground
{
public:
	/**
	 * Constructs new gradient area background.
	 * @param borderPen pen to draw border
	 * @param colour1 first gradient fill color
	 * @param colour2 second gradient fill color
	 * @param dir gradient fill direction
	 */
	GradientAreaBackground(wxPen borderPen = *wxBLACK_PEN,
			wxColour colour1 = wxColour(200, 220, 250),
			wxColour colour2 = wxColour(255, 255, 255),
			wxDirection dir = wxEAST);

	virtual ~GradientAreaBackground();

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

WX_DECLARE_HASH_MAP(int, AreaBackground *, wxIntegerHash, wxIntegerEqual, AreaBackgroundMap);
class WXDLLEXPORT AreaBackgroundMap;

class WXDLLEXPORT AreaBackgroundCollection
{
public:
	AreaBackgroundCollection();
	virtual ~AreaBackgroundCollection();

	void SetAreaBackground(int serie, AreaBackground *barArea);

	AreaBackground *GetAreaBackground(int serie);

private:
	AreaBackgroundMap m_areas;
};

#endif /*AREABACKGROUND_H_*/
