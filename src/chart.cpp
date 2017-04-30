/////////////////////////////////////////////////////////////////////////////
// Name:    chart.cpp
// Purpose: chart implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/chart.h>
#include <wx/drawutils.h>
#include <wx/dcgraph.h>

wxDEFINE_EVENT(EVT_CHART_CHANGED, wxCommandEvent);

Chart::Chart(Plot* plot, Header* header, Footer* footer)
{
    Init(plot, header, footer);
}

Chart::Chart(Plot *plot, const wxString &title)
{
    Init(plot, new Header(TextElement(title, wxALIGN_CENTRE_HORIZONTAL, wxFontInfo(14))));
}

Chart::~Chart()
{
    wxDELETE(m_plot);
    wxDELETE(m_background);
    wxDELETE(m_header);
    wxDELETE(m_footer);
}

void Chart::Init(Plot* plot, Header* header, Footer* footer)
{
    // defaults
    wxColour bgColor = *wxWHITE;

    m_background = new FillAreaDraw(
            *wxThePenList->FindOrCreatePen(bgColor, 1, wxPENSTYLE_SOLID),
            *wxTheBrushList->FindOrCreateBrush(bgColor));

    m_margin = 5;

    m_plot = plot;
    m_header = header;
    m_footer = footer;
    m_headerGap = 2;
    
    // Subscribe to change events from the plot so the chart can be redrawn when necessary.
    plot->Bind(EVT_PLOT_CHANGED, &Chart::OnPlotChanged, this);

    m_horizScrolledAxis = NULL;
    m_vertScrolledAxis = NULL;
}

wxChartPanel *Chart::GetChartPanel()
{
    return m_chartPanel;
}

Axis *Chart::GetHorizScrolledAxis()
{
    return m_horizScrolledAxis;
}

Axis *Chart::GetVertScrolledAxis()
{
    return m_vertScrolledAxis;
}

void Chart::SetChartPanel(wxChartPanel *chartPanel)
{
    m_chartPanel = chartPanel;
    m_plot->SetChartPanel(chartPanel);
}

void Chart::SetScrolledAxis(Axis *axis)
{
    if (axis->IsVertical())
        m_vertScrolledAxis = axis;

    else
        m_horizScrolledAxis = axis;
}

void Chart::Draw(ChartDC &cdc, wxRect &rc, bool antialias)
{
    // Draw chart background with the current AreaDraw.
    m_background->Draw(cdc.GetDC(), rc);

    // Calculate header, footer rects and margins. Draw the header and footer if required.
    int topMargin = m_margin;
    int bottomMargin = m_margin;

    if (m_header && !m_header->IsEmpty()) 
    {
        wxRect headerRect = rc;
        Margins(headerRect, m_margin, m_margin, m_margin, m_margin);
        wxSize headerExtent = m_header->CalculateExtent(cdc.GetDC());
        headerRect.height = headerExtent.y + m_headerGap;
        topMargin += headerRect.height;
        m_header->Draw(cdc.GetDC(), headerRect);
    }

    if (m_footer && !m_footer->IsEmpty()) 
    {
        wxRect footerRect = rc;
        Margins(footerRect, m_margin, m_margin, m_margin, m_margin);
        wxSize footerExtent = m_footer->CalculateExtent(cdc.GetDC());
        footerRect.height = footerExtent.y + m_headerGap;
        footerRect.y = rc.height - footerRect.height;
        bottomMargin += footerRect.height;
        m_footer->Draw(cdc.GetDC(), footerRect);
    }
    
    // Shrink the drawing rectangle by the calculted margins.
    Margins(rc, m_margin, topMargin, m_margin, bottomMargin);
   
    // Draw the plot background, including axes and grid lines.
    m_plot->Draw(cdc, rc, PLOT_DRAW_BACKGROUND);
    
    // Draw the plot data.
    m_plot->Draw(cdc, rc, PLOT_DRAW_DATA);
}

void Chart::ChartChanged()
{
    wxQueueEvent(this, new wxCommandEvent(EVT_CHART_CHANGED));
    std::cout << "Chart::Chart changed event" << std::endl;
}

void Chart::OnPlotChanged(wxCommandEvent& event)
{
    ChartChanged();
}
