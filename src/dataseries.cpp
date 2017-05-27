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
