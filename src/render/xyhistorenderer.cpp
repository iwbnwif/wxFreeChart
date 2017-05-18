/////////////////////////////////////////////////////////////////////////////
// Name:    xyhistorenderer.cpp
// Purpose: xy histogram renderer implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xyhistorenderer.h>
#include <wx/art.h>

IMPLEMENT_CLASS(XYHistoRenderer, XYRenderer)

XYHistoRenderer::XYHistoRenderer(int barWidth, bool vertical)
{
    m_barWidth = barWidth;
    m_vertical = vertical;
    m_serieShift = barWidth + 2; // XXX temporary!
}

XYHistoRenderer::~XYHistoRenderer()
{
}

void XYHistoRenderer::DrawBar(int serie, wxDC &dc, wxRect rcData, wxCoord x, wxCoord y)
{
    wxRect rcBar;

    if (m_vertical) {
        rcBar.x = x - m_barWidth / 2;
        rcBar.y = y;
        rcBar.width = m_barWidth;
        rcBar.height = rcData.height - y + rcData.y;
    }
    else {
        rcBar.x = rcData.x;
        rcBar.y = y - m_barWidth / 2;
        rcBar.width = x - rcData.x;
        rcBar.height = m_barWidth;
    }

    AreaDraw *barArea = GetBarArea(serie);
    wxCHECK_RET(barArea != NULL, wxT("No bar area draw"));
    barArea->Draw(dc, rcBar);
}

void XYHistoRenderer::Draw(wxDC&dc, const wxRect& rc, Axis* xAxis, Axis* yAxis, BiDataSet* dataset)
{
    FOREACH_SERIE(serie, dataset) {
        FOREACH_DATAITEM(n, serie, dataset) {
            double xVal;
            double yVal;

            if (m_vertical) {
                xVal = dataset->GetFirst(serie, n);
                yVal = dataset->GetSecond(serie, n);
            }
            else {
                xVal = dataset->GetSecond(serie, n);
                yVal = dataset->GetFirst(serie, n);
            }

            if (!xAxis->IsVisible(xVal) ||
                    !yAxis->IsVisible(yVal)) {
                continue;
            }

            wxCoord x = xAxis->ToGraphics(dc, rc.x, rc.width, xVal);
            wxCoord y = yAxis->ToGraphics(dc, rc.y, rc.height, yVal);

            DrawBar(serie, dc, rc, x, y);
        }
    }
}

void XYHistoRenderer::SetBarArea(size_t serie, AreaDraw *barArea)
{
    m_barAreas.SetAreaDraw(serie, barArea);
}

AreaDraw *XYHistoRenderer::GetBarArea(size_t serie)
{
    return m_barAreas.GetAreaDraw(serie);
}

void XYHistoRenderer::NeedRedraw(DrawObject *WXUNUSED(obj))
{
    // FireNeedRedraw();
}
