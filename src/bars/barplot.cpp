/////////////////////////////////////////////////////////////////////////////
// Name:    barplot.cpp
// Purpose: bar plot implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/bars/barplot.h>

#include <wx/axis/categoryaxis.h>
#include <wx/axis/numberaxis.h>
#include <wx/axis/dateaxis.h>

BarPlot::BarPlot()
{
}

BarPlot::~BarPlot()
{
}

bool BarPlot::AcceptAxis(Axis *axis)
{
    return (wxDynamicCast(axis, NumberAxis) != NULL) ||
            (wxDynamicCast(axis, CategoryAxis) != NULL);
}

bool BarPlot::AcceptDataset(Dataset *dataset)
{
    return (wxDynamicCast(dataset, CategoryDataset) != NULL);
}

void BarPlot::DrawDatasets(wxDC &dc, wxRect rc)
{
    for (size_t nData = 0; nData < GetDatasetCount(); nData++) {
        CategoryDataset *dataset = (CategoryDataset *) GetDataset(nData);
        BarRenderer *renderer = dataset->GetRenderer();
        wxCHECK_RET(renderer != NULL, wxT("no renderer for data"));

        Axis *vertAxis = GetDatasetVerticalAxis(dataset);
        Axis *horizAxis = GetDatasetHorizontalAxis(dataset);

        wxCHECK_RET(vertAxis != NULL, wxT("no axis for data"));
        wxCHECK_RET(horizAxis != NULL, wxT("no axis for data"));

        // Determine if this is a horizontal or a vertical bar plot.
        // TODO: Should this be done here? Maybe when the axis are added.
        bool verticalBars;
        if (wxDynamicCast(horizAxis, CategoryAxis) != NULL ||
                wxDynamicCast(horizAxis, DateAxis) != NULL) {
            verticalBars = true;
        }
        else if (wxDynamicCast(vertAxis, CategoryAxis) != NULL ||
                wxDynamicCast(vertAxis, DateAxis) != NULL) {
            verticalBars = false;
        }
        else {
            // wrong plot configuration, TODO be handled not here
            return ;
        }
        
        // Do not draw gridlines in the same direction as the bars.
        // Would be better when the grid direction is determined so this can be overridden if desired.
        m_drawGridHorizontal = !verticalBars;
        m_drawGridVertical = verticalBars;

        renderer->Draw(dc, rc, horizAxis, vertAxis, verticalBars, dataset);
    }
}

// TODO: This is an almost blanket copy of the AxisPlot implementation. Consider abstracting a chunk into 
// the base class.
void BarPlot::OnMouseMove(wxMouseEvent& event)
{
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
    return;
}