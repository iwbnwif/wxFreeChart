/////////////////////////////////////////////////////////////////////////////
// Name:    barplot.h
// Purpose: bar plot declaration
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef BARPLOT_H_
#define BARPLOT_H_

#include <wx/dataset.h>
#include <wx/plot/xyplot.h>

enum BarPlotOrientation
{
    BARPLOT_HORIZONTAL,
    BARPLOT_VERTICAL
};

/**
 * Plot for displaying histograms with values at one axis and
 * category names at other.
 */
class WXDLLIMPEXP_FREECHART BarPlot : public XYPlot
{
public:
    BarPlot(BarPlotOrientation orientation = BARPLOT_VERTICAL);
    virtual ~BarPlot();

protected:
    virtual bool AcceptAxis(Axis *axis);

    virtual bool AcceptDataset(DataSet *dataset);

    virtual void DrawDatasets(wxDC &dc, wxRect rc);
    
    /**
     * Override of base class to implement simple tooltip functionality for bar charts.
     * @param event Details of the mouse motion.
     */
    virtual void OnMouseMove(wxMouseEvent& event) wxOVERRIDE;
    
    BarPlotOrientation m_orientation;
};

#endif /*BARPLOT_H_*/
