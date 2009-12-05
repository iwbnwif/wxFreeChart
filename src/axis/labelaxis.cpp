/////////////////////////////////////////////////////////////////////////////
// Name:	labelaxis.cpp
// Purpose: label axis implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/labelaxis.h>
#include <wx/drawutils.h>

IMPLEMENT_CLASS(LabelAxis, Axis)

LabelAxis::LabelAxis(AXIS_LOCATION location)
: Axis(location)
{
	// defaults
	m_labelTextColour = *wxBLACK;
	m_labelTextFont = *wxNORMAL_FONT;//*wxSMALL_FONT;
	m_labelPen = *wxBLACK_PEN;
	m_titleFont = *wxNORMAL_FONT;
	m_titleColour = *wxBLACK;
	m_titleLocation = wxCENTER;

	m_labelLineSize = 5;
	m_labelGap = 2;
	m_verticalLabelText = false;
}

LabelAxis::~LabelAxis()
{
}

wxCoord LabelAxis::GetExtent(wxDC &dc)
{
	wxSize maxLabelExtent = GetLongestLabelExtent(dc);
	wxCoord extent = m_labelLineSize + m_labelGap;

	wxSize titleExtent;

	if (m_title.Length() != 0) {
		dc.SetFont(m_titleFont);
		titleExtent = dc.GetTextExtent(m_title);
	}

	if (IsVertical()) {
		if (m_verticalLabelText) {
			extent += maxLabelExtent.y;
		}
		else {
			extent += maxLabelExtent.x;
		}

		extent += titleExtent.x;
		extent += m_labelPen.GetWidth();
	}
	else {
		if (m_verticalLabelText) {
			extent += maxLabelExtent.x;
		}
		else {
			extent += maxLabelExtent.y;
		}

		extent += titleExtent.y;
		extent += m_labelPen.GetWidth();
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

		lineY1 = lineY2 = y;

		switch (GetLocation()) {
		case AXIS_LEFT:
			lineX1 = rc.x + rc.width - m_labelLineSize;
			lineX2 = rc.x + rc.width;

			if (m_verticalLabelText) {
				textX = lineX1 - labelExtent.y - m_labelGap;
			}
			else {
				textX = lineX1 - labelExtent.x - m_labelGap;
			}
			break;
		case AXIS_RIGHT:
			lineX1 = rc.x;
			lineX2 = rc.x + m_labelLineSize;

			textX = lineX2 + m_labelGap;
			break;
		default:
			return ; // BUG
		}

		if (m_verticalLabelText) {
			textY = y + labelExtent.x / 2;
		}
		else {
			textY = y - labelExtent.y / 2;
		}
	}
	else {
		x = ToGraphics(dc, rc.x, rc.width, value);

		lineX1 = lineX2 = x;

		switch (GetLocation()) {
		case AXIS_TOP:
			lineY1 = rc.y + rc.height - m_labelLineSize;
			lineY2 = rc.y + rc.height;

			if (m_verticalLabelText) {
				textY = lineY1 - m_labelGap;
			}
			else {
				textY = lineY1 - labelExtent.y - m_labelGap;
			}
			break;
		case AXIS_BOTTOM:
			lineY1 = rc.y;
			lineY2 = rc.y + m_labelLineSize;

			if (m_verticalLabelText) {
				textY = lineY2 + m_labelGap + labelExtent.x;
			}
			else {
				textY = lineY2 + m_labelGap;
			}
			break;
		default:
			return ; // BUG
		}

		if (m_verticalLabelText) {
			textX = x - labelExtent.y / 2;
		}
		else {
			textX = x - labelExtent.x / 2;
		}
	}

	dc.DrawLine(lineX1, lineY1, lineX2, lineY2);

	if (m_verticalLabelText) {
		dc.DrawRotatedText(label, textX, textY, 90);
	}
	else {
		dc.DrawText(label, textX, textY);
	}
}

void LabelAxis::DrawLabels(wxDC &dc, wxRect rc)
{
	if (!HasLabels()) {
		return ;
	}

	// setup dc objects for labels and lines
	dc.SetFont(m_labelTextFont);
	dc.SetTextForeground(m_labelTextColour);
	dc.SetPen(m_labelPen);

	wxString label;
	for (int step = 0; !IsEnd(step) ; step++) {
		double value = GetValue(step);
		if (!IsVisible(value)) {
			continue;
		}

		label = wxEmptyString;
		GetLabel(step, label);

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

void LabelAxis::DrawGridLines(wxDC &dc, wxRect rc)
{
	if (!HasLabels()) {
		return ;
	}

	dc.SetPen(m_gridLinesPen);

	for (int nStep = 0; !IsEnd(nStep); nStep++) {
		double value = GetValue(nStep);
		if (!IsVisible(value)) {
			continue;
		}

		if (IsVertical()) {
			wxCoord y = ToGraphics(dc, rc.y, rc.height, value);

			if (y == rc.y || y == (rc.y + rc.height)) {
				continue;
			}

			dc.DrawLine(rc.x, y, rc.x + rc.width, y);
		}
		else {
			wxCoord x = ToGraphics(dc, rc.x, rc.width, value);

			if (x == rc.x || x == (rc.x + rc.width)) {
				continue;
			}

			dc.DrawLine(x, rc.y, x, rc.y + rc.height);
		}
	}
}

void LabelAxis::Draw(wxDC &dc, wxRect rc)
{
	// draw title
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

