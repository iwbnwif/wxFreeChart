/////////////////////////////////////////////////////////////////////////////
// Name:    chart.h
// Purpose: chart declarations
// Author:    Moskvichev Andrey V., changes by Andreas Kuechler
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CHART_H_
#define CHART_H_

#include <wx/wxfreechartdefs.h>

#include <wx/refobject.h>
#include <wx/plot/plot.h>

#include <wx/areadraw.h>

#include <wx/axis/axis.h>

#include <wx/title.h>

class WXDLLIMPEXP_FREECHART Chart;
class WXDLLIMPEXP_FREECHART wxChartPanel;

wxDECLARE_EVENT(EVT_CHART_CHANGED, wxCommandEvent);

/**
 * Chart. Contains plot, title and chart attributes.
 */
class WXDLLIMPEXP_FREECHART Chart : public wxEvtHandler
{
public:
    /**
     * Constructor allowing creation of a custom header and foooter.
     * @param plot The plot that will displayed in this chart. If more than one plot will be displayed, then use MultiPlot - see
     * MultiPlot class documentation for more details.
     * @param header The text element container that will be placed within the header area of the chart.
     * @param footer The text element container that will be placed within the footer area of the chart.
     */
    Chart(Plot *plot, Header* header = NULL, Footer* footer = NULL);

    /**
     * Convenience constructor for creating a chart with a simple header and no footer. A more complex header and a footer can
     * still be added later if necessary.
     * @param plot The plot that will displayed in this chart. If more than one plot will be displayed, then use MultiPlot - see
     * MultiPlot class documentation for more details.
     * @param title The chart's title that will be drawn in the header area using the default title font. Can be NULL, in which
     * case the chart will have no title.
     */
    Chart(Plot *plot, const wxString &title = wxEmptyString);

    /**
     * Destructor. Will also destroy plot, background, header and footer objects.
     */
    virtual ~Chart();

    /**
     * Gets the AreaDraw object that draws the background area of this chart.
     * @return AreaDraw responsible for drawing the chart area.
     */
    AreaDraw* GetBackground()
    {
        return m_background;
    }

    /**
     * Gets the chart panel to which this plot belongs.
     * @return %Chart panel which this plot belongs to.
     */
    wxChartPanel *GetChartPanel();  

    Axis *GetHorizScrolledAxis();

    Axis *GetVertScrolledAxis();

    /**
     * Returns plot associated with chart.
     * @return plot Plot belonging to this chart.
     */
    Plot *GetPlot()
    {
        return m_plot;
    }

    /**
     * Sets chart background.
     * @param background chart background
     */
    void SetBackground(AreaDraw *background)
    {
        wxREPLACE(m_background, background);
    }

    /**
     * Calcalate plot area rectangle.
     * @param dc device context
     * @param rc entire chart rectangle
     * @return plot area rectangle
     */
    //    wxRect CalcPlotRect(wxDC &dc, wxRect rc);

    /**
     * Sets chart title.
     * @param title chart title
     */
    void SetTitle(wxString title)
    {
        SetHeader(new Header(TextElement(title)));
    }

    void SetHeader(Header* header)
    {
        wxREPLACE(m_header, header);
    }

    void SetFooter(Footer* footer)
    {
        wxREPLACE(m_footer, footer);
    }

    void SetMargin(wxCoord margin)
    {
        m_margin = margin;
    }

    //
    // TODO old scrolling code is deprecated,
    // will be used Zoom/pan feature instead.
    //

    void SetScrolledAxis(Axis *axis);

    void SetChartPanel(wxChartPanel *chartPanel);

protected:
    /**
     * Draws chart.
     * @param dc device context
     * @param rc rectangle where to draw chart
     */
    void Draw(ChartDC& dc, wxRect& rc, bool antialias = false);

    /**
     * Called by wxChartPanel when it changes size. The chart then recalculates header, plot area and footer sizes.
     * @param cdc The device context of the chart panel's drawing area. This is needed to calculate text extents.
     * @param size The full size of the chart, including header, plot and footer.
     */
    virtual void ResizeChart(ChartDC& cdc, const wxRect& rect);

    /**
     * Event handler called when (one of) the contained plot(s) changes.
     * @param event Details of the change event.
     */
    virtual void OnPlotChanged(wxCommandEvent& event);
    
    /**
     * Event handler called when (one of) the contained plot(s) wants to set or clear the tooltip.
     * @param event The event's details, containing the new string.
     */
    virtual void OnToolTip(wxCommandEvent& event);

private:
    void Init(Plot* plot, Header* header = NULL, Footer* footer = NULL);
    
    virtual void ChartChanged();

    Plot *m_plot;
    AreaDraw *m_background;
    Header* m_header;
    Footer* m_footer;

    int m_headerGap;
    wxRect m_headerRect;
    wxRect m_footerRect;
    wxCoord m_margin;

    Axis *m_horizScrolledAxis;
    Axis *m_vertScrolledAxis;

    wxChartPanel *m_chartPanel;
    
friend wxChartPanel;
};

#endif /*CHART_H_*/
