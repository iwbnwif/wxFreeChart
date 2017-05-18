/////////////////////////////////////////////////////////////////////////////
// Name:    multiplot.cpp
// Purpose: multiplot implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/plot/multiplot.h>

#include "wx/arrimpl.cpp"

#define FOREACH_SUBPLOT(index, subPlots) \
    for (size_t index = 0; index < subPlots.Count(); index++)

WX_DEFINE_EXPORTED_OBJARRAY(PlotArray)


MultiPlot::MultiPlot(int rows, int cols, wxCoord horizGap, wxCoord vertGap)
{
    wxASSERT_MSG(rows > 0 && cols > 0, "There must be at least one row and one column");
    
    m_rows = rows;
    m_cols = cols;
    m_horizGap = horizGap;
    m_vertGap = vertGap;
}

MultiPlot::~MultiPlot()
{
    FOREACH_SUBPLOT(n, m_subPlots) {
        Plot *plot = m_subPlots[n];
        wxDELETE(plot);
    }
}

void MultiPlot::PlotNeedRedraw(Plot *WXUNUSED(plot))
{
    // FirePlotNeedRedraw();
}

bool MultiPlot::HasData()
{
    return (m_subPlots.Count() != 0);
}

void MultiPlot::DrawData(ChartDC& cdc, wxRect rc)
{
    wxCHECK_RET(m_rows != 0 || m_cols != 0, wxT("row and column count = 0"));
    
    // Note: This method used to also calculate the plot rectangle size but that
    // is now handled by CalcSubplotRects in response to a resize event. The old
    // code may have automatically calculated the number of rows for a given number
    // of columns and vice versa, however that wasn't documented or used in the demos.

    FOREACH_SUBPLOT(n, m_subPlots)
        m_subPlots[n]->Draw(cdc, wxRect(0, 0, 0, 0));
}

void MultiPlot::CalcSubplotRects()
{
    wxCoord subWidth = (m_rect.width - (m_horizGap * (m_cols - 1))) / m_cols;
    wxCoord subHeight = (m_rect.height - (m_vertGap * (m_rows - 1))) / m_rows;
    
    size_t index = 0;

    for (int row = 0; row < m_rows; row++)
    {
        for (int col = 0; col < m_cols; col++)
        {
            wxRect subRect;
            subRect.SetLeft((col * (subWidth + m_horizGap)) + m_rect.x);
            subRect.SetWidth(subWidth);
            subRect.SetTop((row * (subHeight + m_vertGap)) + m_rect.y);
            subRect.SetHeight(subHeight);
            
            if (index < m_subPlots.GetCount())
                m_subPlots[index++]->SetPlotRect(subRect);
        }       
    }
}
