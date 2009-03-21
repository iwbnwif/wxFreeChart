/////////////////////////////////////////////////////////////////////////////
// Name:	xylinerenderer.cpp
// Purpose: XY line renderer implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xylinerenderer.h>

XYLineRenderer::XYLineRenderer(bool drawSymbols, bool drawLines, int defaultPenWidth, int defaultPenStyle)
{
	m_drawSymbols = drawSymbols;
	m_drawLines = drawLines;
	m_defaultPenWidth = defaultPenWidth;
	m_defaultPenStyle = defaultPenStyle;
}

XYLineRenderer::~XYLineRenderer()
{
}

void XYLineRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset)
{
	FOREACH_SERIE(serie, dataset) {
		for (int n = 0; n < dataset->GetCount(serie) - 1; n++) {
			wxCoord x0, y0;
			wxCoord x1, y1;

			TranslateCoords(x0, y0, dc, rc, horizAxis, vertAxis, dataset->GetX(n, serie), dataset->GetY(n, serie));
			TranslateCoords(x1, y1, dc, rc, horizAxis, vertAxis, dataset->GetX(n + 1, serie), dataset->GetY(n + 1, serie));

			DrawSegment(dc, serie, x0, y0, x1, y1);
		}
	}
}

void XYLineRenderer::DrawSegment(wxDC &dc, int serie, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1)
{
	if (m_drawLines) {
		wxPen *pen = GetSeriePen(serie);
		dc.SetPen(*pen);
		dc.DrawLine(x0, y0, x1, y1);
	}

	if (m_drawSymbols) {
		Symbol *symbol = GetSerieSymbol(serie);

		symbol->SetColor(GetSerieColor(serie));
		symbol->Draw(dc, x0, y0);
		symbol->Draw(dc, x1, y1);
	}
}

void XYLineRenderer::SetSeriePen(int serie, wxPen *pen)
{
	m_seriePens[serie] = *pen;
	FireNeedRedraw();
}

void XYLineRenderer::SetSerieColor(int serie, wxColour *color)
{
	SetSeriePen(serie, wxThePenList->FindOrCreatePen(*color, 1, wxSOLID));
}

wxColour XYLineRenderer::GetSerieColor(int serie)
{
	if (m_seriePens.find(serie) == m_seriePens.end()) {
		return GetDefaultColour(serie);
	}
	return m_seriePens[serie].GetColour();
}

wxPen *XYLineRenderer::GetSeriePen(int serie)
{
	if (m_seriePens.find(serie) == m_seriePens.end()) {
		return wxThePenList->FindOrCreatePen(GetDefaultColour(serie), m_defaultPenWidth, m_defaultPenStyle);
	}
	return &m_seriePens[serie];
}

