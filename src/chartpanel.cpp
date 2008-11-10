
/////////////////////////////////////////////////////////////////////////////
// Name:	chartpanel.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/chartpanel.h>
#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE(wxChartPanel, wxScrolledWindow)
	EVT_PAINT(wxChartPanel::OnPaint)
	EVT_SIZE(wxChartPanel::OnSize)
END_EVENT_TABLE()

wxChartPanel::wxChartPanel(wxWindow *parent, Chart *_chart, const wxPoint &pos, const wxSize &_size)
: wxScrolledWindow(parent, wxID_ANY, pos, _size)//, wxFULL_REPAINT_ON_RESIZE)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);

	chart = NULL;

	wxSize size = GetSize();
	ResizeBackBitmap(size);

	SetChart(_chart);
}

wxChartPanel::~wxChartPanel()
{
	SAFE_REMOVE_OBSERVER(this, chart);
	SAFE_UNREF(chart);
}

void wxChartPanel::SetChart(Chart *_chart)
{
	SAFE_REPLACE_OBSERVER(this, chart, _chart);
	SAFE_REPLACE_UNREF(chart, _chart);

	RedrawBackBitmap();
	Refresh(false);
}

void wxChartPanel::ChartChanged(Chart *_chart)
{
	if (chart != _chart) {
		// bug
		return ;
	}

	RedrawBackBitmap();
	Refresh(false);
}

void wxChartPanel::OnPaint(wxPaintEvent &ev)
{
	wxPaintDC dc(this);
	const wxRect &rc = GetClientRect();

	if (chart != NULL) {
		dc.DrawBitmap(backBitmap, 0, 0, false);
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
}

void wxChartPanel::RedrawBackBitmap()
{
	if (chart != NULL) {
		wxMemoryDC mdc;
		mdc.SelectObject(backBitmap);

		// TODO using graphics context instead of normal DC
		// allows antialiasing and other features,
		// but i tested it on Linux-wxGTK-2.8.8 and on Windows(tm)-wxWidgets-2.8.8
		// drawing was too long, and resulting chart was incorrect.\
		// If someone knows how to correctly use graphics context, please let me know.
//#if wxUSE_GRAPHICS_CONTEXT
#if 0
		wxGCDC gdc(mdc);
		wxDC &dc = (wxDC&) gdc;
#else
		wxDC &dc = (wxDC&) mdc;
#endif

		const wxRect &rc = GetClientRect();
		chart->Draw(dc, (wxRect&) rc);
	}
}

void wxChartPanel::ResizeBackBitmap(wxSize size)
{
	backBitmap.Create(size.GetWidth(), size.GetHeight());
}
