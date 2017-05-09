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

/***************************************
 * DATA SET
 ***************************************/
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

/***************************************
 * UNI DATA SET
 ***************************************/
UniDataSet::UniDataSet (const wxString& name)
{
}

UniDataSet::~UniDataSet()
{
}

void UniDataSet::AddCategory(const wxAny& category)
{
    m_baseSeries.push_back(category);
}

size_t UniDataSet::GetBaseCount()
{
    return m_baseSeries.size();
}

const wxVector<wxAny>& UniDataSet::GetBaseSeries() const
{
    return m_baseSeries;
}

const wxAny& UniDataSet::GetBaseValue(size_t index) const
{
    return m_baseSeries[index];
}

double UniDataSet::GetMaxValue(bool vertical)
{
    double max = GetValue(0, 0);
    
    for (size_t ser = 0; ser < GetSerieCount(); ser++)
    {
        for (size_t pt = 0; pt < GetCount(ser); pt++)
            max = wxMax(max, GetValue(ser, pt));
    }
    
    return max;       
}

double UniDataSet::GetMinValue(bool vertical)
{
    double min = GetValue(0, 0);
    
    for (size_t ser = 0; ser < GetSerieCount(); ser++)
    {
        for (size_t pt = 0; pt < GetCount(ser); pt++)
            min = wxMin(min, GetValue(ser, pt));
    }
    
    return min;       
}

double UniDataSet::GetValue(size_t series, size_t index) const
{
    return m_series[series]->GetPoint(index).get()->GetDimensionValue(0);
}


/***************************************
 * BI DATA SET
 ***************************************/
BiDataSet::BiDataSet (const wxString& name)
{
}

BiDataSet::~BiDataSet()
{
}

/***************************************
 * NARY DATA SET
 ***************************************/
NaryDataSet::NaryDataSet (const wxString& name)
{
}

NaryDataSet::~NaryDataSet()
{
}
