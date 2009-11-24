/////////////////////////////////////////////////////////////////////////////
// Name:	chart.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/chart.h>
#include <wx/drawutils.h>

ChartObserver::ChartObserver()
{

}

ChartObserver::~ChartObserver()
{

}

Chart::Chart(Plot *plot, const wxString &title)
{
	// defaults
	wxColour bgColor = wxColour(220, 220, 220);

	m_background = new FillAreaDraw(
			*wxThePenList->FindOrCreatePen(bgColor, 1, wxSOLID),
			*wxTheBrushList->FindOrCreateBrush(bgColor));
	m_titleFont = *wxNORMAL_FONT;

	m_plot = plot;
	m_plot->AddObserver(this);
	m_title = title;

	m_horizScrolledAxis = NULL;
	m_vertScrolledAxis = NULL;
}

Chart::~Chart()
{
	SAFE_REMOVE_OBSERVER(this, m_plot);
	wxDELETE(m_plot);
	wxDELETE(m_background);
}

void Chart::PlotNeedRedraw(Plot *WXUNUSED(plot))
{
	FireChartChanged();
}

void Chart::AxisChanged(Axis *WXUNUSED(axis))
{

}

void Chart::BoundsChanged(Axis *axis)
{
	if (axis == m_horizScrolledAxis || axis == m_vertScrolledAxis) {
		FireChartScrollsChanged();
	}
}

void Chart::SetScrolledAxis(Axis *axis)
{
	if (axis->IsVertical()) {
		if (m_vertScrolledAxis != NULL) {
			m_vertScrolledAxis->RemoveObserver(this);
		}
		m_vertScrolledAxis = axis;
	}
	else {
		if (m_horizScrolledAxis != NULL) {
			m_horizScrolledAxis->RemoveObserver(this);
		}
		m_horizScrolledAxis = axis;
	}

	axis->AddObserver(this);

	FireChartScrollsChanged();
}

Axis *Chart::GetHorizScrolledAxis()
{
	return m_horizScrolledAxis;
}

Axis *Chart::GetVertScrolledAxis()
{
	return m_vertScrolledAxis;
}

wxRect Chart::CalcPlotRect(wxDC &dc, wxRect rc)
{
	int topMargin = 5;
	if (m_title.Length() != 0) {
		dc.SetFont(m_titleFont);

		wxSize textExtent = dc.GetTextExtent(m_title);
		topMargin += textExtent.y + 2;
	}

	Margins(rc, 5, topMargin, 5, 5);
	return rc;
}

void Chart::Draw(wxDC &dc, wxRect &rc)
{
	m_background->Draw(dc, rc);

	int topMargin = 5;
	if (m_title.Length() != 0) {
		dc.SetFont(m_titleFont);

		wxSize textExtent = dc.GetTextExtent(m_title);

		wxRect titleRect = rc;
		titleRect.height = textExtent.y + 2;

		DrawTextCenter(dc, titleRect, m_title);

		topMargin += titleRect.height;
	}

	Margins(rc, 5, topMargin, 5, 5);
	m_plot->Draw(dc, rc);
}
