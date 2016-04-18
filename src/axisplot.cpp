/////////////////////////////////////////////////////////////////////////////
// Name:    axisplot.cpp
// Purpose: axis plot implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axisplot.h>
#include <wx/drawutils.h>

#include <wx/dcgraph.h>
#include "wx/arrimpl.cpp"

#include <iostream>

WX_DEFINE_EXPORTED_OBJARRAY(DataAxisLinkArray)


#define CHECK_INDEX(name, index, v) do {                                            \
    if (index >= v.Count()) {                                                        \
        wxLogError(wxT("%s index out of bounds: %i %i"), name, index, v.Count());    \
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
    
    SetDataBackground(new FillAreaDraw());
}

AxisPlot::~AxisPlot()
{
    for (size_t n = 0; n < m_datasets.Count(); n++) {
        Dataset *dataset = m_datasets[n];
        dataset->RemoveObserver(this);
    }

    for (size_t n = 0; n < m_horizontalAxes.Count(); n++) {
        Axis *axis = m_horizontalAxes[n];
        wxDELETE(axis);
    }

    for (size_t n = 0; n < m_verticalAxes.Count(); n++) {
        Axis *axis = m_verticalAxes[n];
        wxDELETE(axis);
    }

    SAFE_REMOVE_OBSERVER(this, m_dataBackground);
    wxDELETE(m_dataBackground);

    wxDELETE(m_legend);
    wxDELETE(m_crosshair);
}

void AxisPlot::SetDataBackground(AreaDraw *dataBackground)
{
    SAFE_REPLACE_OBSERVER(this, m_dataBackground, dataBackground);
    wxREPLACE(m_dataBackground, dataBackground);
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

    axis->AddObserver(this);
}

bool AxisPlot::HasData()
{
    return m_datasets.Count() != 0;
}

void AxisPlot::ChartPanelChanged(wxChartPanel *oldPanel, wxChartPanel *newPanel)
{
    m_redrawDataArea = true;
    FirePlotNeedRedraw();

    /* TODO
    if (m_crosshair != NULL) {
        SAFE_REPLACE_OBSERVER(m_crosshair, oldPanel, newPanel);
    }
    */
}

void AxisPlot::AddDataset(Dataset *dataset)
{
    if (!AcceptDataset(dataset)) {
        wxLogError(wxT("AxisPlot::AddAxis: dataset unacceptable"));
        return ;
    }

    m_datasets.Add(dataset);
    dataset->AddObserver(this);
    //dataset->AddRef();
    FirePlotNeedRedraw();
}

void AxisPlot::AddObjects(Dataset *dataset, Axis *verticalAxis, Axis *horizontalAxis)
{
    AddDataset(dataset);
    AddAxis(verticalAxis);
    AddAxis(horizontalAxis);

    LinkDataVerticalAxis(m_datasets.Count() - 1, m_verticalAxes.Count() - 1);
    LinkDataHorizontalAxis(m_datasets.Count() - 1, m_horizontalAxes.Count() - 1);
}

size_t AxisPlot::GetDatasetCount()
{
    return m_datasets.Count();
}

