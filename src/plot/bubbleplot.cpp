/////////////////////////////////////////////////////////////////////////////
// Name:    bubbleplot.cpp
// Purpose: bubble plot implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/plot/bubbleplot.h>
#include <wx/render/xyzrenderer.h>

BubblePlot::BubblePlot()
{
}

BubblePlot::~BubblePlot()
{
}

bool BubblePlot::AcceptAxis(Axis *WXUNUSED(axis))
{
    // TODO FIXIT: accepts all axes. 
    return true;
}

bool BubblePlot::AcceptDataset(Dataset *dataset)
{
    return (wxDynamicCast(dataset, NaryDataSet) != NULL);
}

void BubblePlot::DrawDatasets(wxDC &dc, wxRect rc)
{
    for (size_t nData = 0; nData < GetDatasetCount(); nData++) 
    {
        NaryDataSet* dataset = wxDynamicCast(GetDataset(nData), NaryDataSet);
        wxASSERT(dataset);
    
        XYZRenderer* renderer = wxDynamicCast(dataset->GetRenderer(), XYZRenderer);
        wxASSERT(renderer);

        Axis* vertAxis = GetDatasetVerticalAxis(dataset);
        Axis* horizAxis = GetDatasetHorizontalAxis(dataset);
        wxASSERT(vertAxis && horizAxis);

        renderer->Draw(dc, rc, horizAxis, vertAxis, dataset);
    }
}
