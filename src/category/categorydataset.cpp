
/////////////////////////////////////////////////////////////////////////////
// Name:	categorydataset.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/category/categorydataset.h>
#include <wx/xy/xyhistorenderer.h>

CategoryDataset::CategoryDataset()
{
}

CategoryDataset::~CategoryDataset()
{
}

bool CategoryDataset::AcceptRenderer(Renderer *r)
{
	return (dynamic_cast<XYHistoRenderer *>(r) != NULL);
}

bool CategoryDataset::HasValue(int index, int serie)
{
	return true;
}

double CategoryDataset::GetMinValue(bool verticalAxis)
{
	if (GetCount() == 0)
		return 0;

	double minValue = GetValue(0, 0);

	for (int nSerie = 0; nSerie < GetSerieCount(); nSerie++) {
		for (int n = 0; n < GetCount(); n++) {
			minValue = MIN(minValue, GetValue(n, nSerie));
		}
	}
	return minValue;
}

double CategoryDataset::GetMaxValue(bool verticalAxis)
{
	if (GetCount() == 0)
		return 0;

	double maxValue = GetValue(0, 0);

	for (int nSerie = 0; nSerie < GetSerieCount(); nSerie++) {
		for (int n = 0; n < GetCount(); n++) {
			maxValue = MAX(maxValue, GetValue(n, nSerie));
		}
	}
	return maxValue;
}

double CategoryDataset::GetX(int index, int serie)
{
	return index;
}

double CategoryDataset::GetY(int index, int serie)
{
	return GetValue(index, serie);
}

int CategoryDataset::GetCount(int serie)
{
	return GetCount(); // in category dataset all series has equal count of elements
}
