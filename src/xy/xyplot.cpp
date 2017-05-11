/////////////////////////////////////////////////////////////////////////////
// Name:    xyplot.cpp
// Purpose: xy plot implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xyplot.h>

XYPlot::XYPlot()
{
}

XYPlot::~XYPlot()
{
}

bool XYPlot::AcceptAxis(Axis *WXUNUSED(axis))
{
    return true;
}

bool XYPlot::AcceptDataset(Dataset *dataset)
{
    return (wxDynamicCast(dataset, BiDataSet) != NULL);
}

void XYPlot::DrawDatasets(wxDC &dc, wxRect rc)
{
    for (size_t nData = 0; nData < GetDatasetCount(); nData++) 
    {
        BiDataSet* dataset = wxDynamicCast(GetDataset(nData), BiDataSet);
        wxASSERT(dataset);

        DrawXYDataset(dc, rc, dataset);
    }
}

void XYPlot::DrawXYDataset(wxDC& dc, const wxRect& rc, BiDataSet* dataset)
{
    XYRenderer* renderer = dataset->GetRenderer();
    wxASSERT(renderer);

    Axis* yAxis = GetDatasetVerticalAxis(dataset);
    Axis* xAxis = GetDatasetHorizontalAxis(dataset);
    wxASSERT(yAxis && xAxis);

    renderer->Draw(dc, rc, xAxis, yAxis, dataset);
}

/*
#include <wx/xy/xysimpledataset.h>

void XYPlot::OnMouseMove(wxMouseEvent& event)
{
    // wxRealPoint mousetodata = 
    for (size_t set = 0; set < GetDatasetCount(); set++)
    {
        XYSimpleDataset* dataset = static_cast<XYSimpleDataset*>(GetDataset(set));

        NumberAxis* xAxis = static_cast<NumberAxis*>(GetDatasetAxis(dataset, false));
        NumberAxis* yAxis = static_cast<NumberAxis*>(GetDatasetAxis(dataset, true));
        
        for (size_t ser = 0; ser < dataset->GetSerieCount(); ser++)
        {
            XYSerie* series = dataset->GetSerie(ser);
            
            wxMemoryDC dummy;
            double x = xAxis->ToData(dummy, m_rect.x, m_rect.GetWidth(), event.GetPosition().x);
            double y = yAxis->ToData(dummy, m_rect.y, m_rect.GetHeight(), event.GetPosition().y);
            
            for (size_t pt = 0; pt < series->GetCount(); pt++)
            {
                wxRealPoint point = series->GetPoint(pt);
                if (point.x < x + 2 &&
                    point.x > x - 2 &&
                    point.y < y + 2 &&
                    point.y > y - 2)
                {
                        std::cout << "Got a point in Dataset: " << set << ", Series: " << ser << ", Point Index: " << pt <<
                                        ", at Point (x,y): " << point.x << ", " << point.y << std::endl;
                }
            }
        }
    }
}
*/