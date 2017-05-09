/////////////////////////////////////////////////////////////////////////////
// Name:        datapoint.h
// Purpose:     Default data point classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/datapoint.h>

/***************************************
 * DATA POINT
 ***************************************/
DataPoint::DataPoint (const wxString& comment)
{
    m_comment = comment;
    m_hasData = false;
}

DataPoint::~DataPoint()
{
}

const wxString& DataPoint::GetComment() const
{
    return m_comment;
}

bool DataPoint::HasData() const
{
    return m_hasData;
}

void DataPoint::SetComment (const wxString& comment)
{
    m_comment = comment;
}

/***************************************
 * UNI DATA POINT
 ***************************************/
UniDataPoint::UniDataPoint()
{
}

UniDataPoint::UniDataPoint (double val, const wxString& comment)
    : DataPoint (comment)
{
    value = val;
    m_hasData = true;
}

UniDataPoint::~UniDataPoint()
{

}

void UniDataPoint::Clear()
{
    value = 0;
    m_hasData = false;
}

size_t UniDataPoint::GetDimensionCount() const
{
    return 1;
}

double UniDataPoint::GetDimensionValue(size_t dimension) const
{
    wxASSERT (dimension == 0);
    return value;
}

double UniDataPoint::GetValue() const
{
    return value;
}

void UniDataPoint::SetDimensionValue(size_t dimension, double val)
{
    wxASSERT (dimension == 0);
    value = val;
}

void UniDataPoint::SetValue(double val)
{
    value = val;
    m_hasData = true;
}

/***************************************
 * BI DATA POINT
 ***************************************/
BiDataPoint::BiDataPoint()
{
}

BiDataPoint::BiDataPoint (double first, double second, const wxString& comment)
    : DataPoint (comment)
{
}

BiDataPoint::~BiDataPoint()
{
}

void BiDataPoint::Clear()
{
    first = 0;
    second = 0;
    m_hasData = false;
}

size_t BiDataPoint::GetDimensionCount() const
{
    return 2;
}

double BiDataPoint::GetDimensionValue(size_t dimension) const
{
    return dimension == 0 ? first : second;
}

void BiDataPoint::GetValues(double& f, double& s) const
{
    f = first;
    s = second;
}

void BiDataPoint::SetDimensionValue(size_t dimension, double val)
{
    if (dimension == 0)
        first = val;
    else
        second = val;
}

void BiDataPoint::SetValues(double f, double s)
{
    first = f;
    second = s;
}

/***************************************
 * N-ARY DATA POINT
 ***************************************/
NaryDataPoint::NaryDataPoint (const wxVector<double>& dat, const wxString& comment)
    : DataPoint (comment)
{

}

NaryDataPoint::~NaryDataPoint()
{
}

void NaryDataPoint::Clear()
{
    data.clear();
}

size_t NaryDataPoint::GetDimensionCount() const
{
    return data.size();
}

double NaryDataPoint::GetDimensionValue (size_t dimension) const
{
    return data.at(dimension);
}

bool NaryDataPoint::HasData() const
{
    return data.size() > 0 ? true : false; 
}

void NaryDataPoint::SetData(const wxVector<double>& d)
{
    data = d;
}

void NaryDataPoint::SetDimensionValue(size_t dimension, double val)
{
    data[dimension] = val;
}
