/////////////////////////////////////////////////////////////////////////////
// Name:    movingaverage.cpp
// Purpose: moving average implementation
// Author:    Moskvichev Andrey V.
// Created:    2011/12/25
// Copyright:    (c) 2008-2011 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/render/movingaverage.h>
#include <wx/plot/ohlcplot.h>

IMPLEMENT_CLASS(MovingAverage, BiDataSet)

MovingAverage::MovingAverage(BiDataSet* dataset, int period)
{
    m_SourceDataset = dataset;
    m_period = period;

    m_SourceDataset->AddRef();
}

MovingAverage::~MovingAverage()
{
    SAFE_UNREF(m_SourceDataset);
}

size_t MovingAverage::GetSerieCount() const
{
    return 1;
}

size_t MovingAverage::GetSeriesSize(size_t WXUNUSED(serie)) const
{
    int count = m_SourceDataset->GetSeriesSize(0) - m_period + 1;
    if (count < 0) {
        count = 0; // period is larger than OHLC data
    }
    return count;
}

double MovingAverage::GetX(size_t index, size_t WXUNUSED(serie)) const
{
    return index + m_period - 1;
}

double MovingAverage::GetY(size_t index, size_t WXUNUSED(serie)) const
{
    wxCHECK_MSG(m_period != 0, 0, wxT("MovingAverage::GetX"));

    double sum = 0;

    for (size_t n = index; n < index + m_period; n++) 
    {
        const OHLCItem& item = m_SourceDataset->GetPointData(0, n, 1).As<OHLCItem>();

        sum += item.close;
    }
    
    return sum / m_period;
}

void MovingAverage::DatasetChanged(DataSet* WXUNUSED(dataset))
{
    DataSet::DatasetChanged();
}
