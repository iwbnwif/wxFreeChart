
/////////////////////////////////////////////////////////////////////////////
// Name:	plot.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/plot.h>
#include <wx/drawutils.h>

PlotObserver::PlotObserver()
{
}

PlotObserver::~PlotObserver()
{
}


Plot::Plot()
{
	textNoDataFont = *wxNORMAL_FONT;
	textNoData = wxT("No data");

	background = new NoAreaBackground();
}

Plot::~Plot()
{
	SAFE_DELETE(background);
}

void Plot::Draw(wxDC &dc, wxRect rc)
{
	background->Draw(dc, rc);

	if (HasData()) {
		DrawData(dc, rc);
	}
	else {
		DrawNoDataMessage(dc, rc);
	}
}

void Plot::DrawNoDataMessage(wxDC &dc, wxRect rc)
{
	dc.SetFont(textNoDataFont);

	DrawTextCenter(dc, rc, textNoData);
}
