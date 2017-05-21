/////////////////////////////////////////////////////////////////////////////
// Name:    axisplot.cpp
// Purpose: axis plot implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////



#include <wx/plot/axisplot.h>
#include <wx/drawutils.h>
#include <wx/arrimpl.cpp>

#if wxUSE_GRAPHICS_CONTEXT
#include <wx/dcgraph.h>
#endif /* wxUSE_GRAPHICS_CONTEXT */


#include <iostream>

WX_DEFINE_EXPORTED_OBJARRAY(DataAxisLinkArray)

#define CHECK_INDEX(name, index, v) do {                                            \
    if (index >= v.Count()) {                                                        \
        wxLogError(wxT("%s index out of bounds: %zu %zu"), name, index, v.Count());    \
        return ;                                                                    \
    }                                                                                \
} while (0)


AxisPlot::AxisPlot()
{
    m_legendPlotGap = 2;

    m_drawGridVertical = true;
    m_drawGridHorizontal = true;

    m_legend = NULL;
    m_crosshair = NULL;
    m_dataBackground = NULL;
    
    SetBackground(new FillAreaDraw(wxPen(DEFAULT_AXIS_BORDER_COLOUR)));
}

AxisPlot::~AxisPlot()
{
    for (size_t n = 0; n < m_horizontalAxes.Count(); n++) {
        Axis *axis = m_horizontalAxes[n];
        wxDELETE(axis);
    }

    for (size_t n = 0; n < m_verticalAxes.Count(); n++) {
        Axis *axis = m_verticalAxes[n];
        wxDELETE(axis);
    }

    wxDELETE(m_dataBackground);

    wxDELETE(m_legend);
    wxDELETE(m_crosshair);
}

wxCoord AxisPlot::GetAxesExtent(wxDC &dc, AxisArray *axes)
{
    wxCoord ext = 0;
    for (size_t nAxis = 0; nAxis < axes->Count(); nAxis++) {
        ext += (*axes)[nAxis]->GetExtent(dc);
    }
    return ext;
}

DataSet *AxisPlot::GetDataset(size_t index)
{
    return m_datasets[index];
}

Axis *AxisPlot::GetDatasetAxis(DataSet *dataset, size_t index, bool vertical)
{
    size_t axisIndex = 0;

    for (size_t nLink = 0; nLink < m_links.Count(); nLink++) {
        DataAxisLink &link = m_links[nLink];

        if (link.m_dataset == dataset) {
            if (vertical == link.m_axis->IsVertical()) {
                if (axisIndex == index) {
                    return link.m_axis;
                }
                axisIndex++;
            }
        }
    }
    return NULL; // not found
}

Axis *AxisPlot::GetDatasetAxis(DataSet *dataset, bool vertical)
{
    return GetDatasetAxis(dataset, 0, vertical);
}

size_t AxisPlot::GetDatasetCount()
{
    return m_datasets.Count();
}

bool AxisPlot::HasData()
{
    return m_datasets.Count() != 0;
}

void AxisPlot::SetCrosshair(Crosshair *crosshair)
{

}

void AxisPlot::SetDataBackground(AreaDraw *dataBackground)
{
    SetBackground(dataBackground);
}

void AxisPlot::SetDrawGrid(bool drawGridVertical, bool drawGridHorizontal)
{
    m_drawGridVertical = drawGridVertical;
    m_drawGridHorizontal = drawGridHorizontal;
}

void AxisPlot::SetLegend(Legend *legend)
{
    wxREPLACE(m_legend, legend);
}

void AxisPlot::AddAxis(Axis *axis)
{
    if (!AcceptAxis(axis)) {
        wxLogError(wxT("AxisPlot::AddAxis: axis unacceptable"));
        return ;
    }

    switch (axis->GetLocation()) {
    case AXIS_LEFT:
        m_leftAxes.Add(axis);
        m_verticalAxes.Add(axis);
        break;
    case AXIS_RIGHT:
        m_rightAxes.Add(axis);
        m_verticalAxes.Add(axis);
        break;
    case AXIS_TOP:
        m_topAxes.Add(axis);
        m_horizontalAxes.Add(axis);
        break;
    case AXIS_BOTTOM:
        m_bottomAxes.Add(axis);
        m_horizontalAxes.Add(axis);
        break;
    default:
        // BUG!
        wxLogError(wxT("AxisPlot::AddAxis: invalid location value %i"), axis->GetLocation());
        return ;
    }
    
    axis->Bind(EVT_AXIS_CHANGED, &AxisPlot::OnAxisChanged, this);
}

