/////////////////////////////////////////////////////////////////////////////
// Name:	labelaxis.cpp
// Purpose: label axis implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/labelaxis.h>
#include <wx/drawutils.h>

IMPLEMENT_CLASS(LabelAxis, Axis)

LabelAxis::LabelAxis(AXIS_LOCATION location)
: Axis(location)
{
	// defaults
	m_labelColour = *wxBLACK;
	m_labelFont = *wxSMALL_FONT;
	m_labelPen = *wxBLACK_PEN;
	m_titleFont = *wxNORMAL_FONT;
	m_titleColour = *wxBLACK;
	m_titleLocation = wxCENTER;
	m_marginMin = 5;
	m_marginMax = 5;
}

LabelAxis::~LabelAxis()
{
}

wxCoord LabelAxis::GetExtent(wxDC &dc)
{
	wxSize maxTextExtent = GetLongestLabelExtent(dc);
	wxCoord extent = labelLineSize + labelGap;

	wxSize titleExtent;

	if (m_title.Length() != 0) {
		dc.SetFont(m_titleFont);
		titleExtent = dc.GetTextExtent(m_title);
	}

	if (IsVertical()) {
		extent += maxTextExtent.x;
		extent += titleExtent.x;
	}
	else {
		extent += maxTextExtent.y;
		extent += titleExtent.y;
	}
	return extent;
}

void LabelAxis::DrawLabel(wxDC &dc, wxRect rc, const wxString &label, double value)
{
	wxSize labelExtent = dc.GetTextExtent(label);

	wxCoord x, y;
	wxCoord textX, textY;
	wxCoord lineX1, lineY1;
	wxCoord lineX2, lineY2;

	if (IsVertical()) {
		y = ToGraphics(dc, rc.y, rc.height, value);
		textY = y - labelExtent.GetHeight() / 2;

		lineY1 = lineY2 = y;

		switch (GetLocation()) {
		case AXIS_LEFT:
			lineX1 = rc.x + rc.width - labelLineSize;
			lineX2 = rc.x + rc.width;

			textX = rc.x + rc.width - labelLineSize - labelExtent.GetWidth() - labelGap;
			break;
		case AXIS_RIGHT:
			lineX1 = rc.x;
			lineX2 = rc.x + labelLineSize;

			textX = rc.x + labelLineSize + labelGap;
			break;
		default:
			return ; // BUG
		}
	}
	else {
		x = ToGraphics(dc, rc.x, rc.width, value);

		textX = x - labelExtent.GetWidth() / 2;
		lineX1 = lineX2 = x;

		switch (GetLocation()) {
		case AXIS_TOP:
			lineY1 = rc.y + rc.height - labelLineSize;
			lineY2 = rc.y + rc.height;

			textY = rc.y + rc.height - labelLineSize - labelExtent.GetHeight() - labelGap;
			break;
		case AXIS_BOTTOM:
			lineY1 = rc.y;
			lineY2 = rc.y + labelLineSize;

			textY = rc.y + labelLineSize + labelGap;
			break;
		default:
			return ; // BUG
		}
	}

	dc.DrawLine(lineX1, lineY1, lineX2, lineY2);
	dc.DrawText(label, textX, textY);
}

void LabelAxis::DrawLabels(wxDC &dc, wxRect rc)
{
	if (!HasLabels())
		return ;

	// setup dc objects for tick labels and lines
	dc.SetFont(m_labelFont);
	dc.SetPen(m_labelPen);
	dc.SetTextForeground(m_labelColour);

	wxString label;
	for (int nStep = 0; ; nStep++) {
		if (IsEnd(nStep))
			break;

		label = wxEmptyString;
		GetLabel(nStep, label);

		double value = GetValue(nStep);
		DrawLabel(dc, rc, label, value);
	}
}

void LabelAxis::DrawBorderLine(wxDC &dc, wxRect rc)
{
	wxCoord x1, y1;
	wxCoord x2, y2;

	switch (GetLocation()) {
		case AXIS_LEFT:
			x1 = x2 = rc.x + rc.width;
			y1 = rc.y;
			y2 = rc.y + rc.height;
			break;
		case AXIS_RIGHT:
			x1 = x2 = rc.x;
			y1 = rc.y;
			y2 = rc.y + rc.height;
			break;
		case AXIS_TOP:
			x1 = rc.x;
			x2 = rc.x + rc.width;
			y1 = y2 = rc.y + rc.height;
			break;
		case AXIS_BOTTOM:
			x1 = rc.x;
			x2 = rc.x + rc.width;
			y1 = y2 = rc.y;
			break;
		default:
			return ; // BUG
	}

	dc.DrawLine(x1, y1, x2, y2);
}

wxCoord LabelAxis::ToGraphics(wxDC &dc, int minG, int range, double value)
{
	minG += m_marginMin;
	range -= (m_marginMin + m_marginMax);
	if (range < 0)
		range = 0;

	return DoToGraphics(dc, minG, range, value);
}

double LabelAxis::ToData(wxDC &dc, int minG, int range, wxCoord g)
{
	minG += m_marginMin;
	range -= (m_marginMin + m_marginMax);
	if (range < 0)
		range = 0;

	return DoToData(dc, minG, range, g);
}

void LabelAxis::DrawGridLines(wxDC &dc, wxRect rc)
{
	if (!HasLabels())
		return ;

	dc.SetPen(m_gridLinesPen);

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
	if (m_title.Length() != 0) {
		wxSize titleExtent = dc.GetTextExtent(m_title);

		dc.SetFont(m_titleFont);
		dc.SetTextForeground(m_titleColour);

		if (IsVertical()) {
			wxCoord y;
			switch (m_titleLocation) {
				case wxTOP:
					y = rc.y + titleExtent.x;
					break;
				case wxCENTER:
					y = (rc.y + rc.height) / 2 + titleExtent.x / 2;
					break;
				case wxBOTTOM:
					y = rc.y + rc.height;
					break;
				default:
					// fallback to center
					y = (rc.y + rc.height) / 2 + titleExtent.x / 2;
			}

			dc.DrawRotatedText(m_title, rc.x, y, 90);
			rc.x += titleExtent.y;
			rc.width -= titleExtent.y;
		}
		else {
			wxCoord x;
			switch (m_titleLocation) {
				case wxLEFT:
					x = rc.x;
					break;
				case wxCENTER:
					x = (rc.x + rc.width) / 2 - titleExtent.x / 2;
					break;
				case wxRIGHT:
					x = rc.x + rc.width - titleExtent.x;
					break;
				default:
					// fallback to center
					x = (rc.x + rc.width) / 2 - titleExtent.x / 2;
			}

			dc.DrawText(m_title, x, rc.y + rc.height - titleExtent.y);
			rc.height -= titleExtent.y;
		}
	}

	DrawLabels(dc, rc);
	DrawBorderLine(dc, rc);
}

bool LabelAxis::HasLabels()
{
	return true;
}
