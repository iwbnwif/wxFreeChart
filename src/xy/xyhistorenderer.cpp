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
#include <wx/art.h>

XYHistoRenderer::XYHistoRenderer(int barWidth, bool vertical)
{
	m_barWidth = barWidth;
	m_vertical = vertical;
	m_serieShift = barWidth + 2; // XXX temporary!
}

XYHistoRenderer::~XYHistoRenderer()
{
}

void XYHistoRenderer::DrawBar(int serie, wxDC &dc, wxRect rcData, wxCoord x, wxCoord y)
{
	wxRect rcBar;

	if (m_vertical) {
		rcBar.x = x - m_barWidth / 2;
		rcBar.y = y;
		rcBar.width = m_barWidth;
		rcBar.height = rcData.height - y + rcData.y;
	}
	else {
		rcBar.x = rcData.x;
		rcBar.y = y - m_barWidth / 2;
		rcBar.width = x - rcData.x;
		rcBar.height = m_barWidth;
	}

	AreaBackground *barArea = GetBarArea(serie);
	barArea->Draw(dc, rcBar);
}

void XYHistoRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset)
{
	FOREACH_SERIE(serie, dataset) {
		FOREACH_DATAITEM(n, serie, dataset) {
			double xVal;
			double yVal;

			if (m_vertical) {
				xVal = dataset->GetX(n, serie);
				yVal = dataset->GetY(n, serie);
			}
			else {
				xVal = dataset->GetY(n, serie);
				yVal = dataset->GetX(n, serie);
			}

			wxCoord x = horizAxis->ToGraphics(dc, rc.x, rc.width, xVal);
			wxCoord y = vertAxis->ToGraphics(dc, rc.y, rc.height, yVal);

			DrawBar(serie, dc, rc, x, y);
		}
	}
}

void XYHistoRenderer::DrawLegendSymbol(wxDC &dc, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1)
{
// TODO
	//dc.SetPen(symbolPen);
	dc.DrawLine(x0, (y0 + y1) / 2, x1, (y0 + y1) / 2);
}

void XYHistoRenderer::SetBarArea(int serie, AreaBackground *barArea)
{
	m_barAreas.SetAreaBackground(serie, barArea);
	FireNeedRedraw();
}

AreaBackground *XYHistoRenderer::GetBarArea(int serie)
{
	return m_barAreas.GetAreaBackground(serie);
}

void XYHistoRenderer::NeedRedraw(DrawObject *WXUNUSED(obj))
{
	FireNeedRedraw();
}