void AxisPlot::AddDataset(DataSet* dataset)
{
    if (!AcceptDataset(dataset)) {
        wxLogError(wxT("AxisPlot::AddAxis: dataset unacceptable"));
        return ;
    }

    // Subscribe to change events from this dataset so the plot can be redrawn if necessary.
    dataset->Bind(EVT_DATASET_CHANGED, &AxisPlot::OnDataChanged, this);
    
    // Add to the list of datasets drawn by this plot.
    m_datasets.Add(dataset);
}

void AxisPlot::AddObjects(DataSet *dataset, Axis *verticalAxis, Axis *horizontalAxis)
{
    AddDataset(dataset);
    AddAxis(verticalAxis);
    AddAxis(horizontalAxis);

    LinkDataVerticalAxis(m_datasets.Count() - 1, m_verticalAxes.Count() - 1);
    LinkDataHorizontalAxis(m_datasets.Count() - 1, m_horizontalAxes.Count() - 1);
}

void AxisPlot::LinkDataHorizontalAxis(size_t nData, size_t nAxis)
{
    CHECK_INDEX(wxT("data"), nData, m_datasets);
    CHECK_INDEX(wxT("horizontal axis"), nAxis, m_horizontalAxes);

    m_links.Add(new DataAxisLink(m_datasets[nData], m_horizontalAxes[nAxis]));
    m_horizontalAxes[nAxis]->AddDataset(m_datasets[nData]);

    m_horizontalAxes[nAxis]->UpdateBounds();
}

void AxisPlot::LinkDataVerticalAxis(size_t nData, size_t nAxis)
{
    CHECK_INDEX(wxT("data"), nData, m_datasets);
    CHECK_INDEX(wxT("vertical axis"), nAxis, m_verticalAxes);

    m_links.Add(new DataAxisLink(m_datasets[nData], m_verticalAxes[nAxis]));
    m_verticalAxes[nAxis]->AddDataset(m_datasets[nData]);

    m_verticalAxes[nAxis]->UpdateBounds();
}

// Inspects the passed dataset and if axes are set to automatically update
// then their dimensions are recalculated. The return value indicates if
// the axis bounds have changed or not.
bool AxisPlot::UpdateAxis(DataSet *dataset)
{
    int updated = 0;
    
    for (size_t nLink = 0; nLink < m_links.Count(); nLink++) {
        DataAxisLink &link = m_links[nLink];

        if (dataset == NULL || link.m_dataset == dataset) {
            if (link.m_axis->UpdateBounds()) {
                updated++;
            }
        }
    }
    
    return updated > 0;
}

bool AxisPlot::ToDataCoords(size_t nData, wxDC &dc, wxRect rc, wxCoord gx, wxCoord gy, double *x, double *y)
{
    DataSet *dataset = GetDataset(nData);
    wxCHECK_MSG(dataset != NULL, false, wxT("AxisPlot::ToDataCoords: Invalid dataset index"));

    Axis *horizAxis = GetDatasetHorizontalAxis(dataset);
    Axis *vertAxis = GetDatasetVerticalAxis(dataset);

    wxCHECK_MSG(horizAxis != NULL && vertAxis != NULL, false, wxT("AxisPlot::ToDataCoords: dataset not linked with horizontal or vertical axis"));

    wxRect rcData;
    wxRect rcLegend;

    CalcDataArea(dc, rc, rcData, rcLegend);
    if (!rcData.Contains(gx, gy)) {
        return false;
    }

    *x = horizAxis->ToData(dc, rcData.x, rcData.width, gx);
    *y = vertAxis->ToData(dc, rcData.y, rcData.height, gy);
    return true;
}

