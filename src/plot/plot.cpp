/////////////////////////////////////////////////////////////////////////////
// Name:        plot.cpp
// Purpose:     plot base class implementation
// Author:      Moskvichev Andrey V.
// Created:     2008/11/07
// Copyright:   (c) 2008-2010 Moskvichev Andrey V. (c)2017 wxChartCtrl team.
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/plot/plot.h>
#include <wx/drawutils.h>

wxDEFINE_EVENT(EVT_PLOT_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(EVT_PLOT_TIP_DATA, wxCommandEvent);


Plot::Plot()
{
    m_textNoDataFont = *wxNORMAL_FONT;
    m_textNoData = wxT("No data");

    m_background = new NoAreaDraw();

    m_chartPanel = NULL;
    
    // Bind a few default events.
    Bind(wxEVT_MOTION, &Plot::OnMouseMove, this);
    Bind(wxEVT_SIZE, &Plot::OnPlotResize, this);
}

Plot::~Plot()
{
    wxDELETE(m_background);
}

void Plot::Draw(ChartDC &cdc, wxRect rc, PlotDrawMode mode)
{
    if (mode == PLOT_DRAW_BACKGROUND || mode == PLOT_DRAW_ALL)
        DrawBackground(cdc, m_rect);

    if (mode == PLOT_DRAW_DATA || mode == PLOT_DRAW_ALL)
    {
        if (HasData())
            DrawData(cdc,m_rect);
        else
            DrawNoDataMessage(cdc.GetDC(), m_rect);
    }
}

void Plot::DrawNoDataMessage(wxDC &dc, wxRect rc)
{
    dc.SetFont(m_textNoDataFont);
    DrawTextCenter(dc, m_rect, m_textNoData);
}

void Plot::SetChartPanel(wxChartPanel *chartPanel)
{
    ChartPanelChanged(m_chartPanel, chartPanel);
    m_chartPanel = chartPanel;
}

wxChartPanel *Plot::GetChartPanel()
{
    return m_chartPanel;
}

void Plot::ChartPanelChanged(wxChartPanel *WXUNUSED(oldPanel), wxChartPanel *WXUNUSED(newPanel))
{
    // Default - do nothing.
}

void Plot::PlotChanged()
{
    wxQueueEvent(this, new wxCommandEvent(EVT_PLOT_CHANGED));
}

void Plot::SetTipData(const wxString& tip)
{
    wxCommandEvent* event = new wxCommandEvent(EVT_PLOT_TIP_DATA);
    event->SetString(tip);
    
    wxQueueEvent(this, event);
}

void Plot::OnMouseMove(wxMouseEvent& event)
{
    // Default - do nothing.
}

void Plot::OnPlotResize(wxSizeEvent& event)
{
    m_rect = event.GetRect();
}

