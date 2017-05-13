/////////////////////////////////////////////////////////////////////////////
// Name:    ohlcrenderer.cpp
// Purpose: OHLC renderer implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/ohlc/ohlcrenderer.h>
#include <wx/ohlc/ohlcplot.h>

class DefaultOHLCColourer : public OHLCColourer
{
public:
    DefaultOHLCColourer();
    virtual ~DefaultOHLCColourer();

    virtual wxColor GetColour (int step);
};

DefaultOHLCColourer::DefaultOHLCColourer()
{
}

DefaultOHLCColourer::~DefaultOHLCColourer()
{
}

wxColor DefaultOHLCColourer::GetColour (int WXUNUSED (step))
{
    return *wxBLACK;
}

//
// OHLCRenderer
//

OHLCRenderer::OHLCRenderer()
{
    m_colourer = new DefaultOHLCColourer();
}

OHLCRenderer::~OHLCRenderer()
{
    wxDELETE (m_colourer);
}

void OHLCRenderer::SetColourer (OHLCColourer *colourer)
{
    wxREPLACE (m_colourer, colourer);
}

OHLCColourer *OHLCRenderer::GetColourer()
{
    return m_colourer;
}

double OHLCRenderer::GetMax(const Dataset* d, size_t dimension) const
{
    BiDataSet* dataset = wxDynamicCast(d, BiDataSet);
    wxASSERT(dataset && dataset->GetSeriesCount() && dataset->GetCount(0));
 
    if (dimension == 1)
    {
        double max = dataset->GetPointData(0, 0, dimension).As<OHLCItem>().high;
        
        for (size_t ser = 0; ser < dataset->GetSeriesCount(); ser++)
        {
            for (size_t pt = 0; pt < dataset->GetCount(ser); pt++)
                max = wxMax(max, dataset->GetPointData(ser, pt, dimension).As<OHLCItem>().high);
        }
        
        return max; 
    }
    else
    {
        double max = dataset->GetPointData(0, 0, dimension).As<wxDateTime>().GetTicks();
        
        for (size_t ser = 0; ser < dataset->GetSeriesCount(); ser++)
        {
            for (size_t pt = 0; pt < dataset->GetCount(ser); pt++)
                max = wxMax(max, dataset->GetPointData(ser, pt, dimension).As<wxDateTime>().GetTicks());
        }
        
        return max; 
    }
}


double OHLCRenderer::GetMin(const Dataset* d, size_t dimension) const
{
    BiDataSet* dataset = wxDynamicCast(d, BiDataSet);
    wxASSERT(dataset && dataset->GetSeriesCount() && dataset->GetCount(0));
 
    if (dimension == 1)
    {
        double min = dataset->GetPointData(0, 0, dimension).As<OHLCItem>().low;
        
        for (size_t ser = 0; ser < dataset->GetSeriesCount(); ser++)
        {
            for (size_t pt = 0; pt < dataset->GetCount(ser); pt++)
                min = wxMin(min, dataset->GetPointData(ser, pt, dimension).As<OHLCItem>().low);
        }
        
        return min; 
    }
    else
    {
        double min = dataset->GetPointData(0, 0, dimension).As<wxDateTime>().GetTicks();
        
        for (size_t ser = 0; ser < dataset->GetSeriesCount(); ser++)
        {
            for (size_t pt = 0; pt < dataset->GetCount(ser); pt++)
                min = wxMin(min, dataset->GetPointData(ser, pt, dimension).As<wxDateTime>().GetTicks());
        }
        
        return min; 
    }
}

