/////////////////////////////////////////////////////////////////////////////
// Name:	xyarearenderer.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xyarearenderer.h>

IMPLEMENT_CLASS(XYAreaRenderer, XYRenderer)

XYAreaRenderer::XYAreaRenderer()
{
	m_outlinePen = *wxBLACK_PEN;
	m_areaBrush = *wxGREY_BRUSH;
}

XYAreaRenderer::~XYAreaRenderer()
{
}

void XYAreaRenderer::Draw(wxDC &dc, wxRect rcData, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1)
{
	wxPoint pts[4];

	if (x0 > x1) {
		wxCoord t = x1;
		x1 = x0;
		x0 = t;

		t = y1;
		y1 = y0;
		y0 = t;
	}

	pts[0] = wxPoint(x0, rcData.y + rcData.height);
	pts[1] = wxPoint(x0, y0);
	pts[2] = wxPoint(x1, y1);
	pts[3] = wxPoint(x1, rcData.y + rcData.height);

	dc.SetPen(noPen);
	dc.SetBrush(m_areaBrush);
	dc.DrawPolygon(4, pts);

	dc.SetPen(m_outlinePen);
	//dc.DrawLine(pts[0], pts[1]);
	dc.DrawLine(pts[1], pts[2]);
	//dc.DrawLine(pts[3], pts[3]);
}

void XYAreaRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset)
{
	for (int serie = 0; serie < dataset->GetSerieCount(); serie++) {
		for (int n = 0; n < dataset->GetCount(serie) - 1; n++) {
			wxCoord x0 = horizAxis->ToGraphics(dc, rc.x, rc.width, dataset->GetX(n, serie));
			wxCoord y0 = vertAxis->ToGraphics(dc, rc.y, rc.height, dataset->GetY(n, serie));

			wxCoord x1 = horizAxis->ToGraphics(dc, rc.x, rc.width, dataset->GetX(n + 1, serie));
			wxCoord y1 = vertAxis->ToGraphics(dc, rc.y, rc.height, dataset->GetY(n + 1, serie));

			Draw(dc, rc, x0, y0, x1, y1);
		}
	}
}
