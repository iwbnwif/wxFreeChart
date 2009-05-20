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

IMPLEMENT_CLASS(CategoryAxis, Axis)

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
	return ((wxDynamicCast(dataset, CategoryDataset) != NULL)
		&& m_datasets.GetSize() == 0);
}

wxSize CategoryAxis::GetLongestLabelExtent(wxDC &dc)
{
	return dc.GetTextExtent(m_longestCategory);
}

void CategoryAxis::GetDataBounds(double &minValue, double &maxValue)
{
	minValue = 0;
	if (m_categoryCount > 1) {
		maxValue = m_categoryCount - 1;
	}
	else {
		maxValue = 0;
	}
}

void CategoryAxis::UpdateBounds()
{
	CategoryDataset *dataset = wxDynamicCast(m_datasets[0], CategoryDataset);
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

	FireBoundsChanged();
}

double CategoryAxis::GetValue(int step)
{
	if (IsVertical()) {
		step = m_categoryCount - 1 - step;
	}
	return step;
}

void CategoryAxis::GetLabel(int step, wxString &label)
{
	CategoryDataset *dataset = wxDynamicCast(m_datasets[0], CategoryDataset);
	if (dataset == NULL) {
		label = wxEmptyString;
		return ; // BUG
	}

	if (IsVertical()) {
		step = m_categoryCount - 1 - step;
	}

	label = dataset->GetName(step);
}

bool CategoryAxis::IsEnd(int step)
{
	return step >= m_categoryCount;
}
