/////////////////////////////////////////////////////////////////////////////
// Name:	compdateaxis.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/axis/compdateaxis.h"

IMPLEMENT_CLASS(CompDateAxis, LabelAxis)

CompDateAxis::CompDateAxis(AXIS_LOCATION location)
: LabelAxis(location)
{
}

CompDateAxis::~CompDateAxis()
{
}

bool CompDateAxis::AcceptDataset(Dataset *dataset)
{
	// Accepts only date/time dataset
	// and only one dataset
	return (wxDynamicCast(dataset, DateTimeDataset) != NULL)
		&& (m_datasets.GetSize() == 0);
}

/*
void CompDateAxis::UpdateBounds()
{
	m_dateCount = 0;

	for (int n = 0; n < m_datasets.GetSize(); n++) {
		DateTimeDataset *dataset = (DateTimeDataset *) m_datasets[n];

		int count = dataset->GetCount();
		m_dateCount = MAX(m_dateCount, count);
	}
}
*/

wxSize CompDateAxis::GetLongestLabelExtent(wxDC &dc)
{
	return wxSize(0, 0); // TODO temporary
}

void CompDateAxis::GetDataBounds(double &minValue, double &maxValue)
{
	// XXX!!! bug doesn't work with category datasets with only one category
	minValue = 0;
	maxValue = 0; // TODO temporary
}

double CompDateAxis::GetValue(int step)
{
	return step; // TODO temporary
}

void CompDateAxis::GetLabel(int step, wxString &label)
{
	DateTimeDataset *dataset = wxDynamicCast(m_datasets[0], DateTimeDataset);
	if (dataset == NULL) {
		return ; // BUG
	}

	wxDateTime dt;
	dt.Set(dataset->GetDate(step));
	//label = dt.Format(m_dateFormat);
}

bool CompDateAxis::IsEnd(int step)
{
	return true;
	//return step >= m_dateCount;
}

void CompDateAxis::AddInterval(const wxDateSpan &interval)
{
	// TODO not implemented
}

void CompDateAxis::AddInterval(const wxTimeSpan &interval)
{
	// TODO not implemented
}
