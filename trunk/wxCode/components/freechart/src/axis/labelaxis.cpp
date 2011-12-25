/////////////////////////////////////////////////////////////////////////////
// Name:	labelaxis.cpp
// Purpose: label axis implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2010 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/labelaxis.h>
#include <wx/drawutils.h>

IMPLEMENT_CLASS(LabelAxis, Axis)

class DefaultLabelColourer : public LabelColourer
{
public:
	DefaultLabelColourer();
	virtual ~DefaultLabelColourer();

	virtual wxColor GetColour(int step);

private:
	wxColor m_oddColour;
	wxColor m_evenColour;
};

DefaultLabelColourer::DefaultLabelColourer()
{
	m_oddColour = *wxLIGHT_GREY;
	m_evenColour = wxColor(100, 100, 100);
}

DefaultLabelColourer::~DefaultLabelColourer()
{
}

wxColor DefaultLabelColourer::GetColour(int step)
{
	return (step % 2) ? m_oddColour : m_evenColour;
}

LabelAxis::LabelAxis(AXIS_LOCATION location)
: Axis(location)
{
	// defaults
	m_labelLineSize = 5;
	m_labelGap = 2;

	m_labelTextFont = *wxNORMAL_FONT;
	m_labelTextColour = *wxBLACK;
	m_labelPen = *wxBLACK_PEN;
	m_verticalLabelText = false;
	m_majorLabelStep = 1;

	m_title = wxEmptyString;
	m_titleFont = *wxNORMAL_FONT;
	m_titleColour = *wxBLACK;
	m_titleLocation = wxCENTER;

	m_visible = true;
	m_blankLabels = 0;

	m_labelColourer = new DefaultLabelColourer();
}

LabelAxis::~LabelAxis()
{
	wxDELETE(m_labelColourer);
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

		extent += titleExtent.y; // Alan fix
		// orig: extent += titleExtent.x;
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

void LabelAxis::DrawLabel(wxDC &dc, wxRect rc, const wxString &label, double value, bool isMajorLabel)
{
	wxSize labelExtent = dc.GetTextExtent(label);

	wxCoord x, y;
	wxCoord textX, textY;
	wxCoord lineX1, lineY1;
	wxCoord lineX2, lineY2;
	int labelLineSize = isMajorLabel ? m_labelLineSize : m_labelLineSize / 2;

	if (IsVertical()) {
		y = ToGraphics(dc, rc.y, rc.height, value);

		lineY1 = lineY2 = y;

		switch (GetLocation()) {
		case AXIS_LEFT:
			lineX1 = rc.x + rc.width - labelLineSize;
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
			lineX2 = rc.x + labelLineSize;

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
			lineY1 = rc.y + rc.height - labelLineSize;
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
			lineY2 = rc.y + labelLineSize;

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

	if (isMajorLabel) {
		if (m_verticalLabelText) {
			dc.DrawRotatedText(label, textX, textY, 90);
		}
		else {
			dc.DrawText(label, textX, textY);
		}
	}
}

void LabelAxis::SetLabelSkip(int blankLabels)
{
	m_blankLabels = blankLabels;
}

int LabelAxis::GetLabelSkip()
{
	return m_blankLabels;
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
		if (step % (m_blankLabels + 1) == 0)
			GetLabel(step, label);

		DrawLabel(dc, rc, label, value, !(step % m_majorLabelStep));
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

	for (int nStep = 0; !IsEnd(nStep); nStep++) {
		m_gridLinesPen.SetColour(m_labelColourer->GetColour(nStep));
		dc.SetPen(m_gridLinesPen);

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

void LabelAxis::SetAxisVisible(bool bVisible)
{
	m_visible = bVisible;
	FireAxisChanged();
}

void LabelAxis::Draw(wxDC &dc, wxRect rc)
{
	if (!m_visible)
		return;
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

			// Alan add
			if (GetLocation() == AXIS_LEFT)
			{
				dc.DrawRotatedText(m_title, rc.x, y, 90);
				rc.x += titleExtent.y;
				rc.width -= titleExtent.y;
			}
			// End Alan add
			// orig : dc.DrawRotatedText(m_title, rc.x, y, 90);
			// orig : rc.x += titleExtent.y;
			// orig : rc.width -= titleExtent.y;
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
	// Alan add
	int y;
	if (m_title.Length() != 0)
	{
		wxSize titleExtent = dc.GetTextExtent(m_title);
		wxSize maxLabelExtent = GetLongestLabelExtent(dc);
		if (GetLocation() == AXIS_RIGHT)
		{
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
			dc.DrawRotatedText(m_title, rc.x + maxLabelExtent.x + m_labelGap + m_labelLineSize + 1, y, 90);
		}
	}
	// End Alan add
}

bool LabelAxis::HasLabels()
{
	return true;
}

