
/////////////////////////////////////////////////////////////////////////////
// Name:	xylinerenderer.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xylinerenderer.h>

XYLineRenderer::XYLineRenderer(bool _drawSymbols, int _defaultWidth, int _defaultStyle)
: drawSymbols(_drawSymbols), defaultWidth(_defaultWidth), defaultStyle(_defaultStyle)
{
}

XYLineRenderer::~XYLineRenderer()
{
}

void XYLineRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset)
{
	for (int serie = 0; serie < dataset->GetSerieCount(); serie++) {
		for (int n = 0; n < dataset->GetCount(serie) - 1; n++) {
			wxCoord x0 = horizAxis->ToGraphics(dc, rc.x, rc.width, dataset->GetX(n, serie));
			wxCoord y0 = vertAxis->ToGraphics(dc, rc.y, rc.height, dataset->GetY(n, serie));

			wxCoord x1 = horizAxis->ToGraphics(dc, rc.x, rc.width, dataset->GetX(n + 1, serie));
			wxCoord y1 = vertAxis->ToGraphics(dc, rc.y, rc.height, dataset->GetY(n + 1, serie));

			DrawSegment(dc, serie, x0, y0, x1, y1);
		}
	}
}


void XYLineRenderer::DrawSegment(wxDC &dc, int serie, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1)
{

	wxPen *pen = GetSeriePen(serie);
	dc.SetPen(*pen);
	dc.DrawLine(x0, y0, x1, y1);

	if (drawSymbols) {
		Symbol *symbol = GetSerieSymbol(serie);

		symbol->SetColor(GetSerieColor(serie));
		symbol->Draw(dc, x0, y0);
		symbol->Draw(dc, x1, y1);
	}
}

void XYLineRenderer::SetSeriePen(int serie, wxPen *pen)
{
	seriePens[serie] = *pen;
	FireNeedRedraw();
}

void XYLineRenderer::SetSerieSymbol(int serie, Symbol *symbol)
{
	serieSymbols[serie] = symbol;
	FireNeedRedraw();
}

wxColour XYLineRenderer::GetSerieColor(int serie)
{
	if (seriePens.find(serie) == seriePens.end()) {
		return GetDefaultColour(serie);
	}
	return seriePens[serie].GetColour();
}

wxPen *XYLineRenderer::GetSeriePen(int serie)
{
	if (seriePens.find(serie) == seriePens.end()) {
		return wxThePenList->FindOrCreatePen(GetDefaultColour(serie), defaultWidth, defaultStyle);
	}
	return &seriePens[serie];
}

Symbol *XYLineRenderer::GetSerieSymbol(int serie)
{
	if (serieSymbols.find(serie) == serieSymbols.end()) {
		return GetDefaultSymbol(serie);
	}
	return serieSymbols[serie];
}
