
/////////////////////////////////////////////////////////////////////////////
// Name:	categoryaxis.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/categoryaxis.h>
#include <wx/category/categorydataset.h>

CategoryAxis::CategoryAxis(AXIS_LOCATION location)
: LabelAxis(location)
{
}

CategoryAxis::~CategoryAxis()
{
}

bool CategoryAxis::AcceptDataset(Dataset *dataset)
{
	//
	// It must be CategoryDataset and this class supports only one
	// dataset
	//
	return ((dynamic_cast<CategoryDataset *>(dataset) != 0)
		&& datasets.GetSize() == 0);
}

wxSize CategoryAxis::GetLongestLabelExtent(wxDC &dc)
{
	return dc.GetTextExtent(longestCategory);
}

wxCoord CategoryAxis::DoToGraphics(wxDC &dc, int minG, int range, double value)
{
	wxSize maxTextExtent = dc.GetTextExtent(longestCategory);

	double maxValue = categoryCount - 1;

	// XXX!!! bug doesn't work with category datasets with only one category
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

void CategoryAxis::UpdateBounds()
{
	CategoryDataset *dataset = dynamic_cast<CategoryDataset *>(datasets[0]);
	if (dataset == NULL) {
		wxLogError(wxT("CategoryAxis::DataChanged: BUG dataset is not CategoryDataset")); // BUG!
		return ;
	}

	categoryCount = dataset->GetCount();

	for (int nCat = 0; nCat < categoryCount; nCat++) {
		if (nCat == 0) {
			longestCategory = dataset->GetName(nCat);
		}
		else {
			if (longestCategory.Length() < dataset->GetName(nCat).Length()) {
				longestCategory = dataset->GetName(nCat);
			}
		}
	}
}

double CategoryAxis::GetValue(int step)
{
	return step; // TODO temporary
}

void CategoryAxis::GetLabel(int step, wxString &label)
{
	CategoryDataset *dataset = dynamic_cast<CategoryDataset *>(datasets[0]);
	if (dataset == NULL) {
		return ; // BUG
	}

	label = dataset->GetName(step);
}

bool CategoryAxis::IsEnd(int step)
{
	return step >= categoryCount;
}
