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
#include <wx/plot.h>

#include <wx/areadraw.h>

#include <wx/axis/axis.h>

#include <wx/title.h>

class WXDLLIMPEXP_FREECHART Chart;
class WXDLLIMPEXP_FREECHART wxChartPanel;

/**
 * Chart. Contains plot, title and chart attributes.
 */
class WXDLLIMPEXP_FREECHART Chart
{
public:
    /**
     * Constructs new chart.
     * @param plot plot
     * @param title chart title (empty string - no title)
     */
    Chart(Plot *plot, const wxString &title = wxEmptyString);

    Chart(Plot *plot, Header* header = NULL, Footer* footer = NULL);

    virtual ~Chart();

    /**
     * Returns plot associated with chart.
     * @return plot
     */
    Plot *GetPlot()
    {
        return m_plot;
    }

    /**
     * Draws chart.
     * @param dc device context
     * @param rc rectangle where to draw chart
     */
    void Draw(ChartDC& dc, wxRect& rc, bool antialias = false);

    /**
     * Sets chart background.
     * @param background chart background
     */
    void SetBackground(AreaDraw *background)
    {
        wxREPLACE(m_background, background);
    }
    
    AreaDraw* GetBackground()
    {
        return m_background;
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

    Axis *GetHorizScrolledAxis();

    Axis *GetVertScrolledAxis();


    wxChartPanel *GetChartPanel();

    void SetChartPanel(wxChartPanel *chartPanel);

    //
    // PlotObserver
    //
    virtual void PlotNeedRedraw(Plot *plot);

    //
    // AxisObserver
    //
    virtual void AxisChanged(Axis *axis);

    virtual void BoundsChanged(Axis *axis);

private:
    void Init(Plot* plot, Header* header = NULL, Footer* footer = NULL);

    Plot *m_plot;
    AreaDraw *m_background;
    Header* m_header;
    Footer* m_footer;

    int m_headerGap;
    wxCoord m_margin;

    Axis *m_horizScrolledAxis;
    Axis *m_vertScrolledAxis;

    wxChartPanel *m_chartPanel;
};

#endif /*CHART_H_*/
