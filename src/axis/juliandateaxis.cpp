/////////////////////////////////////////////////////////////////////////////
// Name:    juliandateaxis.cpp
// Purpose: Axis declaration where the values are Julian Dates
// Author:    Carsten Arnholm
// Created:    2010/08/19
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/axis/juliandateaxis.h"
#include <wx/datetime.h>

JulianDateAxis::JulianDateAxis(AXIS_LOCATION location)
: NumberAxis(location)
{
}

JulianDateAxis::~JulianDateAxis()
{
}

void JulianDateAxis::SetDateFormat(const wxString& dateFormat)
{
   m_dateFormat = dateFormat;
}

void JulianDateAxis::GetLabel(size_t step, wxString &label)
{
    double value = GetValue(step);

    if (value == -0) {
        value = 0;
    }

   wxDateTime dt(value);
   label = dt.Format(m_dateFormat);
}

/*
 * Hack to change the interval to a single day, no matter what nice interval is calculated.
 * TODO: This is probably something that needs to be implemented properly for number axis.
 */
bool JulianDateAxis::UpdateBounds()
{
    NumberAxis::UpdateBounds();
    
    m_labelInterval = 1.0;
    m_labelCount = ((m_maxValue - m_minValue) / m_labelInterval) + 1;
    
    return true;
}
