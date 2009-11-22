/////////////////////////////////////////////////////////////////////////////
// Name:	xylinerenderer.cpp
// Purpose: XY line renderer implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xylinerenderer.h>

IMPLEMENT_CLASS(XYLineRenderer, XYRenderer)

void TruncHoriz(Axis *axis, double &x, double &y, double x1, double y1)
{
	if (!axis->IsVisible(x)) {
		double p = axis->BoundValue(x);
		y = (y1 - y) * (p - x) / (x1 - x) + y;
		x = p;
	}
}

void TruncVert(Axis *axis, double &x, double &y, double x1, double y1)
{
	if (!axis->IsVisible(x)) {
		double p = axis->BoundValue(x);
		x = (p - y1) * (x1 - x) / (y1 - y) + x;
		y = p;
	}
}

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
			double x0 = dataset->GetX(n, serie);
			double y0 = dataset->GetY(n, serie);
			double x1 = dataset->GetX(n + 1, serie);
			double y1 = dataset->GetY(n + 1, serie);

			// check whether segment is visible
			if (!horizAxis->IntersectsWindow(x0, x1) &&
					!vertAxis->IntersectsWindow(y0, y1)) {
				continue;
			}

			TruncHoriz(horizAxis, x0, y0, x1, y1);
			TruncHoriz(horizAxis, x1, y1, x0, y0);
			TruncVert(vertAxis, x0, y0, x1, y1);
			TruncVert(vertAxis, x1, y1, x0, y0);

			// translate to graphics coordinates.
			wxCoord xg0, yg0;
			wxCoord xg1, yg1;

			xg0 = horizAxis->ToGraphics(dc, rc.x, rc.width, x0);
			yg0 = vertAxis->ToGraphics(dc, rc.y, rc.height, y0);
			xg1 = horizAxis->ToGraphics(dc, rc.x, rc.width, x1);
			yg1 = vertAxis->ToGraphics(dc, rc.y, rc.height, y1);

			DrawSegment(dc, serie, xg0, yg0, xg1, yg1);
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
	SetSeriePen(serie, wxThePenList->FindOrCreatePen(*color, m_defaultPenWidth, m_defaultPenStyle));
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

