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

#include <wx/wx.h>
#include <wx/drawobject.h>

/**
 * Base class for drawing area background.
 * Areas can be data area in Plot, chart background, etc...
 */
class AreaBackground : public DrawObject
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
class NoAreaBackground : public AreaBackground
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
class FillAreaBackground : public AreaBackground
{
public:
	FillAreaBackground(wxPen _borderPen = (wxPen) *wxBLACK_PEN, wxBrush _fillBrush =  (wxBrush) *wxWHITE_BRUSH);

	virtual ~FillAreaBackground();

	virtual void Draw(wxDC &dc, wxRect rc);

	/**
	 * Sets border len.
	 * @param _borderPen border pen
	 */
	void SetBorderPen(wxPen _borderPen)
	{
		borderPen = _borderPen;
		FireNeedRedraw();
	}

	/**
	 * Sets fill brush.
	 * @param _fillBrush fill brush
	 */
	void SetFillBrush(wxBrush _fillBrush)
	{
		fillBrush = _fillBrush;
		FireNeedRedraw();
	}

private:
	wxBrush fillBrush;
	wxPen borderPen;
};

/**
 * Gradient fill area.
 */
class GradientAreaBackground : public AreaBackground
{
public:
	/**
	 * Constructs new gradient area background.
	 * @param _borderPen pen to draw border
	 * @param _colour1 first gradient fill color
	 * @param _colour2 second gradient fill color
	 * @param _dir gradient fill direction
	 */
	GradientAreaBackground(wxPen _borderPen = *wxBLACK_PEN,
			wxColour _colour1 = wxColour(200, 220, 250),
			wxColour _colour2 = wxColour(255, 255, 255),
			wxDirection _dir = wxEAST);

	virtual ~GradientAreaBackground();

	virtual void Draw(wxDC &dc, wxRect rc);

	/**
	 * Sets gradient fill first color.
	 * @param _colour1 first color
	 */
	void SetColour1(wxColour _colour1)
	{
		colour1 = _colour1;
		FireNeedRedraw();
	}

	/**
	 * Sets gradient fill second color.
	 * @param _colour2 second color
	 */
	void SetColour2(wxColour _colour2)
	{
		colour2 = _colour2;
		FireNeedRedraw();
	}

	/**
	 * Sets gradient fill direction.
	 * @param _dir direction
	 */
	void SetDirection(wxDirection _dir)
	{
		dir = _dir;
		FireNeedRedraw();
	}

private:
	wxPen borderPen;

	wxColour colour1;
	wxColour colour2;
	wxDirection dir;
};

#endif /*AREABACKGROUND_H_*/
