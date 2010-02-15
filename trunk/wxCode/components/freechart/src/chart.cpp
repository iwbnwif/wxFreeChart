/////////////////////////////////////////////////////////////////////////////
// Name:	chart.cpp
// Purpose: chart implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2010 Moskvichev Andrey V.
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

	m_margin = 5;

	m_plot = plot;
	m_plot->AddObserver(this);
	m_title = title;

	m_horizScrolledAxis = NULL;
	m_vertScrolledAxis = NULL;
}

Chart::~Chart()
{
	SAFE_REMOVE_OBSERVER(this, m_horizScrolledAxis);
	SAFE_REMOVE_OBSERVER(this, m_vertScrolledAxis);

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
	// do nothing
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
	int topMargin = m_margin;
	if (m_title.Length() != 0) {
		dc.SetFont(m_titleFont);

		wxSize textExtent = dc.GetTextExtent(m_title);
		topMargin += textExtent.y + 2;
	}

	Margins(rc, m_margin, topMargin, m_margin, m_margin);
	return rc;
}

void Chart::Draw(wxDC &dc, wxRect &rc)
{
	// draw chart background
	m_background->Draw(dc, rc);

	int topMargin = m_margin;
	if (m_title.Length() != 0) {
		dc.SetFont(m_titleFont);

		wxSize textExtent = dc.GetTextExtent(m_title);

		wxRect titleRect = rc;
		titleRect.height = textExtent.y + 2;

		DrawTextCenter(dc, titleRect, m_title);

		topMargin += titleRect.height;
	}

	Margins(rc, m_margin, topMargin, m_margin, m_margin);
	m_plot->Draw(dc, rc);
}
