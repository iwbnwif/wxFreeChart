/////////////////////////////////////////////////////////////////////////////
// Name:    barrenderer.cpp
// Purpose: bar renderer implementation
// Author:    Moskvichev Andrey V.
// Created:    14.11.2008
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/render/barrenderer.h"

//
// bar types
//

BarType::BarType(double base)
{
    m_base = base;
}

BarType::~BarType()
{
}

void BarType::Draw(BarRenderer* barRenderer, wxDC& dc, wxRect rc, 
                    Axis* horizAxis, Axis* vertAxis, 
                    bool vertical, size_t item, UniDataSet* dataset)
{
    for(size_t n = 0; n < dataset->GetSeriesCount(); n++)
    {
        // bar geometry params
        int width;
        wxCoord shift;
        double base, value;

        // get bar geometry
        GetBarGeometry(dataset, item, n, width, shift, base, value);

        double xBase, yBase;
        double xVal, yVal;

        if (vertical) {
            xBase = xVal = item;
            yBase = base;
            yVal = value;
        }
        else {
            xBase = base;
            yBase = yVal = item;
            xVal = value;
        }

        // transform base and value to graphics coordinates
        wxCoord xBaseG = horizAxis->ToGraphics(dc, rc.x, rc.width, xBase);
        wxCoord yBaseG = vertAxis->ToGraphics(dc, rc.y, rc.height, yBase);
        wxCoord xG = horizAxis->ToGraphics(dc, rc.x, rc.width, xVal);
        wxCoord yG = vertAxis->ToGraphics(dc, rc.y, rc.height, yVal);

        wxRect rcBar;
        if (vertical) {
            xBaseG += shift;
            xG += shift;

            rcBar.x = wxMin(xBaseG, xG);
            rcBar.y = wxMin(yBaseG, yG);
            rcBar.width = width;
            rcBar.height = ABS(yBaseG - yG);
        }
        else {
            yBaseG += shift;
            yG += shift;

            rcBar.x = wxMin(xBaseG, xG);
            rcBar.y = wxMin(yBaseG, yG);
            rcBar.width = ABS(xBaseG - xG);
            rcBar.height = width;
        }

        // draw bar
        AreaDraw *barDraw = barRenderer->GetBarDraw(n);
        barDraw->Draw(dc, rcBar);
    }
}

double BarType::GetMinValue(DataSet* dataset) const
{
    double min = dataset->GetMinValue1(0);

    return wxMin(min, m_base);
}

double BarType::GetMaxValue(DataSet* dataset) const
{
    double max = dataset->GetMaxValue1(0);

    return wxMax(max, m_base);
}

//
// NormalBarType
//

NormalBarType::NormalBarType(int barWidth, int serieGap, double base)
: BarType(base)
{
    m_barWidth = barWidth;
    m_serieGap = serieGap;
}

NormalBarType::~NormalBarType()
{
}

void NormalBarType::GetBarGeometry(UniDataSet *dataset, size_t item, size_t series, int &width, wxCoord &shift, double &base, double &value)
{
    width = m_barWidth;

    const int seriesCount = dataset->GetSeriesCount();
    if (seriesCount > 1)
        shift = series * (m_barWidth + m_serieGap) - (m_serieGap * (seriesCount - 1) + m_barWidth);

    else
        shift = -m_barWidth / 2;

    base = m_base;
    value = dataset->GetValue(series, item);
}

//
// StackedBarType
//

StackedBarType::StackedBarType(int barWidth, double base)
: BarType(base)
{
    m_barWidth = barWidth;
}

StackedBarType::~StackedBarType()
{
}

void StackedBarType::GetBarGeometry(UniDataSet* dataset, size_t item, size_t series, int& width, wxCoord& shift, double& base, double& value)
{
    width = m_barWidth;
    shift = -m_barWidth / 2;
    
    // Find the end of the previous bar segment.
    base = (series >= 1) ? dataset->GetValue(series - 1, item) : m_base;
    
    // Add the length of this segment.
    value = dataset->GetValue(series, item);
    if (series >= 1)
        value += base;
}

double StackedBarType::GetMinValue(DataSet* dataset) const
{
    return m_base;
}

double StackedBarType::GetMaxValue(DataSet* dataset) const
{
    double max = 0;

    // Implement a special version of GetMaxValue to take into account that the bars are stacked
    // and therefore the maximum value is the sum or all series for a given category.
    
    // For each category ...
    for (size_t pt = 0; pt < dataset->GetCount(0); pt++) 
    {
        double sum = m_base;

        // Accumulate all series values for this category.
        for (size_t ser = 0; ser < dataset->GetSeriesCount(); ser++)
            sum += dataset->InterpretAsValue(ser, pt, 0);

        // Build the maximum accumulated value across all categories.
        max = wxMax(max, sum);
    }

    return max;
}


//
// LayeredBarType
//

LayeredBarType::LayeredBarType(int initialBarWidth, double base)
: BarType(base)
{
    m_initialBarWidth = initialBarWidth;
}

LayeredBarType::~LayeredBarType()
{
}

void LayeredBarType::GetBarGeometry(UniDataSet* dataset, size_t item, size_t series, int &width, wxCoord &shift, double &base, double &value)
{
    width = (int) (m_initialBarWidth * (1 - series / (double)dataset->GetSeriesCount()));
    shift = -width / 2;
    base = m_base;
    value = dataset->GetValue(series, item);
}

//
// BarRenderer
//

IMPLEMENT_CLASS(BarRenderer, Renderer)

BarRenderer::BarRenderer(BarType *barType)
{
    m_barType = barType;
}

BarRenderer::~BarRenderer()
{
    wxDELETE(m_barType);
}

void BarRenderer::SetBarType(BarType *barType)
{
    wxREPLACE(m_barType, barType);
}

BarType *BarRenderer::GetBarType()
{
    return m_barType;
}

void BarRenderer::DrawLegendSymbol(wxDC &dc, wxRect rcSymbol, size_t serie)
{
    AreaDraw *barDraw = GetBarDraw(serie);
    barDraw->Draw(dc, rcSymbol);
}

void BarRenderer::SetBarDraw(size_t serie, AreaDraw *areaDraw)
{
    m_barDraws.SetAreaDraw(serie, areaDraw);
}

AreaDraw *BarRenderer::GetBarDraw(size_t serie)
{
    AreaDraw *barDraw = m_barDraws.GetAreaDraw(serie);
    if (barDraw == NULL) 
    {
        // barDraw = new FillAreaDraw(GetDefaultColour(serie), GetDefaultColour(serie));
        barDraw = new FillAreaDraw(*wxTRANSPARENT_PEN, GetDefaultColour(serie));

        m_barDraws.SetAreaDraw(serie, barDraw);
    }
    return barDraw;
}

void BarRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, UniDataSet* dataset)
{
    for (size_t n = 0; n < dataset->GetSeries(0)->GetCount(); n++) {
        m_barType->Draw(this, dc, rc, horizAxis, vertAxis, vertical, n, dataset);
    }
}

double BarRenderer::GetMinValue(DataSet* dataset, size_t dimension) const
{
    return m_barType->GetMinValue(dataset);
}

double BarRenderer::GetMaxValue(DataSet* dataset, size_t dimension) const
{
    return m_barType->GetMaxValue(dataset);
}
