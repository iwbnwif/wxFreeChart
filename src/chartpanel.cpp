/////////////////////////////////////////////////////////////////////////////
// Name:    chartpanel.cpp
// Purpose:
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/chartpanel.h>
#include <wx/dcbuffer.h>

#if wxUSE_GRAPHICS_CONTEXT
#include <wx/dcgraph.h>
#endif /* wxUSE_GRAPHICS_CONTEXT */

//
// Events
//

/*// XXX deprecated?!
DEFINE_EVENT_TYPE(wxEVT_FREECHART_LEFT_CLICK)
DEFINE_EVENT_TYPE(wxEVT_FREECHART_RIGHT_CLICK)
DEFINE_EVENT_TYPE(wxEVT_FREECHART_LEFT_DCLICK)
DEFINE_EVENT_TYPE(wxEVT_FREECHART_RIGHT_DCLICK)
DEFINE_EVENT_TYPE(wxEVT_FREECHART_LEFT_DOWN)
DEFINE_EVENT_TYPE(wxEVT_FREECHART_RIGHT_DOWN)
DEFINE_EVENT_TYPE(wxEVT_FREECHART_LEFT_UP)
DEFINE_EVENT_TYPE(wxEVT_FREECHART_RIGHT_UP)
*/

const int scrollPixelStep = 100;
const int stepMult = 100;

void GetAxisScrollParams(Axis *axis, int &noUnits, int &pos)
{
    double minValue, maxValue;
    axis->GetDataBounds(minValue, maxValue);

    noUnits = RoundHigh(stepMult * (maxValue - minValue - axis->GetWindowWidth())) + 10/*XXX dirty hack*/;
    if (noUnits < 0) {
        noUnits = 0;
    }

    pos = (int) (stepMult * (axis->GetWindowPosition() - minValue));
}


//
// wxChartPanel
//

BEGIN_EVENT_TABLE(wxChartPanel, wxScrolledWindow)
    EVT_PAINT(wxChartPanel::OnPaint)
    EVT_SIZE(wxChartPanel::OnSize)
    EVT_SCROLLWIN(wxChartPanel::OnScrollWin)
    EVT_MOUSE_EVENTS(wxChartPanel::OnMouseEvents)
END_EVENT_TABLE()

wxChartPanel::wxChartPanel(wxWindow *parent, wxWindowID id, Chart *chart, const wxPoint &pos, const wxSize &size)
: wxScrolledWindow(parent, id, pos, size, wxHSCROLL | wxVSCROLL | wxFULL_REPAINT_ON_RESIZE)
{
    new wxLogWindow(this, "Log Window");
    
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    EnableScrolling(false, false);

    m_chart = NULL;
    m_mode = NULL;
    m_antialias = false;
    
    m_redrawThrottle.SetOwner(this);
    Bind(wxEVT_TIMER, &wxChartPanel::OnThrottleTimer, this);

    ResizeBackBitmap(size);

    SetScrollRate(1, 1);
    SetChart(chart);
}

wxChartPanel::~wxChartPanel()
{
    wxDELETE(m_chart);
}

void wxChartPanel::SetChart(Chart *chart)
{
    if (m_chart != NULL)
    {
        m_chart->Unbind(EVT_CHART_CHANGED, &wxChartPanel::OnChartChanged, this);
        m_chart->SetChartPanel(NULL);
    }

    wxREPLACE(m_chart, chart);

    if (m_chart != NULL) 
    {
        m_chart->Bind(EVT_CHART_CHANGED, &wxChartPanel::OnChartChanged, this);
        m_chart->SetChartPanel(this);
    }

    RecalcScrollbars();

    // Update the chart with the current size.
    Resize(GetClientRect());
}

Chart *wxChartPanel::GetChart()
{
    return m_chart;
}

void wxChartPanel::SetMode(ChartPanelMode *mode)
{
    wxREPLACE(m_mode, mode);

    if (m_mode != NULL)
        m_mode->Init(this);
}

