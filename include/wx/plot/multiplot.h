/////////////////////////////////////////////////////////////////////////////
// Name:    multiplot.h
// Purpose:
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef MULTIPLOT_H_
#define MULTIPLOT_H_

#include <wx/dynarray.h>
#include <wx/plot/plot.h>

WX_DECLARE_USER_EXPORTED_OBJARRAY(Plot *, PlotArray, WXDLLIMPEXP_FREECHART);

/**
 * Multiplot is plot containing one or more plots, called subplots.
 * It arranges subplots to rows and columns.
 */
class WXDLLIMPEXP_FREECHART MultiPlot : public Plot
{
public:
    /**
     * Constructs new multiplot.
     * @param rows number of rows for subplots
     * @param cols number of columns for subplots
     * @param horizGap distance between columns
     * @param vertGap distance between rows
     */
    MultiPlot(int rows, int cols, wxCoord horizGap, wxCoord vertGap);
    virtual ~MultiPlot();

    /**
     * Add plot to this multiplot.
     * @param subPlot plot to be added
     */
    void AddPlot(Plot *subPlot)
    {
        m_subPlots.Add(subPlot);
    }

    //
    // PlotObserver
    //
    virtual void PlotNeedRedraw(Plot *plot);
    
    virtual void SetPlotRect(const wxRect& rect)
    {
        m_rect = rect;
        CalcSubplotRects();
        PlotChanged();
    }

protected:
    virtual bool HasData();

    virtual void DrawData(ChartDC& cdc, wxRect rc);
    
    /**
     * Overridden to do nothing in a multiplot.
     */
    virtual void DrawBackground(ChartDC& cdc, wxRect rc) {}; // Does nothing in a multi plot?

private:
    void CalcSubplotRects();

    PlotArray m_subPlots;

    int m_rows;
    int m_cols;
    wxCoord m_horizGap;
    wxCoord m_vertGap;
};

#endif /*MULTIPLOT_H_*/
