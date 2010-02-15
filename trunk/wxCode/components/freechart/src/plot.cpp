/////////////////////////////////////////////////////////////////////////////
// Name:	plot.cpp
// Purpose: plot base class implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2010 Moskvichev Andrey V.
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
	m_textNoDataFont = *wxNORMAL_FONT;
	m_textNoData = wxT("No data");

	m_background = new NoAreaDraw();
}

Plot::~Plot()
{
	wxDELETE(m_background);
}

void Plot::Draw(wxDC &dc, wxRect rc)
{
	m_background->Draw(dc, rc);

	if (HasData()) {
		DrawData(dc, rc);
	}
	else {
		DrawNoDataMessage(dc, rc);
	}
}

void Plot::DrawNoDataMessage(wxDC &dc, wxRect rc)
{
	dc.SetFont(m_textNoDataFont);
	DrawTextCenter(dc, rc, m_textNoData);
}