void wxChartPanel::SetAntialias(bool antialias)
{
    if (m_antialias != antialias) {
#if wxUSE_GRAPHICS_CONTEXT
#else
        wxASSERT_MSG(!antialias, wxT("Cannot enable antialiasing due to missing wxUSE_GRAPHICS_CONTEXT"));
#endif
        m_antialias = antialias;

        RedrawBackBitmap();
        Refresh(false);
    }
}

bool wxChartPanel::GetAntialias()
{
    return m_antialias;
}

wxBitmap wxChartPanel::CopyBackbuffer()
{
    return wxBitmap(m_backBitmap);
}

void wxChartPanel::ChartChanged(Chart *WXUNUSED(chart))
{
    RedrawBackBitmap();
    Refresh(false);
}

void wxChartPanel::ChartScrollsChanged(Chart *WXUNUSED(chart))
{
    RecalcScrollbars();

    RedrawBackBitmap();
    Refresh(false);
}

void wxChartPanel::RecalcScrollbars()
{
    if (m_chart == NULL) {
        SetScrollbars(1, 1, 0, 0, 0, 0, true);
        return ;
    }

    Axis *horizAxis = m_chart->GetHorizScrolledAxis();
    Axis *vertAxis = m_chart->GetVertScrolledAxis();

    int noUnitsX = 0;
    int noUnitsY = 0;
    int xPos = 0;
    int yPos = 0;

    if (horizAxis != NULL) {
        GetAxisScrollParams(horizAxis, noUnitsX, xPos);
    }

    if (vertAxis != NULL) {
        GetAxisScrollParams(vertAxis, noUnitsY, yPos);
    }

    SetScrollbars(scrollPixelStep, scrollPixelStep, noUnitsX, noUnitsY, xPos, yPos, true);
}

void wxChartPanel::OnPaint(wxPaintEvent &WXUNUSED(ev))
{
    wxPaintDC dc(this);

    if (m_chart != NULL)
        dc.DrawBitmap(m_backBitmap, 0, 0, false);

    else 
    {
        dc.SetBrush(*wxBLUE); // *wxTheBrushList->FindOrCreateBrush(GetBackgroundColour()));
        dc.SetPen(*wxThePenList->FindOrCreatePen(GetBackgroundColour(), 1, wxPENSTYLE_SOLID));
        dc.DrawRectangle(GetClientRect());
    }
}

void wxChartPanel::OnSize(wxSizeEvent &ev)
{
    Resize(GetClientRect());
}

void wxChartPanel::OnScrollWin(wxScrollWinEvent &ev)
{
    if (m_chart == NULL) {
        return ;
    }

    Axis *axis = NULL;

    switch (ev.GetOrientation()) {
    case wxHORIZONTAL:
        axis = m_chart->GetHorizScrolledAxis();
        break;
    case wxVERTICAL:
        axis = m_chart->GetVertScrolledAxis();
        break;
    default: // BUG
        return ;
    }

    if (axis != NULL) {
        double winPos = (double) ev.GetPosition() / (double) stepMult;
        double minValue, maxValue;

        axis->GetDataBounds(minValue, maxValue);
        winPos += minValue;

        axis->SetWindowPosition(winPos);
        
        ChartScrollsChanged(m_chart);
    }
    ev.Skip();
}

