
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
#include <wx/datetimedataset.h>

DateAxis::DateAxis(AXIS_LOCATION location)
: LabelAxis(location)
{
	dateFormat = wxT("%d %m");
}

DateAxis::~DateAxis()
{
}

bool DateAxis::AcceptDataset(Dataset *dataset)
{
	// Accepts only date/time dataset
	// and only one dataset
	return (dynamic_cast<DateTimeDataset *>(dataset) != NULL)
		&& (datasets.GetSize() == 0);
}

void DateAxis::UpdateBounds()
{
	dateCount = 0;

	for (int n = 0; n < datasets.GetSize(); n++) {
		DateTimeDataset *dataset = dynamic_cast<DateTimeDataset *>(datasets[n]);
		if (dataset == NULL) {
			wxLogError(wxT("DateAxis::UpdateBounds: BUG dataset is not DateTimeDataset")); // BUG!
			return ;
		}

		int count = dataset->GetCount();
		if (n == 0)
			dateCount = count;
		else {
			dateCount = MAX(dateCount, count);
		}
	}
}

wxSize DateAxis::GetLongestLabelExtent(wxDC &dc)
{
	return wxSize(0, 0); // TODO temporary
}

wxCoord DateAxis::DoToGraphics(wxDC &dc, int minG, int range, double value)
{
	wxSize maxTextExtent(0, 0);// = dc.GetTextExtent(longestCategory);

	double maxValue = dateCount - 1;

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

double DateAxis::GetValue(int step)
{
	return step; // TODO temporary
}

void DateAxis::GetLabel(int step, wxString &label)
{
	DateTimeDataset *dataset = dynamic_cast<DateTimeDataset *>(datasets[0]);
	if (dataset == NULL) {
		return ; // BUG
	}

	wxDateTime dt;
	dt.Set(dataset->GetDate(step)); // TODO temporary
	label = dt.Format(dateFormat);
}

bool DateAxis::IsEnd(int step)
{
	return step >= dateCount;
}

