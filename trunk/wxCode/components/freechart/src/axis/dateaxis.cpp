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
	return (dynamic_cast<DateTimeDataset *>(dataset) != NULL)
		&& (m_datasets.GetSize() == 0);
}

void DateAxis::UpdateBounds()
{
	m_dateCount = 0;

	for (int n = 0; n < m_datasets.GetSize(); n++) {
		DateTimeDataset *dataset = (DateTimeDataset *) m_datasets[n];

		int count = dataset->GetCount();
		m_dateCount = MAX(m_dateCount, count);
	}
}

wxSize DateAxis::GetLongestLabelExtent(wxDC &dc)
{
	return wxSize(0, 0); // TODO temporary
}

wxCoord DateAxis::DoToGraphics(wxDC &dc, int minG, int range, double value)
{
	wxSize maxTextExtent = GetLongestLabelExtent(dc);

	double maxValue = m_dateCount - 1;

	if (IsVertical()) {
		wxCoord y0 = minG + maxTextExtent.GetHeight() / 2;
		double height = range - maxTextExtent.GetHeight();

		wxCoord y = (wxCoord) ((maxValue - value) * height / maxValue + y0);
		return y;
	}
	else {
		wxCoord x0 = minG + maxTextExtent.GetWidth() / 2;
		double width = range - maxTextExtent.GetWidth();

		wxCoord x = (wxCoord) ((value * width) / maxValue + x0);
		return x;
	}
}

double DateAxis::DoToData(wxDC &dc, int minG, int range, wxCoord g)
{
	wxSize maxTextExtent = GetLongestLabelExtent(dc);

	wxCoord minCoord;
	double gRange;

	double maxValue = m_dateCount - 1;

	if (IsVertical()) {
		minCoord = minG + maxTextExtent.GetHeight() / 2;
		gRange = range - maxTextExtent.GetHeight();
		if (gRange <= 0) {
			return 0;
		}

		return maxValue - ((g - minCoord) * maxValue / gRange);
	}
	else {
		minCoord = minG + maxTextExtent.GetWidth() / 2;
		gRange = range - maxTextExtent.GetWidth();
		if (gRange <= 0) {
			return 0;
		}

		return ((g - minCoord) * maxValue / gRange);
	}
}

double DateAxis::GetValue(int step)
{
	return step; // TODO temporary
}

void DateAxis::GetLabel(int step, wxString &label)
{
	DateTimeDataset *dataset = dynamic_cast<DateTimeDataset *>(m_datasets[0]);
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

void DateAxis::AddInterval(const wxDateSpan &interval)
{

}

void DateAxis::AddInterval(const wxTimeSpan &interval)
{

}
