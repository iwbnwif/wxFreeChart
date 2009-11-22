/////////////////////////////////////////////////////////////////////////////
// Name:	drawutils.h
// Purpose: Defines some useful drawing utilities.
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DRAWUTILS_H_
#define DRAWUTILS_H_

/**
 * Draws text, where center defined by [x,y]
 * @param dc device context
 * @param x x coordinate of center
 * @param y y coordinate of center
 * @param text text to draw
 */
inline static void DrawTextCenter(wxDC &dc, wxCoord x, wxCoord y, wxString text)
{
	wxSize textExtent = dc.GetTextExtent(text);

	x -= textExtent.x / 2;
	y -= textExtent.y / 2;

	dc.DrawText(text, x, y);
}

/**
 * Draws text in center of rectangle.
 * @param dc device context
 * @param rc rectangle where to draw text
 * @param text text to draw
 */
inline static void DrawTextCenter(wxDC &dc, wxRect &rc, wxString text)
{
	wxSize textExtent = dc.GetTextExtent(text);

	wxCoord x = rc.x + (rc.GetWidth() - textExtent.x) / 2;
	wxCoord y = rc.y + (rc.GetHeight() - textExtent.y) / 2;

	dc.DrawText(text, x, y);
}

inline static void CheckFixRect(wxRect &rc)
{
	if (rc.x < 0)
		rc.x = 0;
	if (rc.y < 0)
		rc.y = 0;
	if (rc.width < 0)
		rc.width = 0;
	if (rc.height < 0)
		rc.height = 0;
}

/**
 *
 */
inline static void Margins(wxRect &rc, wxCoord left, wxCoord top, wxCoord right, wxCoord bottom)
{
	if ((left + right) > rc.width) {
		rc.x = left;
		rc.width = 0; //XXX
	}
	else {
		rc.x += left;
		rc.width -= (left + right);
	}

	if ((top + bottom) > rc.height) {
		rc.y = top;
		rc.height = 0; //XXX
	}
	else {
		rc.y += top;
		rc.height -= (top + bottom);
	}

	CheckFixRect(rc);
}

inline static void SetupRect(wxRect &rc, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1)
{
	if (x0 < x1) {
		rc.x = x0;
		rc.width = x1 - x0;
	}
	else {
		rc.x = x1;
		rc.width = x0 - x1;
	}

	if (y0 < y1) {
		rc.y = y0;
		rc.height = y1 - y0;
	}
	else {
		rc.y = y1;
		rc.height = y0 - y1;
	}
}

#endif /*DRAWUTILS_H_*/
