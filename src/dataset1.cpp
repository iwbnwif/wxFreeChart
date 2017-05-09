/////////////////////////////////////////////////////////////////////////////
// Name:        dataeet.cpp
// Purpose:     Default data set classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dataset1.h>

#include <wx/xy/xylinerenderer.h>


DataSet::DataSet (const wxString& name)
{
}

DataSet::~DataSet()
{

}

const wxString& DataSet::GetName()
{
    return m_name;
}

void DataSet::SetName (const wxString& name)
{
}

const wxSharedPtr<DataSeries> DataSet::GetSeries(size_t index)
{
    return m_series.at(index);
}

const size_t DataSet::GetSeriesCount()
{
    return m_series.size();
}

bool DataSet::AcceptRenderer (Renderer* r)
{
    return true;
}

size_t DataSet::GetCount (size_t serie)
{
    return m_series.at(serie)->GetCount();
}

size_t DataSet::GetSerieCount()
{
    return GetSeriesCount();
}

wxString DataSet::GetSerieName (size_t serie)
{
    return m_series.at(serie)->GetName();
}

void DataSet::AddSeries(DataSeries* series)
{
    m_series.push_back(wxSharedPtr<DataSeries>(series));
    
    // Each series added must have a corresponding renderer.
    // TODO: Create a NullRenderer class that does nothing.
    m_renderers.push_back(wxSharedPtr<Renderer>(new XYLineRenderer(true, false)));
}

void DataSet::SetSeriesRenderer(size_t series, Renderer* renderer)
{
    m_renderers[series] = (wxSharedPtr<Renderer>(renderer));
}

UniDataSet::UniDataSet (const wxString& name)
{
}

UniDataSet::~UniDataSet()
{
}

void UniDataSet::AddCategory(const wxAny& category)
{
    m_baseSeries.AddPoint(new UniDataPoint(category));
}

size_t UniDataSet::GetBaseCount()
{
    return m_baseSeries.GetCount();
}

DataSeries& UniDataSet::GetBaseSeries()
{
    return m_baseSeries;
}

const wxAny& UniDataSet::GetBaseValue(size_t index)
{
    return m_baseSeries.GetPointPtr(index).get()->GetDimensionValue(0);
}

double UniDataSet::GetMaxValue (bool vertical)
{
    return 100.0;
}

double UniDataSet::GetMinValue (bool vertical)
{
    return 0.0;
}

const wxAny& UniDataSet::GetValue(size_t series, size_t index)
{
    return m_series[series]->GetPointPtr(index).get()->GetDimensionValue(0);
}


BiDataSet::BiDataSet (const wxString& name)
{
}

BiDataSet::~BiDataSet()
{
}

NaryDataSet::NaryDataSet (const wxString& name)
{
}

NaryDataSet::~NaryDataSet()
{
}
