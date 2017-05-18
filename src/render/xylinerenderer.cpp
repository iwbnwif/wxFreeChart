/////////////////////////////////////////////////////////////////////////////
// Name:    xylinerenderer.cpp
// Purpose: XY line renderer implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xylinerenderer.h>

IMPLEMENT_CLASS(XYLineRendererBase, XYRenderer)
IMPLEMENT_CLASS(XYLineRenderer, XYLineRendererBase)
IMPLEMENT_CLASS(XYLineStepRenderer, XYLineRendererBase)

//
// XYLineRendererBase
//

XYLineRendererBase::XYLineRendererBase(bool drawSymbols, bool drawLines, int defaultPenWidth, wxPenStyle defaultPenStyle)
{
    m_defaultPenWidth = defaultPenWidth;
    m_defaultPenStyle = defaultPenStyle;
    m_drawSymbols = drawSymbols;
    m_drawLines = drawLines;
}

XYLineRendererBase::~XYLineRendererBase()
{
}

void XYLineRendererBase::SetSeriePen(size_t serie, wxPen *pen)
{
    m_seriePens[serie] = *pen;
}

wxPen *XYLineRendererBase::GetSeriePen(size_t serie)
{
    if (m_seriePens.find(serie) == m_seriePens.end()) {
        return wxThePenList->FindOrCreatePen(GetDefaultColour(serie), m_defaultPenWidth, m_defaultPenStyle);
    }
    return &m_seriePens[serie];
}

void XYLineRendererBase::SetSerieColour(size_t serie, wxColour *colour)
{
    SetSeriePen(serie, wxThePenList->FindOrCreatePen(*colour, m_defaultPenWidth, m_defaultPenStyle));
}

wxColour XYLineRendererBase::GetSerieColour(size_t serie)
{
    if (m_seriePens.find(serie) == m_seriePens.end()) {
        return GetDefaultColour(serie);
    }
    return m_seriePens[serie].GetColour();
}

void XYLineRendererBase::Draw(wxDC&dc, const wxRect& rc, Axis* xAxis, Axis* yAxis, BiDataSet* dataset)
{
  if(m_drawLines) {
    DrawLines(dc, rc, xAxis, yAxis, dataset);
  }

  if(m_drawSymbols) {
    DrawSymbols(dc, rc, xAxis, yAxis, dataset);
  }
}

void XYLineRendererBase::DrawLegendSymbol(wxDC &dc, wxRect rcSymbol, size_t serie)
{
    if (m_drawLines) {
        dc.SetPen(*GetSeriePen(serie));
        dc.DrawLine(rcSymbol.x, rcSymbol.y + rcSymbol.height / 2,
                rcSymbol.x + rcSymbol.width, rcSymbol.y + rcSymbol.height / 2);
    }

    if (m_drawSymbols) {
        wxColour colour = GetSerieColour(serie);
        Symbol *symbol = GetSerieSymbol(serie);

        symbol->Draw(dc, rcSymbol.x + rcSymbol.width / 2, rcSymbol.y + rcSymbol.height / 2, colour);
    }
}

void XYLineRendererBase::DrawSymbols(wxDC&dc, const wxRect& rc, Axis* xAxis, Axis* yAxis, BiDataSet* dataset)
{
  FOREACH_SERIE(serie, dataset) {
    Symbol *symbol = GetSerieSymbol(serie);
    wxColour color = GetSerieColour(serie);

    for(size_t n = 0; n < dataset->GetCount(serie); ++n) {
      double x = dataset->GetFirst(serie, n);
      double y = dataset->GetSecond(serie, n);

      if(xAxis->IsVisible(x) && yAxis->IsVisible(y)) {
        int xg = xAxis->ToGraphics(dc, rc.x, rc.width, x);
        int yg = yAxis->ToGraphics(dc, rc.y, rc.height, y);

        symbol->Draw(dc, xg, yg, color);
      }
    }
  }
}

double XYLineRendererBase::GetMax(const Dataset* d, size_t dimension) const
{
    BiDataSet* dataset = wxDynamicCast(d, BiDataSet);
    wxASSERT(dataset && dataset->GetSeriesCount() && dataset->GetCount(0));
    
    double max = dataset->InterpretAsValue(0, 0, dimension);
    
    for (size_t ser = 0; ser < dataset->GetSeriesCount(); ser++)
    {
        for (size_t pt = 0; pt < dataset->GetCount(ser); pt++)
            max = wxMax(max, dataset->InterpretAsValue(ser, pt, dimension));
    }
    
    return max; 
}

double XYLineRendererBase::GetMin(const Dataset* d, size_t dimension) const
{
    BiDataSet* dataset = wxDynamicCast(d, BiDataSet);
    wxASSERT(dataset && dataset->GetSeriesCount() && dataset->GetCount(0));

    double min = dataset->InterpretAsValue(0, 0, dimension);
    
    for (size_t ser = 0; ser < dataset->GetSeriesCount(); ser++)
    {
        for (size_t pt = 0; pt < dataset->GetCount(ser); pt++)
            min = wxMin(min, dataset->InterpretAsValue(ser, pt, dimension));
    }
    
    return dataset->GetInterpreter()->AsValue(min, dimension);
}



