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
    data = val;
    m_hasData = true;
}

UniDataPoint::~UniDataPoint()
{

}

void UniDataPoint::Clear()
{
    data.MakeNull();
    m_hasData = false;
}

size_t UniDataPoint::GetDimensionCount() const
{
    return 1;
}

const wxAny& UniDataPoint::GetDimensionData (size_t dimension) const
{
    wxASSERT (dimension == 0);
    return data;
}

double UniDataPoint::GetDimensionValue(size_t dimension) const
{
    wxASSERT (dimension == 0 && data.CheckType<double>());
    return data.As<double>();
}

double UniDataPoint::GetValue() const
{
    wxASSERT_MSG (data.CheckType<double>(), "GetValue() called on non-double data");
    return data.As<double>();
}

void UniDataPoint::SetDimensionData(size_t dimension, const wxAny& d)
{
    wxASSERT (dimension == 0);
    data = d;
}

void UniDataPoint::SetDimensionValue(size_t dimension, double val)
{
    wxASSERT (dimension == 0 && data.CheckType<double>());
    data = val;
}

void UniDataPoint::SetValue(double val)
{
    data = val;
    m_hasData = true;
}

/***************************************
 * BI DATA POINT
 ***************************************/
BiDataPoint::BiDataPoint()
{
}

BiDataPoint::BiDataPoint (double f, double s, const wxString& comment)
    : DataPoint (comment)
{
    first = f;
    second = s;
    m_comment = comment;
    m_hasData = true;
}

BiDataPoint::BiDataPoint(const wxAny& f, const wxAny& s, const wxString& comment)
{
    first = f;
    second = s;
    m_comment = comment;
    m_hasData = true;
}

BiDataPoint::~BiDataPoint()
{
}

void BiDataPoint::Clear()
{
    first.MakeNull();
    second.MakeNull();
    m_hasData = false;
}

size_t BiDataPoint::GetDimensionCount() const
{
    return 2;
}

const wxAny& BiDataPoint::GetDimensionData(size_t dimension) const
{
    wxASSERT (dimension < 2);
    return dimension == 0 ? first : second;
}

double BiDataPoint::GetDimensionValue (size_t dimension) const
{
    wxASSERT (dimension < 2);
    wxASSERT (first.CheckType<double>());
    return dimension == 0 ? first.As<double>() : second.As<double>();
}

void BiDataPoint::GetValues (double& f, double& s) const
{
    wxASSERT_MSG (first.CheckType<double>(), "GetValues() called on non-double data");
    f = first.As<double>();
    s = second.As<double>();
}

void BiDataPoint::SetDimensionData(size_t dimension, const wxAny& data)
{
    wxASSERT (dimension < 2);
    
    if (dimension == 0)
        first = data;
    else
        second = data;  
}

void BiDataPoint::SetDimensionValue (size_t dimension, double val)
{
    wxASSERT (dimension < 2 && first.CheckType<double>());

    if (dimension == 0)
        first = val;
    else
        second = val;
}

void BiDataPoint::SetValues (double f, double s)
{
    first = f;
    second = s;
}


/***************************************
 * N-ARY DATA POINT
 ***************************************/
NaryDataPoint::NaryDataPoint(const wxVector<double>& dat, const wxString& comment)
    : DataPoint (comment)
{
    for (size_t i = 0; i < dat.size(); i++)
        data.push_back(wxAny(dat[i]));
}

NaryDataPoint::NaryDataPoint(const wxVector<wxAny>& dat, const wxString& comment)
    : DataPoint (comment)
{
    data = dat;
    /*
    for (size_t i = 0; i < dat.size(); i++)
        data.push_back(dat[i]);
    */
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

const wxAny& NaryDataPoint::GetDimensionData(size_t dimension) const
{
    return data[dimension];
}

double NaryDataPoint::GetDimensionValue(size_t dimension) const
{
    wxASSERT (data[dimension].CheckType<double>());
    return data[dimension].As<double>();
}

bool NaryDataPoint::HasData() const
{
    return data.size() > 0 ? true : false;
}

void NaryDataPoint::SetData(const wxVector<wxAny>& d)
{
    data = d;
}

void NaryDataPoint::SetData(const wxVector<double>& d)
{
    data.clear();

    for (size_t i = 0; i < d.size(); i++)
        data.push_back (d[i]);
}

void NaryDataPoint::SetDimensionData(size_t dimension, const wxAny& d)
{
    data[dimension] = d;   
}

void NaryDataPoint::SetDimensionValue(size_t dimension, double val)
{
    data[dimension] = val;
}
