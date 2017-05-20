/////////////////////////////////////////////////////////////////////////////
// Name:    barplot.cpp
// Purpose: bar plot implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/categoryaxis.h>
#include <wx/axis/dateaxis.h>
#include <wx/axis/numberaxis.h>

#include <wx/plot/barplot.h>

#include <wx/render/barrenderer.h>

BarPlot::BarPlot(BarPlotOrientation orientation)
{
    m_orientation = orientation;
    
    if (orientation == BARPLOT_VERTICAL)
        m_drawGridHorizontal = false;
    else
        m_drawGridVertical = false;

}

BarPlot::~BarPlot()
{
}

bool BarPlot::AcceptAxis(Axis *axis)
{
    if (m_orientation == BARPLOT_VERTICAL && 
            wxDynamicCast(axis, NumberAxis) &&
            dynamic_cast<NumberAxis*>(axis)->IsVertical())
        return true;
        
    if (m_orientation == BARPLOT_VERTICAL && 
            wxDynamicCast(axis, CategoryAxis) &&
            dynamic_cast<CategoryAxis*>(axis)->IsHorizontal())
        return true;

    if (m_orientation == BARPLOT_HORIZONTAL && 
            wxDynamicCast(axis, NumberAxis) &&
            dynamic_cast<NumberAxis*>(axis)->IsHorizontal())
        return true;
        
    if (m_orientation == BARPLOT_HORIZONTAL && 
            wxDynamicCast(axis, CategoryAxis) &&
            dynamic_cast<CategoryAxis*>(axis)->IsVertical())
        return true;
    
    return false;
}

bool BarPlot::AcceptDataset(Dataset *dataset)
{
    return (wxDynamicCast(dataset, UniDataSet) != NULL);
}

void BarPlot::DrawDatasets(wxDC &dc, wxRect rc)
{
    for (size_t nData = 0; nData < GetDatasetCount(); nData++) 
    {
        DataSet *dataset = GetDataset(nData);

        BarRenderer *renderer = wxDynamicCast(dataset->GetBaseRenderer(), BarRenderer);
        wxCHECK_RET(renderer != NULL, wxT("no renderer for data"));

        Axis *vertAxis = GetDatasetVerticalAxis(dataset);
        Axis *horizAxis = GetDatasetHorizontalAxis(dataset);

        wxCHECK_RET(vertAxis != NULL, wxT("no axis for data"));
        wxCHECK_RET(horizAxis != NULL, wxT("no axis for data"));

        renderer->Draw(dc, rc, horizAxis, vertAxis, m_orientation == BARPLOT_VERTICAL, (UniDataSet*)dataset);
    }
}

// TODO: This is an almost blanket copy of the AxisPlot implementation. Consider abstracting a chunk into 
// the base class.
void BarPlot::OnMouseMove(wxMouseEvent& event)
{
    /*
    for (size_t set = 0; set < GetDatasetCount(); set++)
    {
        CategoryDataset* dataset = wxDynamicCast(GetDataset(set), CategoryDataset);
        
        if (dataset)
        {
            wxMemoryDC dummy;
            
            // Define a rectangle in graphics coordinate space to search for points.
            wxPoint gmin = event.GetPosition() + wxPoint(-5, 5);
            wxPoint gmax = event.GetPosition() + wxPoint(5, -5);
            
            // Convert the search rectangle to dataset coordinate space.
            wxRealPoint dmin, dmax;
            ToDataCoords(set, dummy, m_rect, gmin.x, gmin.y, &dmin.x, &dmin.y);
            ToDataCoords(set, dummy, m_rect, gmax.x, gmax.y, &dmax.x, &dmax.y);
            
            // Search the dataset (all series) for a point within the search area.
            DataItemLocator item = dataset->SearchNearPoint(dmin, dmax);
            
            // If a point is found then set the tip data.
            if (item.IsValid())
            {
                SetTipData(wxString::Format("Dataset: %zu, Series: %zu, Data: %s, %g", set, item.GetSeries(), 
                                                dataset->GetName(item.GetIndex()), 
                                                dataset->GetY(item.GetIndex(), item.GetSeries())));
                return;
            }
        }
    }
    
    // If no points have been found, clear the tip.
    SetTipData(wxEmptyString);
    */ 
    return;
}