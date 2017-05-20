/////////////////////////////////////////////////////////////////////////////
// Name:        dataeeries.cpp
// Purpose:     Default data series classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dataseries.h>


DataSeries::DataSeries(const wxString& name)
{
    
}

DataSeries::~DataSeries()
{
    
}

const wxString& DataSeries::GetName()
{
    return m_name;
}

void DataSeries::SetName(const wxString& name)
{
}

void DataSeries::AddPoint(DataPoint* dataPoint)
{
    m_points.push_back(wxSharedPtr<DataPoint>(dataPoint));
}

void DataSeries::Clear()
{
    m_points.clear();
}

const size_t DataSeries::GetSize()
{
    return m_points.size();
}

wxSharedPtr<DataPoint> DataSeries::GetPoint(size_t index)
{
    return m_points[index];
}

#ifdef DONOTUSE
UniDataSeries::UniDataSeries(const wxString& name)
: DataSeries(name)
{
}

UniDataSeries::UniDataSeries(const wxVector<UniDataPoint>& data, const wxString& name)
: DataSeries(name)
{
}

UniDataSeries::~UniDataSeries()
{
}

const size_t UniDataSeries::GetCount()
{
    return m_data.size();
}

UniDataPoint& UniDataSeries::GetData(size_t index)
{
    return m_data.at(index);
}

BiDataSeries::BiDataSeries(const wxString& name)
: DataSeries(name)
{
}

BiDataSeries::BiDataSeries(const wxVector<UniDataPoint>& data, const wxString& name)
: DataSeries(name)
{
}

BiDataSeries::~BiDataSeries()
{
}

const size_t BiDataSeries::GetCount()
{
    return m_data.size();
}

NaryDataSeries::NaryDataSeries(const wxString& name)
: DataSeries(name)
{
}

NaryDataSeries::NaryDataSeries(const wxVector<UniDataPoint>& data, const wxString& name)
: DataSeries(name)
{
}

NaryDataSeries::~NaryDataSeries()
{
}

const size_t NaryDataSeries::GetCount()
{
    return m_data.size();
}

#endif
