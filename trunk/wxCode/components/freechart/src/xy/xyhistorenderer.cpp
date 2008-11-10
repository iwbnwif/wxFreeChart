
/////////////////////////////////////////////////////////////////////////////
// Name:	xyhistorenderer.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xyhistorenderer.h>

XYHistoRenderer::XYHistoRenderer(int _barWidth, bool _vertical)
{
	barWidth = _barWidth;
	vertical = _vertical;
	serieShift = barWidth + 2; // XXX temporary!

	barArea = new FillAreaBackground(*wxBLACK_PEN, *wxRED_BRUSH);
}

XYHistoRenderer::~XYHistoRenderer()
{
	SAFE_DELETE(barArea);
}

void XYHistoRenderer::DrawBar(wxDC &dc, wxRect rcData, wxCoord x, wxCoord y)
{
	wxRect rcBar;

	if (vertical) {
		rcBar.x = x - barWidth / 2;
		rcBar.y = y;
		rcBar.width = barWidth;
		rcBar.height = rcData.height - y + rcData.y;
	}
	else {
		rcBar.x = rcData.x;
		rcBar.y = y - barWidth / 2;
		rcBar.width = x - rcData.x;
		rcBar.height = barWidth;
	}

	barArea->Draw(dc, rcBar);
}

void XYHistoRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset)
{
	const int serieCount = dataset->GetSerieCount();

	wxCoord xShift = 0;
	wxCoord yShift = 0;

	wxCoord c0 = (serieShift - 1) * serieCount / 2 - barWidth / 2;
	if (vertical) {
		xShift -= c0;
	}
	else {
		yShift -= c0;
	}

	PrepareDC(dc);
	for (int serie = 0; serie < serieCount; serie++) {
		for (int n = 0; n < dataset->GetCount(serie); n++) {
			double xVal;
			double yVal;

			if (vertical) {
				xVal = dataset->GetX(n, serie);
				yVal = dataset->GetY(n, serie);
			}
			else {
				xVal = dataset->GetY(n, serie);
				yVal = dataset->GetX(n, serie);
			}

			wxCoord x = horizAxis->ToGraphics(dc, rc.x, rc.width, xVal);
			wxCoord y = vertAxis->ToGraphics(dc, rc.y, rc.height, yVal);

			x += xShift;
			y += yShift;

			DrawBar(dc, rc, x, y);
		}

		if (vertical) {
			xShift += serieShift;
		}
		else {
			yShift += serieShift;
		}
	}
}

void XYHistoRenderer::Draw(wxDC &dc, wxRect rcData, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1)
{
}

void XYHistoRenderer::DrawLegendSymbol(wxDC &dc, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1)
{
// TODO
	//dc.SetPen(symbolPen);
	dc.DrawLine(x0, (y0 + y1) / 2, x1, (y0 + y1) / 2);
}
