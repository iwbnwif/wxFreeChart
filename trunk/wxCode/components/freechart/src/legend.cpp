/////////////////////////////////////////////////////////////////////////////
// Name:	legend.cpp
// Purpose: legend drawing implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/legend.h>

const wxCoord Legend::labelsSpacing = 2;

Legend::Legend(int vertPosition, int horizPosition, AreaDraw *background, int symbolTextGap, int margin)
{
	m_vertPosition = vertPosition;
	m_horizPosition = horizPosition;
	m_background = background;
	m_symbolTextGap = symbolTextGap;
	m_margin = margin;
}

Legend::~Legend()
{
	wxDELETE(m_background);
}

void Legend::Draw(wxDC &dc, wxRect rc, DatasetArray &datasets)
{
	dc.SetFont(m_font);

	m_background->Draw(dc, rc);

	wxCoord x = rc.x + m_margin;
	wxCoord y = rc.y;

	for (size_t n = 0; n < datasets.Count(); n++) {
		Dataset *dataset = datasets[n];

		FOREACH_SERIE(serie, dataset) {
			wxString serieName = dataset->GetSerieName(serie);
			wxSize textExtent = dc.GetTextExtent(serieName);

			Renderer *renderer = dataset->GetBaseRenderer();

			Symbol *symbol = renderer->GetSerieSymbol(serie);
			wxColour color = renderer->GetSerieColor(serie);

			wxSize symbolExtent = symbol->GetExtent();
			symbol->Draw(dc, x + symbolExtent.x / 2, y + symbolExtent.y / 2 + textExtent.y / 2, color);

			wxCoord textX = x + symbolExtent.x + m_symbolTextGap;

			dc.DrawText(serieName, textX, y);

			y += textExtent.y + labelsSpacing;
		}
	}
}

wxSize Legend::GetExtent(wxDC &dc, DatasetArray &datasets)
{
	wxSize extent(0, 0);

	dc.SetFont(m_font);

	for (size_t n = 0; n < datasets.Count(); n++) {
		Dataset *dataset = datasets[n];

		FOREACH_SERIE(serie, dataset) {
			wxSize textExtent = dc.GetTextExtent(dataset->GetSerieName(serie));

			Renderer *renderer = dataset->GetBaseRenderer();
			Symbol *symbol = renderer->GetSerieSymbol(serie);

			wxSize symbolExtent = symbol->GetExtent();

			wxCoord width = textExtent.x + symbolExtent.x + m_symbolTextGap + 2 * m_margin;

			extent.y += textExtent.y + labelsSpacing;
			extent.x = wxMax(extent.x, width);
		}
	}
	return extent;
}