void AxisPlot::CalcDataArea(wxDC &dc, wxRect rc, wxRect &rcData, wxRect &rcLegend)
{
    if (m_legend != NULL) {
        wxSize legendExtent = m_legend->GetExtent(dc, m_datasets);

        switch (m_legend->GetHorizPosition()) {
        case wxLEFT:
            rcLegend.x = rc.x;

            rc.x += legendExtent.x + m_legendPlotGap;
            rc.width -= legendExtent.x + m_legendPlotGap;
            break;
        case wxRIGHT:
            rcLegend.x = rc.x + rc.width - legendExtent.x + m_legendPlotGap;

            rc.width -= legendExtent.x + m_legendPlotGap;
            break;
        case wxCENTER:
            rcLegend.x = rc.x + rc.width / 2 - legendExtent.x / 2;
            break;
        default:
            //(wxT("Invalid legend horizontal position"));
            return ;
        }

        switch (m_legend->GetVertPosition()) {
        case wxTOP:
            rcLegend.y = rc.y;

            rc.y += legendExtent.y + m_legendPlotGap;
            rc.height -= legendExtent.y + m_legendPlotGap;
            break;
        case wxBOTTOM:
            rcLegend.y = rc.y + rc.height - legendExtent.y + m_legendPlotGap;

            rc.height -= legendExtent.y + m_legendPlotGap;
            break;
        case wxCENTER:
            rcLegend.y = rc.y + rc.height / 2 - legendExtent.y / 2;
            break;
        default:
            //(wxT("Invalid legend vertical position"));
            return;
        }

        rcLegend.width = legendExtent.x;
        rcLegend.height = legendExtent.y;

        CheckFixRect(rcLegend);
    }

    rcData = rc;

    // substract axes areas from data rectangle
    if (m_leftAxes.Count() != 0) {
        wxCoord ext = GetAxesExtent(dc, &m_leftAxes);

        rcData.x += ext;
        rcData.width -= ext;
    }
    if (m_rightAxes.Count() != 0) {
        wxCoord ext = GetAxesExtent(dc, &m_rightAxes);

        rcData.width -= ext;
    }
    if (m_topAxes.Count() != 0) {
        wxCoord ext = GetAxesExtent(dc, &m_topAxes);

        rcData.y += ext;
        rcData.height -= ext;
    }
    if (m_bottomAxes.Count() != 0) {
        wxCoord ext = GetAxesExtent(dc, &m_bottomAxes);

        rcData.height -= ext;
    }

    CheckFixRect(rcData);
}

void AxisPlot::DrawAxes(wxDC &dc, wxRect &rc, wxRect rcData)
{
    if (m_leftAxes.Count() != 0) {
        wxRect rcLeftAxes(rc.x, rcData.y, (rcData.x - rc.x), rcData.height - 1);
        DrawAxesArray(dc, rcLeftAxes, &m_leftAxes, true);
    }
    if (m_rightAxes.Count() != 0) {
        wxRect rcRightAxes(rcData.x + rcData.width - 1, rcData.y, (rc.x + rc.width - rcData.x - rcData.width - 1), rcData.height);
        DrawAxesArray(dc, rcRightAxes, &m_rightAxes, true);
    }
    if (m_topAxes.Count() != 0) {
        wxRect rcTopAxes(rcData.x, rc.y, rcData.width, (rcData.y - rc.y));
        //wxRect rcTopAxes(rcData.x, rc.y + 2, rcData.width, (rcData.y - rc.y + 2));
        DrawAxesArray(dc, rcTopAxes, &m_topAxes, false);
    }
    if (m_bottomAxes.Count() != 0) {
        wxRect rcBottomAxes(rcData.x, rcData.y + rcData.height - 1, rcData.width, (rc.y + rc.height - rcData.y - rcData.height - 1));
        DrawAxesArray(dc, rcBottomAxes, &m_bottomAxes, false);
    }
}

void AxisPlot::DrawAxesArray(wxDC &dc, wxRect rc, AxisArray *axes, bool vertical)
{
    wxRect rcAxis(rc);

    for (size_t nAxis = 0; nAxis < axes->Count(); nAxis++) {
        Axis *axis = (*axes)[nAxis];
        wxCoord ext = axis->GetExtent(dc);

        if (vertical) {
            rcAxis.width = ext;
        }
        else {
            rcAxis.height = ext;
        }

        axis->Draw(dc, rcAxis);

        if (vertical) {
            rcAxis.x += ext;
        }
        else {
            rcAxis.y += ext;
        }
    }
}

// Draw the background of the data area, basically everything except the data.
void AxisPlot::DrawBackground(ChartDC& cdc, wxRect rc)
{
    wxRect rcPlot;
    wxRect rcLegend;
    
    wxDC& dc = cdc.GetDC();

    // Calculate the rectangle where the actual data is plotted.
    CalcDataArea(dc, rc, rcPlot, rcLegend);

    // Draw the very background of the plot area.
    m_background->Draw(dc, rcPlot);
    
    // Draw all static items.
    DrawGridLines(dc, rcPlot);
    DrawAxes(dc, rc, rcPlot);
    DrawMarkers(dc, rcPlot);
    DrawLegend (dc, rcLegend);

    if (m_crosshair != NULL) 
    {
        // TODO crosshair drawing
        //m_crosshair->Draw(dc, rcData, );
    }
}

