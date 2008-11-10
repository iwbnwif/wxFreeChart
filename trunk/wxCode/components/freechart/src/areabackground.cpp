
/////////////////////////////////////////////////////////////////////////////
// Name:	areabackground.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/areabackground.h>

AreaBackground::AreaBackground()
{
}

AreaBackground::~AreaBackground()
{
}

NoAreaBackground::NoAreaBackground()
{
}

NoAreaBackground::~NoAreaBackground()
{
}

void NoAreaBackground::Draw(wxDC &dc, wxRect rc)
{
	// do nothing
}


FillAreaBackground::FillAreaBackground(wxPen _borderPen, wxBrush _fillBrush)
{
	fillBrush = _fillBrush;
	borderPen = _borderPen;
}

FillAreaBackground::~FillAreaBackground()
{
}

void FillAreaBackground::Draw(wxDC &dc, wxRect rc)
{
	dc.SetPen(borderPen);
	dc.SetBrush(fillBrush);
	dc.DrawRectangle(rc);
}

GradientAreaBackground::GradientAreaBackground(wxPen _borderPen, wxColour _colour1, wxColour _colour2, wxDirection _dir)
{
	borderPen = _borderPen;
	colour1 = _colour1;
	colour2 = _colour2;
	dir = _dir;
}

GradientAreaBackground::~GradientAreaBackground()
{
}

void GradientAreaBackground::Draw(wxDC &dc, wxRect rc)
{
	dc.GradientFillLinear(rc, colour1, colour2, dir);

	dc.SetPen(borderPen);
	dc.SetBrush(noBrush);
	dc.DrawRectangle(rc);
}
