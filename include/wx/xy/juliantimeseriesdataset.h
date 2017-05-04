/////////////////////////////////////////////////////////////////////////////
// Name:    JulianTimeSeriesDataset.h
// Purpose: An XY dataset where the X axis is a Julian Date
// Author:    Carsten Arnholm
// Created:    2010/08/19
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef TIMESERIESDATA_H
#define TIMESERIESDATA_H

#include <wx/dataset.h>
#include <wx/xy/xydataset.h>

struct TimePair
{
    TimePair(double f, double s) : first(f), second(s) {}
    double first;
    double second;
};

class WXDLLIMPEXP_FREECHART JulianTimeSeriesDataset : public XYDataset 
{
public:
    JulianTimeSeriesDataset();
    JulianTimeSeriesDataset(const wxVector<TimePair>& data);
    virtual ~JulianTimeSeriesDataset();

    virtual size_t GetSerieCount();

    virtual wxString GetSerieName(size_t serie);

    virtual size_t GetCount(size_t serie);

    virtual double GetX(size_t index, size_t serie);

    virtual double GetY(size_t index, size_t serie);

    void clear();
    void reserve(size_t length);
    void push_back(const TimePair& tvpair);

private:
    wxVector<TimePair> m_data;
};

#endif // TIMESERIESDATA_H