//
// XYLineRenderer
//

XYLineRenderer::XYLineRenderer(bool drawSymbols, bool drawLines, int defaultPenWidth, wxPenStyle defaultPenStyle)
: XYLineRendererBase(drawSymbols, drawLines, defaultPenWidth, defaultPenStyle)
{
}

XYLineRenderer::~XYLineRenderer()
{
}


void XYLineRenderer::DrawLines(wxDC&dc, const wxRect& rc, Axis* xAxis, Axis* yAxis, BiDataSet* dataset)
{
    FOREACH_SERIE(serie, dataset) 
    {
        if (dataset->GetCount(serie) < 2)
            continue;

        for (size_t n = 0; n < dataset->GetCount(serie) - 1; n++) 
        {
            double x0 = dataset->InterpretAsValue(serie, n, 0);
            double y0 = dataset->InterpretAsValue(serie, n, 1);
            double x1 = dataset->InterpretAsValue(serie, n + 1, 0);
            double y1 = dataset->InterpretAsValue(serie, n + 1, 1);

            // Check whether segment is visible.
            if (!xAxis->IntersectsWindow(x0, x1) &&
                !yAxis->IntersectsWindow(y0, y1)) 
                continue;

            ClipHoriz(xAxis, x0, y0, x1, y1);
            ClipHoriz(xAxis, x1, y1, x0, y0);
            ClipVert(yAxis, x0, y0, x1, y1);
            ClipVert(yAxis, x1, y1, x0, y0);

            // translate to graphics coordinates.
            wxCoord xg0, yg0;
            wxCoord xg1, yg1;

            xg0 = xAxis->ToGraphics(dc, rc.x, rc.width, x0);
            yg0 = yAxis->ToGraphics(dc, rc.y, rc.height, y0);
            xg1 = xAxis->ToGraphics(dc, rc.x, rc.width, x1);
            yg1 = yAxis->ToGraphics(dc, rc.y, rc.height, y1);

            wxPen *pen = GetSeriePen(serie);
            dc.SetPen(*pen);
            dc.DrawLine(xg0, yg0, xg1, yg1);
        }
    }
}

//
// XYLineStepRenderer
//

XYLineStepRenderer::XYLineStepRenderer(int defaultPenWidth, wxPenStyle defaultPenStyle)
: XYLineRendererBase(false, true, defaultPenWidth, defaultPenStyle)
{
}

XYLineStepRenderer::~XYLineStepRenderer()
{
}

void XYLineStepRenderer::DrawLines(wxDC&dc, const wxRect& rc, Axis* xAxis, Axis* yAxis, BiDataSet* dataset)
{
    FOREACH_SERIE(serie, dataset) {
        if (dataset->GetCount(serie) < 2) {
            continue;
        }

        // find first visible index
        size_t first = GetFirstVisibleIndex(xAxis, yAxis, dataset, serie);
        if (first == (size_t) -1) {
            continue; // nothing visible
        }

        // Set serie pen
        wxPen *pen = GetSeriePen(serie);
        dc.SetPen(*pen);

        // iterate until two points will be invisible
        for (size_t n = first; n < dataset->GetCount(serie) - 1; n++) {
            double x0 = dataset->GetFirst(serie, n);
            double y0 = dataset->GetSecond(serie, n);
            double x1 = dataset->GetFirst(serie, n + 1);
            double y1 = dataset->GetSecond(serie, n + 1);

            if (!xAxis->IntersectsWindow(x0, x1) ||
                    !yAxis->IntersectsWindow(y0, y1)) {
                break;
            }

            ClipHoriz(xAxis, x0, y0, x1, y1);
            ClipHoriz(xAxis, x1, y1, x0, y0);
            ClipVert(yAxis, x0, y0, x1, y1);
            ClipVert(yAxis, x1, y1, x0, y0);

            // translate to graphics coordinates.
            wxCoord xg0, yg0;
            wxCoord xg1, yg1;

            xg0 = xAxis->ToGraphics(dc, rc.x, rc.width, x0);
            yg0 = yAxis->ToGraphics(dc, rc.y, rc.height, y0);
            xg1 = xAxis->ToGraphics(dc, rc.x, rc.width, x1);
            yg1 = yAxis->ToGraphics(dc, rc.y, rc.height, y1);

            dc.DrawLine(xg0, yg0, xg1, yg1);
        }
    }
}

size_t XYLineStepRenderer::GetFirstVisibleIndex(Axis* xAxis, Axis* yAxis, BiDataSet* dataset, size_t serie)
{
    for (size_t n = 0; n < dataset->GetCount(serie) - 1; n++) {
        double x0 = dataset->GetFirst(serie, n);
        double y0 = dataset->GetSecond(serie, n);
        double x1 = dataset->GetFirst(serie, n + 1);
        double y1 = dataset->GetSecond(serie, n + 1);

        // check whether segment is visible
        if (xAxis->IntersectsWindow(x0, x1) ||
                yAxis->IntersectsWindow(y0, y1)) {
            return n;
        }
    }
    return (size_t) -1; // nothing visible
}
