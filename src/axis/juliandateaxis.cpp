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
   label = dt.FormatISODate(); // Format(m_dateFormat);
   wxLogMessage(dt.FormatISODate());
}

bool JulianDateAxis::UpdateBounds()
{
    NumberAxis::UpdateBounds();
    
    wxLogMessage("%f", m_labelInterval);
    m_labelInterval = 1.0;
    m_labelCount *= 5.0;
    
    return true;
}