Dataset *AxisPlot::GetDataset(size_t index)
{
    return m_datasets[index];
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

void AxisPlot::SetLegend(Legend *legend)
{
    wxREPLACE(m_legend, legend);
    FirePlotNeedRedraw();
}

void AxisPlot::SetCrosshair(Crosshair *crosshair)
{
    /*// TODO
    if (m_crosshair != NULL && GetChartPanel() != NULL) {
        GetChartPanel()->RemoveObserver(m_crosshair);
    }

    wxREPLACE(m_crosshair, crosshair);
    if (m_crosshair != NULL && GetChartPanel() != NULL) {
        GetChartPanel()->AddObserver(m_crosshair);
    }
    */
    FirePlotNeedRedraw();
}

// Inspects the passed dataset and if axes are set to automatically update
// then their dimensions are recalculated. The return value indicates if
// the axis bounds have changed or not.
bool AxisPlot::UpdateAxis(Dataset *dataset)
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

void AxisPlot::SetDrawGrid(bool drawGridVertical, bool drawGridHorizontal)
{
    m_drawGridVertical = drawGridVertical;
    m_drawGridHorizontal = drawGridHorizontal;

    FirePlotNeedRedraw();
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

Axis *AxisPlot::GetDatasetAxis(Dataset *dataset, size_t index, bool vertical)
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

Axis *AxisPlot::GetDatasetAxis(Dataset *dataset, bool vertical)
{
    return GetDatasetAxis(dataset, 0, vertical);
}

void AxisPlot::NeedRedraw(DrawObject *WXUNUSED(obj))
{
    FirePlotNeedRedraw();
}

void AxisPlot::DatasetChanged(Dataset *dataset)
{
    // Update the axis. If the axis have changed (UpdateAxis returns true)
    // then redraw the chart background because the scale will have changed.
    if (UpdateAxis(dataset))
        m_redrawDataArea = true;
    else
        m_redrawDataArea = false;

    FirePlotNeedRedraw();
}

void AxisPlot::AxisChanged(Axis *WXUNUSED(axis))
{
    FirePlotNeedRedraw();
}

void AxisPlot::BoundsChanged(Axis *WXUNUSED(axis))
{
    FirePlotNeedRedraw();
}

wxCoord AxisPlot::GetAxesExtent(wxDC &dc, AxisArray *axes)
{
    wxCoord ext = 0;
    for (size_t nAxis = 0; nAxis < axes->Count(); nAxis++) {
        ext += (*axes)[nAxis]->GetExtent(dc);
    }
    return ext;
}

bool AxisPlot::ToDataCoords(size_t nData, wxDC &dc, wxRect rc, wxCoord gx, wxCoord gy, double *x, double *y)
{
    Dataset *dataset = GetDataset(nData);
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

void AxisPlot::DrawAxes(wxDC &dc, wxRect &rc, wxRect rcData)
{
    if (m_leftAxes.Count() != 0) {
        wxRect rcLeftAxes(rc.x, rcData.y, (rcData.x - rc.x), rcData.height);
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

void AxisPlot::DrawMarkers(wxDC &dc, wxRect rcData)
{
    for (size_t n = 0; n < m_datasets.Count(); n++) {
        Dataset *dataset = m_datasets[n];

        if (dataset->GetMarkersCount() == 0) {
            continue;
        }

        Axis *horizAxis = GetDatasetHorizontalAxis(dataset);
        Axis *vertAxis = GetDatasetVerticalAxis(dataset);

        for (size_t nMarker = 0; nMarker < dataset->GetMarkersCount(); nMarker++) {
            Marker *marker = dataset->GetMarker(nMarker);

            marker->Draw(dc, rcData, horizAxis, vertAxis);
        }
    }
}

void AxisPlot::DrawLegend(wxDC &dc, wxRect rcLegend)
{
    if (m_legend != NULL) {
        m_legend->Draw(dc, rcLegend, m_datasets);
    }
}

// Draw the background of the data area, basically everything except the data.
void AxisPlot::DrawDataAreaBackground(wxDC &dc, wxRect rc)
{
    wxRect rcData;
    wxRect rcLegend;

    // Hackish test to see if the background needs to be redrawn 
    // due to a size change.
    if (rc.GetSize() != m_drawRect)
    {
        m_redrawDataArea = true;
        m_drawRect.SetSize(rc.GetSize());
        m_drawRect.SetTopLeft(wxPoint(0, 0));
    }

    // Calculate the rectangle where the actual data is plotted.
    CalcDataArea(dc, m_drawRect, rcData, rcLegend);
    
    // The plot area has changed (size change, axis change).
    if (m_redrawDataArea) {
        wxMemoryDC mdc;
        wxPrintf ("Drawing background\n");
        
        // Redimension the 
        m_plotBackgroundBitmap.Create(m_drawRect.GetWidth(), m_drawRect.GetHeight());
        mdc.SelectObject(m_plotBackgroundBitmap);

        // Clear the background of the data area and draw the axis.
        m_dataBackground->Draw(mdc, m_drawRect);
        DrawAxes(mdc, m_drawRect, rcData);

        // Define the clipping rectangle for the data area.
        wxRect clipRc = rcData;
        clipRc.Deflate(1, 1);
        wxDCClipper clip(mdc, clipRc);

        // Draw markers and gridlines.
        DrawMarkers(mdc, rcData);
        DrawGridLines(mdc, rcData);
        
        // Redimension the data overlay bitmap here, in preparation.
        // TODO: The overlay only needs to be rcData big, but currently
        // this function draws the whole chart, including axes and titles!
        m_dataOverlayBitmap.Create(m_drawRect.GetWidth(), m_drawRect.GetHeight());

        // Clear redraw flag. TODO: Replace flag with 'smarter' function calls.
        m_redrawDataArea = false;
    }

    wxMemoryDC mdc;
    mdc.SelectObject(m_dataOverlayBitmap);

    // Copy the background bitmap onto a temporary bitmap.
    mdc.DrawBitmap(m_plotBackgroundBitmap, 0, 0);

    // Draw the actual plot data onto the temporary bitmap (over the top of the 
    // background. If antialiasing is enabled, then draw the data with a wxGCDC.
#if wxUSE_GRAPHICS_CONTEXT
    if (true) { // TODO: Should be if m_antialias.
        wxGCDC gdc(mdc);
        DrawData ((wxDC&)gdc, rcData);
    }
    else {
        DrawData ((wxDC&)mdc, rcData);
    }
#else
        DrawData ((wxDC&)mdc, rcData);
#endif

    // Finally copy the updated temporary bitmap onto the background.
    dc.DrawBitmap(m_dataOverlayBitmap, rc.GetTopLeft());
    
    DrawLegend (dc, rcLegend);
    
    if (m_crosshair != NULL) {
        // TODO crosshair drawing
        //m_crosshair->Draw(dc, rcData, );
    }
}

void AxisPlot::DrawData(wxDC &dc, wxRect rcData)
{
    DrawDatasets(dc, rcData);
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