/////////////////////////////////////////////////////////////////////////////
// Name:    dateaxis.cpp
// Purpose: date axis implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/dateaxis.h>
#include <wx/dataset1.h>

IMPLEMENT_CLASS(DateAxis, Axis)

DateAxis::DateAxis(AXIS_LOCATION location)
: NumberAxis(location)
{
    m_dateFormat = wxT("%d %m");
    m_dateCount = 0;
}

DateAxis::~DateAxis()
{
}

bool DateAxis::AcceptDataset(DataSet *dataset)
{
    return true;
}

bool DateAxis::UpdateBounds()
{
    wxASSERT(m_datasets[0]);

    m_dateCount = m_datasets[0]->GetSeriesSize(0);
    
    if (m_dateCount > 0)
    {
        m_minValue = m_datasets[0]->GetMinValue1(0);
        m_maxValue = m_datasets[0]->GetMaxValue1(0);

        m_hasLabels = true;
    }
    else
        m_hasLabels = false;

    return m_hasLabels;
}

wxSize DateAxis::GetLongestLabelExtent(wxDC &dc)
{
    dc.SetFont(GetLabelTextFont());

    wxSize maxExtent(0, 0);

    for (size_t step = 0; !IsEnd(step); step++) {
        wxString label;
        GetLabel(step, label);

        wxSize labelExtent = dc.GetTextExtent(label);
        maxExtent.x = wxMax(maxExtent.x, labelExtent.x);
        maxExtent.y = wxMax(maxExtent.y, labelExtent.y);
    }

    return maxExtent;
}

void DateAxis::GetDataBounds(double &minValue, double &maxValue) const
{
    minValue = m_minValue; 
    maxValue = m_maxValue; 
}

double DateAxis::GetValue(size_t step)
{
    // Dates must always be in the first dimension of any data point.
    DataSet* dataset = wxDynamicCast(m_datasets[0], DataSet);
    wxASSERT(dataset);
    
    return dataset->InterpretAsValue(0, step, 0);
}

void DateAxis::GetLabel(size_t step, wxString &label)
{
    // Dates must always be in the first dimension of any data point.
    DataSet* dataset = wxDynamicCast(m_datasets[0], DataSet);
    wxASSERT(dataset);
    
    // Retrieve the wxAny object for this data point and convert to a date string.
    wxDateTime dt = dataset->InterpretAsAny(0, step, 0).As<wxDateTime>();
    label = dt.Format(m_dateFormat);
}

bool DateAxis::IsEnd(size_t step)
{
    return step >= m_dateCount;
}
