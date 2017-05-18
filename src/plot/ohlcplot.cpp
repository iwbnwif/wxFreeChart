/////////////////////////////////////////////////////////////////////////////
// Name:    ohlcplot.cpp
// Purpose: OHLC plot implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////


#include <wx/axis/dateaxis.h>
#include <wx/axis/numberaxis.h>

#include <wx/plot/ohlcplot.h>

#include <wx/render/ohlcrenderer.h>

OHLCPlot::OHLCPlot()
{
}

OHLCPlot::~OHLCPlot()
{
}

bool OHLCPlot::AcceptAxis(Axis *axis)
{
    return axis->IsVertical() ?
                    wxDynamicCast(axis, NumberAxis) != NULL :
                    wxDynamicCast(axis, DateAxis) != NULL;
}

bool OHLCPlot::AcceptDataset(Dataset *dataset)
{
    return wxDynamicCast(dataset, BiDataSet) != NULL;
}

void OHLCPlot::DrawDatasets(wxDC &dc, wxRect rc)
{
    for (size_t nData = 0; nData < GetDatasetCount(); nData++) 
    {
        BiDataSet* dataset = wxDynamicCast(GetDataset(nData), BiDataSet);
        wxASSERT(dataset);

        DrawOHLCData(dc, rc, dataset);
   }
}

void OHLCPlot::DrawOHLCData(wxDC &dc, wxRect rc, BiDataSet* dataset)
{
    OHLCRenderer* renderer = wxDynamicCast(dataset->GetRenderer(), OHLCRenderer);
    wxASSERT_MSG(renderer != NULL, "No renderer for data");

    Axis *vAxis = GetDatasetVerticalAxis(dataset);
    wxASSERT_MSG(vAxis != NULL, wxT("No vertical axis for data"));

    Axis *hAxis = GetDatasetHorizontalAxis(dataset);
    wxASSERT_MSG(hAxis != NULL, wxT("No horizontal axis for data"));

    // draw OHLC items
    for (size_t n = 0; n < dataset->GetCount(0); n++) 
    {
        const OHLCItem& item = dataset->GetPointData(0, n, 1).As<OHLCItem>();
        wxCoord open = vAxis->ToGraphics(dc, rc.y, rc.height, item.open);
        wxCoord high = vAxis->ToGraphics(dc, rc.y, rc.height, item.high);
        wxCoord low = vAxis->ToGraphics(dc, rc.y, rc.height, item.low);
        wxCoord close = vAxis->ToGraphics(dc, rc.y, rc.height, item.close);

        const wxDateTime& time = dataset->GetPointData(0, n, 0).As<wxDateTime>();
        wxCoord x = hAxis->ToGraphics(dc, rc.x, rc.width, time.GetTicks());

        renderer->DrawItem(dc, x, open, high, low, close);
    }
}
