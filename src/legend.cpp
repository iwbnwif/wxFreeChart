/////////////////////////////////////////////////////////////////////////////
// Name:	legend.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/legend.h>

const int symbolTextGap = 2;
const int margin = 2;

Legend::Legend(int vertPosition, int horizPosition, AreaDraw *background)
{
	m_vertPosition = vertPosition;
	m_horizPosition = horizPosition;
	m_background = background;
}

Legend::~Legend()
{
	SAFE_DELETE(m_background);
}

void Legend::Draw(wxDC &dc, wxRect rc, Array<Dataset, 1> &datasets)
{
	dc.SetFont(m_font);

	m_background->Draw(dc, rc);

	wxCoord x = rc.x + margin;
	wxCoord y = rc.y;

	for (int n = 0; n < datasets.GetSize(); n++) {
		Dataset *dataset = datasets[n];

		for (int nSerie = 0; nSerie < dataset->GetSerieCount(); nSerie++) {
			wxString serieName = dataset->GetSerieName(nSerie);
			wxSize textExtent = dc.GetTextExtent(serieName);

			Renderer *renderer = dataset->GetBaseRenderer();
			Symbol *symbol = renderer->GetSerieSymbol(nSerie);

			wxSize symbolExtent = symbol->GetExtent();
			symbol->Draw(dc, x + symbolExtent.x / 2, y + symbolExtent.y / 2 + textExtent.y / 2);

			wxCoord textX = x + symbolExtent.x + symbolTextGap;

			dc.DrawText(serieName, textX, y);

			y += textExtent.y + labelsSpacing;
		}
	}
}

wxSize Legend::GetExtent(wxDC &dc, Array<Dataset, 1> &datasets)
{
	wxSize extent(0, 0);

	dc.SetFont(m_font);

	for (int n = 0; n < datasets.GetSize(); n++) {
		Dataset *dataset = datasets[n];

		for (int nSerie = 0; nSerie < dataset->GetSerieCount(); nSerie++) {
			wxSize textExtent = dc.GetTextExtent(dataset->GetSerieName(nSerie));

			Renderer *renderer = dataset->GetBaseRenderer();
			Symbol *symbol = renderer->GetSerieSymbol(nSerie);

			wxSize symbolExtent = symbol->GetExtent();

			wxCoord width = textExtent.x + symbolExtent.x + symbolTextGap + 2 * margin;

			extent.y += textExtent.y + labelsSpacing;
			extent.x = MAX(extent.x, width);
		}
	}
	return extent;
}