void AxisPlot::DrawGridLines(wxDC &dc, wxRect rc)
{
    if (m_drawGridVertical) {
        for (size_t nAxis = 0; nAxis < m_verticalAxes.Count(); nAxis++) {
            m_verticalAxes[nAxis]->DrawGridLines(dc, rc);
        }
    }

    if (m_drawGridHorizontal) {
        for (size_t nAxis = 0; nAxis < m_horizontalAxes.Count(); nAxis++) {
            m_horizontalAxes[nAxis]->DrawGridLines(dc, rc);
        }
    }
}

void AxisPlot::DrawLegend(wxDC &dc, wxRect rcLegend)
{
    if (m_legend != NULL) {
        m_legend->Draw(dc, rcLegend, m_datasets);
    }
}

void AxisPlot::DrawMarkers(wxDC &dc, wxRect rcData)
{
    for (size_t n = 0; n < m_datasets.Count(); n++) {
        DataSet *dataset = m_datasets[n];

        if (dataset->GetMarkerCount() == 0) {
            continue;
        }

        Axis *horizAxis = GetDatasetHorizontalAxis(dataset);
        Axis *vertAxis = GetDatasetVerticalAxis(dataset);

        for (size_t nMarker = 0; nMarker < dataset->GetMarkerCount(); nMarker++) {
            Marker *marker = dataset->GetMarker(nMarker);

            marker->Draw(dc, rcData, horizAxis, vertAxis);
        }
    }
}

void AxisPlot::DrawData(ChartDC& cdc, wxRect rc)
{
    wxRect rcPlot;
    wxRect rcLegend;
    
    wxDC& dc = cdc.GetDC();

    // Calculate the rectangle where the actual data is plotted.
    CalcDataArea(dc, rc, rcPlot, rcLegend);
    
    // Deflate by one to prevent drawing on the axis.
    rcPlot.Deflate(1);

    // TODO: Currently all data items are drawn using antialiasing if it is available and enabled.
    // It would be better if this decision was made at the individual renderer level, for example 
    // a bar couild be drawn without antialiasing, but an XY line could be drawn with it.
    
    // A clipping rectangle is needed for the data area to avoid drawing outside this area when
    // a scrolled window is in use. The clipper is specific to the DC, so has to be created within
    // the correct context.
#if wxUSE_GRAPHICS_CONTEXT
		if (cdc.AntialiasActive()) 
        {
			wxGCDC gdc((wxMemoryDC&)dc);
            wxDCClipper clip(gdc, rcPlot);
			DrawDatasets(gdc, rcPlot);
		}
		else
        {
            wxDCClipper clip(dc, rcPlot);
            DrawDatasets(dc, rcPlot);
        }
			
#else
        wxDCClipper clip(dc, rcPlot);
		DrawDatasets(dc, rcPlot);
#endif
}

void AxisPlot::AxisChanged(Axis *WXUNUSED(axis))
{
    PlotChanged();
}

void AxisPlot::BoundsChanged(Axis *WXUNUSED(axis))
{
    PlotChanged();
}

void AxisPlot::ChartPanelChanged(wxChartPanel *oldPanel, wxChartPanel *newPanel)
{
    PlotChanged();
}

void AxisPlot::DatasetChanged(DataSet *dataset)
{
    PlotChanged();
}

void AxisPlot::OnAxisChanged(wxCommandEvent& event)
{
    PlotChanged();
}

void AxisPlot::OnDataChanged(wxCommandEvent& event)
{
    PlotChanged();
}

void AxisPlot::OnMouseMove(wxMouseEvent& event)
{
    /*
    for (size_t set = 0; set < GetDatasetCount(); set++)
    {
        BiDataSet* dataset = wxDynamicCast(GetDataset(set), BiDataSet);
        
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
                SetTipData(wxString::Format("Dataset: %zu, Series: %zu, Data: %g, %g", set, item.GetSeries(), 
                                                dataset->GetX(item.GetIndex(), item.GetSeries()), 
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

// TODO: Everything below this point is still TODO.

/*
void AxisPlot::ChartEnterWindow()
{
}
*/

void AxisPlot::ChartMouseDown(wxPoint &pt, int key)
{
    
}

/*
void AxisPlot::ChartMouseUp(wxPoint &pt, int key)
{
}

void AxisPlot::ChartMouseMove(wxPoint &pt)
{
}

void AxisPlot::ChartMouseDrag(wxPoint &pt)
{
}

void AxisPlot::ChartMouseWheel(int rotation)
{
}
*/