/////////////////////////////////////////////////////////////////////////////
// Name:    chartpanel.h
// Purpose: wxChartPanel declaration
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CHARTPANEL_H_
#define CHARTPANEL_H_

#include <wx/wxfreechartdefs.h>
#include <wx/chart.h>

class wxChartPanel;

/**
 * Base class for zoom/pan modes.
 */
class WXDLLIMPEXP_FREECHART ChartPanelMode
{
public:
    // IY: Virtual destructor needed otherwise behaviour is undefined.
    virtual ~ChartPanelMode() {}
    virtual void Init(wxChartPanel *chartPanel) = 0;
};


/**
 * ChartPanel is wxWidgets panel for displaying chart.
 *
 */
class WXDLLIMPEXP_FREECHART wxChartPanel : public wxScrolledWindow
{
public:
    wxChartPanel(wxWindow *parent, wxWindowID = wxID_ANY, Chart *chart = NULL,
        const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
    virtual ~wxChartPanel();

    /**
     * Sets chart.
     * @param chart new chart
     */
    void SetChart(Chart *chart);

    /**
     * Returns chart.
     * @return chart
     */
    Chart *GetChart();

    /**
     * Sets chart panel mode, eg. zoom, pan, etc.
     * @param mode mode
     */
    void SetMode(ChartPanelMode *mode);

    /**
     * Turn antialiasing on/off.
     * Has effect only when wx wxUSE_GRAPHICS_CONTEXT is set in wxWidgets build.
     * Warning: this feature can dramatically lower rendering performance.
     *
     * @param antialias true to turn on antialiasing.
     */
    void SetAntialias(bool antialias);

    /**
     * Checks whether antialiasing is enabled.
     * @return true if antialiasing is enabled
     */
    bool GetAntialias();

    /**
     * Returns back buffer copy as wxBitmap.
     * Can be used to save chart image to file.
     * @return back buffer copy as wxBitmap
     */
    wxBitmap CopyBackbuffer();

    //
    // ChartObserver
    //
    virtual void ChartChanged(Chart *chart);

    virtual void ChartScrollsChanged(Chart *chart);

    // TODO: Quick hack to allow axis plot to call to cause refresh from event - set back to private.
    void RedrawBackBitmap();

protected:
    void OnChartChanged(wxCommandEvent& event);

private:
    void ResizeBackBitmap(wxSize size);
    void RecalcScrollbars();

    //
    // Event handlers
    //
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnScrollWin(wxScrollWinEvent& event);
    void OnMouseEvents(wxMouseEvent& event);
    
    /**
     * \cond INTERNAL
     */
     
    /**
     * The chart panel implements a very simple throttling mechanism for limiting the number of 'burst' redraws caused
     * by several small changes at a time.
     * 
     * A timer is started (currently 10 milliseconds) that is allowed to timeout prior to the redraw occuring. Any 
     * redraw instructions arriving within the 10 millisecond period are discarded and only the first redraw command
     * has any effect.
     * 
     * This is safe because currently the whole chart is redrawn for each redraw event. Therefore, whatever causes the
     * redraw will be included in the udpate. 
     * 
     * It may still be possible to aggregate redraws in future using a similar mechanism to save the common parts of the
     * redraw being repeated.
     */
    void OnThrottleTimer(wxTimerEvent& event);

    void Resize(const wxRect& rect);
    
    void ScrollAxis(Axis *axis, int d);

    Chart *m_chart;

    wxBitmap m_backBitmap;

    bool m_antialias;

    ChartPanelMode *m_mode;
    
    wxTimer m_redrawThrottle;

    /**
     * \endcond
     */
    DECLARE_EVENT_TABLE()
};


#endif /*CHARTPANEL_H_*/
