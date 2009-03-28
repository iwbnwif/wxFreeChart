/////////////////////////////////////////////////////////////////////////////
// Name:	dateaxis.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/dateaxis.h>

IMPLEMENT_CLASS(DateAxis, Axis)

DateAxis::DateAxis(AXIS_LOCATION location)
: LabelAxis(location)
{
	m_dateFormat = wxT("%d %m");
}

DateAxis::~DateAxis()
{
}

bool DateAxis::AcceptDataset(Dataset *dataset)
{
	// Accepts only date/time dataset
	// and only one dataset
	return (wxDynamicCast(dataset, DateTimeDataset) != NULL)
		&& (m_datasets.GetSize() == 0);
}

void DateAxis::UpdateBounds()
{
	int dateCount = 0;

	for (int n = 0; n < m_datasets.GetSize(); n++) {
		DateTimeDataset *dataset = (DateTimeDataset *) m_datasets[n];

		int count = dataset->GetCount();
		dateCount = wxMax(dateCount, count);
	}

	if (dateCount != m_dateCount) {
		m_dateCount = dateCount;
		FireBoundsChanged();
	}
}

wxSize DateAxis::GetLongestLabelExtent(wxDC &dc)
{
	wxSize maxExtent(0, 0);

	for (int step = 0; ; step++) {
		if (IsEnd(step))
			break;

		wxString label;
		GetLabel(step, label);

		wxSize labelExtent = dc.GetTextExtent(label);
		maxExtent.x = wxMax(maxExtent.x, labelExtent.x);
		maxExtent.y = wxMax(maxExtent.y, labelExtent.y);
	}

	return maxExtent;
}

void DateAxis::GetDataBounds(double &minValue, double &maxValue)
{
	minValue = 0;
	if (m_dateCount > 1) {
		maxValue = m_dateCount - 1;
	}
	else {
		maxValue = 0;
	}
}

double DateAxis::GetValue(int step)
{
	return step;
}

void DateAxis::GetLabel(int step, wxString &label)
{
	DateTimeDataset *dataset = wxDynamicCast(m_datasets[0], DateTimeDataset);
	if (dataset == NULL) {
		return ; // BUG
	}

	wxDateTime dt;
	dt.Set(dataset->GetDate(step));
	label = dt.Format(m_dateFormat);
}

bool DateAxis::IsEnd(int step)
{
	return step >= m_dateCount;
}
