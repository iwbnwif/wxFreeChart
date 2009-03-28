/////////////////////////////////////////////////////////////////////////////
// Name:	ganttrenderer.cpp
// Purpose: gantt renderer implementation
// Author:	Moskvichev Andrey V.
// Created:	2009/03/23
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2009/03/23 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/gantt/ganttrenderer.h>

IMPLEMENT_CLASS(GanttRenderer, Renderer);

GanttRenderer::GanttRenderer(int barWidth, int serieGap)
{
	m_barWidth = barWidth;
	m_serieGap = serieGap;
}

GanttRenderer::~GanttRenderer()
{
}

void GanttRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, GanttDataset *dataset)
{
	const int serieCount = dataset->GetSerieCount();

//	wxCoord x = rc.x;

	FOREACH_SERIE(serie, dataset) {
		int shift;

		if (serieCount > 1) {
			shift = serie * (m_barWidth + m_serieGap) - (m_serieGap * (serieCount - 1) + m_barWidth);
		}
		else {
			shift = -m_barWidth / 2;
		}

		FOREACH_DATAITEM(n, serie, dataset) {

		}
	}
}
