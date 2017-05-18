/////////////////////////////////////////////////////////////////////////////
// Name:    chart.cpp
// Purpose: chart implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/chart.h>
#include <wx/chartpanel.h>
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
    
    // Subscribe to plot events so the chart can be redrawn when necessary.
    plot->Bind(EVT_PLOT_CHANGED, &Chart::OnPlotChanged, this);
    plot->Bind(EVT_PLOT_TIP_DATA, &Chart::OnToolTip, this);
    
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

    // Draw header and footer if necessary.
    if (m_header && !m_header->IsEmpty()) 
        m_header->Draw(cdc.GetDC(), m_headerRect);

    if (m_footer && !m_footer->IsEmpty()) 
        m_footer->Draw(cdc.GetDC(), m_footerRect);

    // Draw the plot background, including axes and grid lines.
    m_plot->Draw(cdc, rc, PLOT_DRAW_BACKGROUND);
    
    // Draw the plot data.
    m_plot->Draw(cdc, rc, PLOT_DRAW_DATA);
}

void Chart::ChartChanged()
{
    wxQueueEvent(this, new wxCommandEvent(EVT_CHART_CHANGED));
}

void Chart::ResizeChart(ChartDC& cdc, const wxRect& rect)
{
    // Calculate header, footer rects and margins.
    int topMargin = m_margin;
    int bottomMargin = m_margin;

    if (m_header && !m_header->IsEmpty()) 
    {
        m_headerRect = rect;
        Margins(m_headerRect, m_margin, m_margin, m_margin, m_margin);
        wxSize headerExtent = m_header->CalculateExtent(cdc.GetDC());
        m_headerRect.height = headerExtent.y + m_headerGap;
        topMargin += m_headerRect.height;
    }

    if (m_footer && !m_footer->IsEmpty()) 
    {
        m_footerRect = rect;
        Margins(m_footerRect, m_margin, m_margin, m_margin, m_margin);
        wxSize footerExtent = m_footer->CalculateExtent(cdc.GetDC());
        m_footerRect.height = footerExtent.y + m_headerGap;
        m_footerRect.y = rect.height - m_footerRect.height;
        bottomMargin += m_footerRect.height;
    }
    
    if (m_plot)
    {
        // Shrink the drawing rectangle by the calculted margins.
        wxRect plotRect = rect;
        Margins(plotRect, m_margin, topMargin, m_margin, bottomMargin);

        // TODO: Why isn't this being called?
        wxQueueEvent(m_plot, new wxSizeEvent(plotRect, wxID_ANY));

        m_plot->SetPlotRect(plotRect);
    }
}

void Chart::OnPlotChanged(wxCommandEvent& event)
{
    ChartChanged();
}

void Chart::OnToolTip(wxCommandEvent& event)
{
    wxASSERT(GetChartPanel());
    
    if (event.GetString() != wxEmptyString)
        GetChartPanel()->SetToolTip(event.GetString());
        
    else
        GetChartPanel()->UnsetToolTip();
}
