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

Chart::Chart(Plot *_plot, const wxString &_title)
{
	plot = _plot;
	plot->AddObserver(this);

	title = _title;

	background = new FillAreaBackground(*wxLIGHT_GREY_PEN, *wxLIGHT_GREY_BRUSH);

	titleFont = *wxNORMAL_FONT;
}

Chart::~Chart()
{
	SAFE_REMOVE_OBSERVER(this, plot);
	SAFE_DELETE(background);
}

void Chart::PlotNeedRedraw(Plot *_plot)
{
	if (plot != _plot) {
		return ;
	}

	FireChartChanged();
}

void Chart::Draw(wxDC &dc, wxRect &rc)
{
	background->Draw(dc, rc);

	int topMargin = 5;

	if (title.Length() != 0) {
		dc.SetFont(titleFont);

		wxSize textExtent = dc.GetTextExtent(title);

		wxRect titleRect = rc;
		titleRect.height = textExtent.y + 2;

		DrawTextCenter(dc, titleRect, title);

		topMargin += titleRect.height;
	}

	Margins(rc, 5, topMargin, 5, 5); // TODO temporary!
	plot->Draw(dc, rc);
}
