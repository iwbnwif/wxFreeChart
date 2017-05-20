/////////////////////////////////////////////////////////////////////////////
// Name:    xyrenderer.h
// Purpose: xy renderer base class declaration
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYRENDERER_H_
#define XYRENDERER_H_

#include <wx/axis/axis.h>
#include <wx/dataset.h>
#include <wx/render/chartrenderer.h>

/**
 * Base class for all XYDataset renderers.
 */
class WXDLLIMPEXP_FREECHART XYRenderer : public Renderer
{
    DECLARE_CLASS(XYRenderer)
public:
    XYRenderer();
    virtual ~XYRenderer();

    /**
     * Base class for classes that render to an X-Y scatter plot.
     * @param dc The device context for the plot.
     * @param rc The rectangle that defines the boundaries of the plot.
     * @param xAxis A pointer to the X (horizontal) axis.
     * @param yAxis A pointer to the Y (vertical) axis.
     * @param dataset The dataset to be drawn by this renderer.
     */
    virtual void Draw(wxDC& dc, const wxRect& rc, Axis* xAxis, Axis* yAxis, BiDataSet* dataset) = 0;
    virtual double GetMax(const BiDataSet* dataset, size_t dimension) const;
    virtual double GetMin(const BiDataSet* dataset, size_t dimension) const;
};

#endif /*XYRENDERER_H_*/
