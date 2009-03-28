/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcplot.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/ohlc/ohlcplot.h>

OHLCPlot::OHLCPlot()
{
}

OHLCPlot::~OHLCPlot()
{
}

bool OHLCPlot::AcceptAxis(Axis *axis)
{
	if (axis->IsVertical()) {
		return (wxDynamicCast(axis, NumberAxis) != NULL);
	}
	else {
		return (wxDynamicCast(axis, DateAxis) != NULL);
	}
}

bool OHLCPlot::AcceptDataset(Dataset *dataset)
{
	return (wxDynamicCast(dataset, OHLCDataset) != NULL);
}

void OHLCPlot::DrawDatasets(wxDC &dc, wxRect rc)
{
	for (int nData = 0; nData < GetDatasetCount(); nData++) {
		OHLCDataset *dataset = (OHLCDataset *) GetDataset(nData);
		OHLCRenderer *renderer = dataset->GetRenderer();
		wxCHECK_RET(renderer != NULL, wxT("no renderer for data"));

		Axis *vertAxis = GetDatasetVerticalAxis(dataset);
		Axis *horizAxis = GetDatasetHorizontalAxis(dataset);

		wxCHECK_RET(vertAxis != NULL, wxT("no axis for data"));
		wxCHECK_RET(horizAxis != NULL, wxT("no axis for data"));

		for (int n = 0; n < dataset->GetCount(0); n++) {
			OHLCItem *item = dataset->GetItem(n);

			wxCoord open = vertAxis->ToGraphics(dc, rc.y, rc.height, item->open);
			wxCoord high = vertAxis->ToGraphics(dc, rc.y, rc.height, item->high);
			wxCoord low = vertAxis->ToGraphics(dc, rc.y, rc.height, item->low);
			wxCoord close = vertAxis->ToGraphics(dc, rc.y, rc.height, item->close);

			wxCoord x = horizAxis->ToGraphics(dc, rc.x, rc.width, n);//item->date);

			renderer->DrawItem(dc, x, open, high, low, close);
		}
	}
}
