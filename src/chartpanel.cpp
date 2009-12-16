/////////////////////////////////////////////////////////////////////////////
// Name:	chartpanel.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/chartpanel.h>
#include <wx/dcbuffer.h>

#if wxUSE_GRAPHICS_CONTEXT
#include <wx/dcgraph.h>
#endif /* wxUSE_GRAPHICS_CONTEXT */

const int scrollPixelStep = 100;
const int stepMult = 100;

void GetAxisScrollParams(Axis *axis, int &noUnits, int &pos)
{
	double minValue, maxValue;
	axis->GetDataBounds(minValue, maxValue);

	noUnits = RoundHigh(stepMult * (maxValue - minValue - axis->GetWindowWidth())) + 10/*XXX dirty hack*/;
	if (noUnits < 0) {
		noUnits = 0;
	}

	pos = (int) (stepMult * (axis->GetWindowPosition() - minValue));
}

BEGIN_EVENT_TABLE(wxChartPanel, wxScrolledWindow)
	EVT_PAINT(wxChartPanel::OnPaint)
	EVT_SIZE(wxChartPanel::OnSize)
	EVT_SCROLLWIN(wxChartPanel::OnScrollWin)
END_EVENT_TABLE()

wxChartPanel::wxChartPanel(wxWindow *parent, wxWindowID id, Chart *chart, const wxPoint &pos, const wxSize &size)
: wxScrolledWindow(parent, id, pos, size, wxHSCROLL | wxVSCROLL | wxFULL_REPAINT_ON_RESIZE)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	EnableScrolling(false, false);

	m_chart = NULL;
	m_antialias = false;

	ResizeBackBitmap(size);

	SetScrollRate(1, 1);
	SetChart(chart);
}

wxChartPanel::~wxChartPanel()
{
	SAFE_REMOVE_OBSERVER(this, m_chart);
	wxDELETE(m_chart);
}

void wxChartPanel::SetChart(Chart *chart)
{
	SAFE_REPLACE_OBSERVER(this, m_chart, chart);
	wxREPLACE(m_chart, chart);

	RecalcScrollbars();

	RedrawBackBitmap();
	Refresh(false);
}

void wxChartPanel::SetAntialias(bool antialias)
{
	if (m_antialias != antialias) {
#if wxUSE_GRAPHICS_CONTEXT
#else
		wxASSERT_MSG(!antialias, wxT("Cannot enable antialiasing due to missing wxUSE_GRAPHICS_CONTEXT"));
#endif
		m_antialias = antialias;

		RedrawBackBitmap();
		Refresh(false);
	}
}

wxBitmap wxChartPanel::CopyBackbuffer()
{
	return wxBitmap(m_backBitmap);
}

void wxChartPanel::ChartChanged(Chart *WXUNUSED(chart))
{
	RedrawBackBitmap();
	Refresh(false);
}

void wxChartPanel::ChartScrollsChanged(Chart *WXUNUSED(chart))
{
	RecalcScrollbars();

	RedrawBackBitmap();
	Refresh(false);
}

void wxChartPanel::RecalcScrollbars()
{
	if (m_chart == NULL) {
		SetScrollbars(1, 1, 0, 0, 0, 0, true);
		return ;
	}

	Axis *horizAxis = m_chart->GetHorizScrolledAxis();
	Axis *vertAxis = m_chart->GetVertScrolledAxis();

	int noUnitsX = 0;
	int noUnitsY = 0;
	int xPos = 0;
	int yPos = 0;

	if (horizAxis != NULL) {
		GetAxisScrollParams(horizAxis, noUnitsX, xPos);
	}

	if (vertAxis != NULL) {
		GetAxisScrollParams(vertAxis, noUnitsY, yPos);
	}

	SetScrollbars(scrollPixelStep, scrollPixelStep, noUnitsX, noUnitsY, xPos, yPos, true);
}

void wxChartPanel::OnPaint(wxPaintEvent &WXUNUSED(ev))
{
	wxPaintDC dc(this);
	const wxRect &rc = GetClientRect();


	if (m_chart != NULL) {
		dc.DrawBitmap(m_backBitmap, 0, 0, false);
	}
	else {
		dc.SetBrush(*wxLIGHT_GREY_BRUSH);
		dc.SetPen(*wxLIGHT_GREY_PEN);
		dc.DrawRectangle(rc);
	}
}

void wxChartPanel::OnSize(wxSizeEvent &ev)
{
	const wxSize size = ev.GetSize();
	ResizeBackBitmap(size);

	RedrawBackBitmap();
	Refresh();
}

void wxChartPanel::OnScrollWin(wxScrollWinEvent &ev)
{
	if (m_chart == NULL) {
		return ;
	}

	Axis *axis = NULL;

	switch (ev.GetOrientation()) {
	case wxHORIZONTAL:
		axis = m_chart->GetHorizScrolledAxis();
		break;
	case wxVERTICAL:
		axis = m_chart->GetVertScrolledAxis();
		break;
	default: // BUG
		return ;
	}

	if (axis != NULL) {
		double winPos = (double) ev.GetPosition() / (double) stepMult;
		double minValue, maxValue;

		axis->GetDataBounds(minValue, maxValue);
		winPos += minValue;

		axis->SetWindowPosition(winPos);
	}
	ev.Skip();
}

void wxChartPanel::ScrollAxis(Axis *axis, int d)
{
	double delta = (double) d / (double) stepMult;
	double minValue, maxValue;

	axis->GetDataBounds(minValue, maxValue);

	double winPos = axis->GetWindowPosition();
	winPos += minValue + delta;

	axis->SetWindowPosition(winPos);
}

void wxChartPanel::RedrawBackBitmap()
{
	if (m_chart != NULL) {
		wxMemoryDC mdc;
		mdc.SelectObject(m_backBitmap);

		const wxRect &rc = GetClientRect();

		// Using graphics context instead of normal DC
		// allows antialiasing and other features,
		// i tested it on Linux-wxGTK-2.8.8 and on Windows(tm)-wxWidgets-2.8.8
		// there is bug with wxSHORT_DASH pen style, it drawing hungs,
		// when wxGCDC used
#if wxUSE_GRAPHICS_CONTEXT
		if (m_antialias) {
			wxGCDC gdc(mdc);
			m_chart->Draw((wxDC&) gdc, (wxRect&) rc);
		}
		else {
			m_chart->Draw(mdc, (wxRect&) rc);
		}
#else
		m_chart->Draw(mdc, (wxRect&) rc);
#endif
	}
}

void wxChartPanel::ResizeBackBitmap(wxSize size)
{
	m_backBitmap.Create(size.GetWidth(), size.GetHeight());
}
