/////////////////////////////////////////////////////////////////////////////
// Name:	chart.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
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
	m_background = new FillAreaBackground(*wxLIGHT_GREY_PEN, *wxLIGHT_GREY_BRUSH);
	m_titleFont = *wxNORMAL_FONT;

	m_plot = plot;
	m_plot->AddObserver(this);
	m_title = title;
}

Chart::~Chart()
{
	SAFE_REMOVE_OBSERVER(this, m_plot);
	SAFE_DELETE(m_background);
}

void Chart::PlotNeedRedraw(Plot *WXUNUSED(plot))
{
	FireChartChanged();
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
