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

bool DateAxis::AcceptDataset(Dataset *dataset)
{
    return true;
}

bool DateAxis::UpdateBounds()
{
    size_t dateCount = 0;

    for (size_t n = 0; n < m_datasets.Count(); n++) 
    {
        Dataset* dataset = m_datasets[n];

        size_t count = dataset->GetCount(0);
        dateCount = wxMax(dateCount, count);
    }

    if (dateCount != m_dateCount) 
    {
        m_dateCount = dateCount;
        if (dateCount)
            m_hasLabels = true;
        else
            m_hasLabels = false;
        return true;
    }
    else
        return false;
}

wxSize DateAxis::GetLongestLabelExtent(wxDC &dc)
{
    dc.SetFont(GetLabelTextFont());

    wxSize maxExtent(0, 0);

    for (int step = 0; !IsEnd(step); step++) {
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
    const Dataset* const dataset = GetDataset(0);
    
    minValue = dataset->GetMinValue(false);
    maxValue = dataset->GetMaxValue(false);
}

double DateAxis::GetValue(size_t step)
{
    // Dates must always be in the first dimension of any data point.
    DataSet* dataset = wxDynamicCast(m_datasets[0], DataSet);
    wxASSERT(dataset && dataset->GetPointData(0, step, 0).CheckType<wxDateTime>());
    
    // Retrieve the wxAny object for this data point and convert to a date string.
    const wxDateTime& dt = dataset->GetPointData(0, step, 0).As<wxDateTime>();

    return dt.GetTicks();
}

void DateAxis::GetLabel(size_t step, wxString &label)
{
    // Dates must always be in the first dimension of any data point.
    DataSet* dataset = wxDynamicCast(m_datasets[0], DataSet);
    wxASSERT(dataset && dataset->GetPointData(0, step, 0).CheckType<wxDateTime>());
    
    // Retrieve the wxAny object for this data point and convert to a date string.
    wxDateTime dt = dataset->GetPointData(0, step, 0).As<wxDateTime>();
    label = dt.Format(m_dateFormat);
}

bool DateAxis::IsEnd(size_t step)
{
    return step >= m_dateCount;
}
