/////////////////////////////////////////////////////////////////////////////
// Name:	categoryaxis.cpp
// Purpose: category axis implementation
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
		&& m_datasets.GetSize() == 0); // TODO don't use dynamic_cast and RTTI!
}

wxSize CategoryAxis::GetLongestLabelExtent(wxDC &dc)
{
	return dc.GetTextExtent(m_longestCategory);
}

wxCoord CategoryAxis::DoToGraphics(wxDC &dc, int minG, int range, double value)
{
	wxSize maxTextExtent = dc.GetTextExtent(m_longestCategory);

	double maxValue = m_categoryCount - 1;

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

double CategoryAxis::DoToData(wxDC &dc, int minG, int range, wxCoord g)
{
	wxSize maxTextExtent = GetLongestLabelExtent(dc);

	wxCoord minCoord;
	double gRange;

	double maxValue = m_categoryCount - 1;

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

void CategoryAxis::UpdateBounds()
{
	CategoryDataset *dataset = dynamic_cast<CategoryDataset *>(m_datasets[0]);
	if (dataset == NULL) {
		wxLogError(wxT("CategoryAxis::DataChanged: BUG dataset is not CategoryDataset")); // BUG!
		return ;
	}

	m_categoryCount = dataset->GetCount();

	m_longestCategory = dataset->GetName(0);
	for (int nCat = 1; nCat < m_categoryCount; nCat++) {
		wxString catName = dataset->GetName(nCat);

		if (m_longestCategory.Length() < catName.Length()) {
			m_longestCategory = catName;
		}
	}
}

double CategoryAxis::GetValue(int step)
{
	return step;
}

void CategoryAxis::GetLabel(int step, wxString &label)
{
	CategoryDataset *dataset = dynamic_cast<CategoryDataset *>(m_datasets[0]);
	if (dataset == NULL) {
		return ; // BUG
	}

	label = dataset->GetName(step);
}

bool CategoryAxis::IsEnd(int step)
{
	return step >= m_categoryCount;
}
