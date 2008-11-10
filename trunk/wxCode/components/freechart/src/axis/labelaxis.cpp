
/////////////////////////////////////////////////////////////////////////////
// Name:	labelaxis.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/labelaxis.h>
#include <wx/drawutils.h>

LabelAxis::LabelAxis(AXIS_LOCATION location)
: Axis(location)
{
	tickLabelsColor = *wxBLACK; // defaults
	tickFont = *wxSMALL_FONT;
	tickPen = *wxBLACK_PEN;

	marginMin = 5;
	marginMax = 5;
}

LabelAxis::~LabelAxis()
{
}

wxCoord LabelAxis::GetExtent(wxDC &dc)
{
	wxSize maxTextExtent = GetLongestLabelExtent(dc);
	if (IsVertical()) {
		return tickSize + tickLabelGap + maxTextExtent.x;
	}
	else {
		return tickSize + tickLabelGap + maxTextExtent.y;
	}
}

void LabelAxis::DrawTick(wxDC &dc, wxRect rc, wxString label, double value)
{
	wxSize labelExtent = dc.GetTextExtent(label);

	if (IsVertical()) {
		wxCoord y = ToGraphics(dc, rc.y, rc.height, value);

		switch (GetLocation()) {
		case AXIS_LEFT:
			dc.DrawLine(rc.x + rc.width - tickSize, y, rc.x + rc.width, y);
			dc.DrawText(label, rc.x + rc.width - tickSize - labelExtent.GetWidth() - tickLabelGap, y - labelExtent.GetHeight() / 2);
			break;
		case AXIS_RIGHT:
			dc.DrawLine(rc.x, y, rc.x + tickSize, y);
			dc.DrawText(label, rc.x + tickSize + tickLabelGap, y - labelExtent.GetHeight() / 2);
			break;
		default:
			break;
		}
	}
	else {
		wxCoord x = ToGraphics(dc, rc.x, rc.width, value);

		switch (GetLocation()) {
		case AXIS_TOP:
			dc.DrawLine(x, rc.y + rc.height - tickSize, x, rc.y + rc.height);
			dc.DrawText(label, x - labelExtent.GetWidth() / 2, rc.y + rc.height - tickSize - labelExtent.GetHeight() - tickLabelGap);
			break;
		case AXIS_BOTTOM:
			dc.DrawLine(x, rc.y, x, rc.y + tickSize);
			dc.DrawText(label, x - labelExtent.GetWidth() / 2, rc.y + tickSize + tickLabelGap);
			break;
		default:
			break;
		}
	}
}

void LabelAxis::DrawTicks(wxDC &dc, wxRect rc)
{
	if (!HasTicks())
		return ;

	// setup dc objects for tick labels and lines
	dc.SetFont(tickFont);
	dc.SetPen(tickPen);
	dc.SetTextForeground(tickLabelsColor);

	wxString label;
	for (int nStep = 0; ; nStep++) {
		if (IsEnd(nStep))
			break;

		label = wxEmptyString;
		GetLabel(nStep, label);

		double value = GetValue(nStep);
		DrawTick(dc, rc, label, value);
	}
}

void LabelAxis::DrawBorderLine(wxDC &dc, wxRect rc)
{
	switch (GetLocation()) {
		case AXIS_LEFT:
			dc.DrawLine(rc.x + rc.width, rc.y, rc.x + rc.width, rc.y + rc.height);
			break;
		case AXIS_RIGHT:
			dc.DrawLine(rc.x, rc.y, rc.x, rc.y + rc.height);
			break;
		case AXIS_TOP:
			dc.DrawLine(rc.x, rc.y + rc.height, rc.x + rc.width, rc.y + rc.height);
			break;
		case AXIS_BOTTOM:
			dc.DrawLine(rc.x, rc.y, rc.x + rc.width, rc.y);
			break;
	}
}
wxCoord LabelAxis::ToGraphics(wxDC &dc, int minG, int range, double value)
{
	minG += marginMin;
	range -= (marginMin + marginMax);
	if (range < 0)
		range = 0;

	return DoToGraphics(dc, minG, range, value);
}

void LabelAxis::DrawGridLines(wxDC &dc, wxRect rc)
{
	if (!HasTicks())
		return ;

	dc.SetPen(gridLinesPen);

	for (int nStep = 0; ; nStep++) {
		if (IsEnd(nStep))
			break;

		double value = GetValue(nStep);

		if (IsVertical()) {
			wxCoord y = ToGraphics(dc, rc.y, rc.height, value);

			dc.DrawLine(rc.x, y, rc.x + rc.width, y);
		}
		else {
			wxCoord x = ToGraphics(dc, rc.x, rc.width, value);

			dc.DrawLine(x, rc.y, x, rc.y + rc.height);
		}
	}
}

void LabelAxis::Draw(wxDC &dc, wxRect rc)
{
	DrawTicks(dc, rc);
	DrawBorderLine(dc, rc);
}

bool LabelAxis::HasTicks()
{
	return true;
}
