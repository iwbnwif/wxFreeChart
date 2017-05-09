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

const wxString& DataPoint::GetComment()
{
    return m_comment;
}

bool DataPoint::HasData()
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

UniDataPoint::UniDataPoint (const wxAny& val, const wxString& comment)
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
    value.MakeNull();
    m_hasData = false;
}

const size_t UniDataPoint::GetDimensionCount()
{
    return 1;
}

const wxAny& UniDataPoint::GetDimensionValue (const size_t dimension)
{
    return value;
}

const wxAny& UniDataPoint::GetValue()
{
    return value;
}

void UniDataPoint::SetDimensionValue (const size_t dimension, const wxAny& val)
{
    wxASSERT (dimension == 0);
    value = val;
}

void UniDataPoint::SetValue (const wxAny& val)
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

BiDataPoint::BiDataPoint (const wxAny& first, const wxAny& second, const wxString& comment)
    : DataPoint (comment)
{
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

const size_t BiDataPoint::GetDimensionCount()
{
    return 2;
}

const wxAny& BiDataPoint::GetDimensionValue (const size_t dimension)
{
    return dimension == 0 ? first : second;
}

void BiDataPoint::GetValues(wxAny& fst, wxAny& snd)
{
    first = fst;
    second = snd;
}

void BiDataPoint::SetDimensionValue (const size_t dimension, const wxAny& val)
{
    if (dimension == 0)
        first = val;
    else
        second = val;
}

void BiDataPoint::SetValue (const wxAny& fst, const wxAny& snd)
{
    first = fst;
    second = snd;
}

/***************************************
 * N-ARY DATA POINT
 ***************************************/
NaryDataPoint::NaryDataPoint (const wxVector<wxAny>& dat, const wxString& comment)
    : DataPoint (comment)
{

}

NaryDataPoint::~NaryDataPoint()
{
}

void NaryDataPoint::Clear()
{
    for (size_t i = 0; i < data.size(); i++)
        data[i].MakeNull();
}

const size_t NaryDataPoint::GetDimensionCount()
{
    return data.size();
}

const wxAny& NaryDataPoint::GetDimensionValue (const size_t dimension)
{
    return data.at(dimension);
}

bool NaryDataPoint::HasData()
{
    // Note: m_hasData is not used here. If any dimensions do not have valid data
    // then return false, otherwise return true.
    for (size_t i = 0; i < data.size(); i++)
        {
            if (data[i].IsNull())
                return false;
        }
        
    return true; 
}

void NaryDataPoint::SetData (const wxVector<wxAny>& dat)
{
    data = dat;
}

void NaryDataPoint::SetDimensionValue (const size_t dimension, const wxAny& val)
{
    data.at(0) = val;
}