void wxChartPanel::OnMouseEvents(wxMouseEvent &ev)
{
    // Forward the mouse event to the Plot or Multiplot
    if (GetChart() && GetChart()->GetPlot())
        wxQueueEvent(GetChart()->GetPlot(), new wxMouseEvent(ev));

    
    if (m_mode == NULL) {
        return ;
    }


#if 0
    // TODO
    switch (ev.GetEventType()) {
    case wxEVT_ENTER_WINDOW:
        m_mode->ChartEnterWindow();
        break;
    case wxEVT_LEAVE_WINDOW:
        m_mode->ChartLeaveWindow();
        break;
    case wxEVT_LEFT_DOWN:
        m_mode->ChartMouseDown(ev.GetPosition(), wxMOUSE_BTN_LEFT);
        break;
    case wxEVT_LEFT_UP:
        m_mode->ChartMouseUp(ev.GetPosition(), wxMOUSE_BTN_LEFT);
        break;
    //case wxEVT_LEFT_DCLICK:
    case wxEVT_MIDDLE_DOWN:
        m_mode->ChartMouseDown(ev.GetPosition(), wxMOUSE_BTN_MIDDLE);
        break;
    case wxEVT_MIDDLE_UP:
        m_mode->ChartMouseUp(ev.GetPosition(), wxMOUSE_BTN_MIDDLE);
        break;
    //case wxEVT_MIDDLE_DCLICK:
    case wxEVT_RIGHT_DOWN:
        m_mode->ChartMouseDown(ev.GetPosition(), wxMOUSE_BTN_RIGHT);
        break;
    case wxEVT_RIGHT_UP:
        m_mode->ChartMouseUp(ev.GetPosition(), wxMOUSE_BTN_RIGHT);
        break;
    //case wxEVT_RIGHT_DCLICK:
    case wxEVT_MOTION:
        if (ev.Dragging()) {
            m_mode->ChartMouseDrag(ev.GetPosition());
        }
        else {
            m_mode->ChartMouseMove(ev.GetPosition());
        }
        break;
    case wxEVT_MOUSEWHEEL:
        m_mode->ChartMouseWheel(GetWheelRotation());
        break;
    }
#endif
}

void wxChartPanel::ScrollAxis(Axis *axis, int d)
{
    double delta = (double) d / (double) stepMult;
    double minValue, maxValue;

    axis->GetDataBounds(minValue, maxValue);

    double winPos = axis->GetWindowPosition();
    winPos += minValue + delta;

    axis->SetWindowPosition(winPos);
}

void wxChartPanel::RedrawBackBitmap()
{
    wxLogMessage("wxChartPanel::RedrawBackBitmap");
    wxMemoryDC mdc(m_backBitmap);

    ChartDC cdc (mdc, m_antialias);

    if (m_chart != NULL) 
    {
        wxRect rect = GetClientRect();
        m_chart->Draw(cdc, rect, m_antialias);
    }
        
    else
    {
        mdc.SetBrush(*wxRED_BRUSH);
        mdc.DrawRectangle(GetClientRect());
    }
}

void wxChartPanel::Resize(const wxRect& rect)
{
    // Create a temporary DC for the chart (needed to calculate text extents).
    wxMemoryDC mdc(m_backBitmap);
    ChartDC cdc (mdc, m_antialias);   

    // Update the chart's size (will cascade to plot).
    if (m_chart)
        m_chart->ResizeChart(cdc, rect);
    
    // Update the caching bitmap's size.
    ResizeBackBitmap(rect.GetSize());
}

void wxChartPanel::ResizeBackBitmap(wxSize size)
{
    // Make sure the size is valid for a bitmap (at least 1 x 1).
    size.IncTo(wxSize(1, 1));
    
    // Rescale image with a zoom blur effect whilst the window size is changing.
    if (m_backBitmap.IsOk())
    {
        wxImage old = m_backBitmap.ConvertToImage();
        m_backBitmap = wxBitmap(old.Rescale(size.x, size.y, wxIMAGE_QUALITY_BILINEAR));
    }
    
    else
        m_backBitmap.Create(size.GetWidth(), size.GetHeight());
}

void wxChartPanel::OnChartChanged(wxCommandEvent& event)
{
    if (!m_redrawThrottle.IsRunning())
        m_redrawThrottle.StartOnce(10);
        
    else
        wxLogMessage("Redraw throttled");
}

void wxChartPanel::OnThrottleTimer(wxTimerEvent& event)
{
    wxLogMessage("Redraw timeout");
    RedrawBackBitmap();
    Refresh(false);
}

