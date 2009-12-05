/////////////////////////////////////////////////////////////////////////////
// Name:	xydataset.cpp
// Purpose: xy dataset implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xydataset.h>
#include <wx/xy/xyrenderer.h>

IMPLEMENT_CLASS(XYDataset, Dataset)

XYDataset::XYDataset()
{
}

XYDataset::~XYDataset()
{
}

bool XYDataset::AcceptRenderer(Renderer *renderer)
{
	return (wxDynamicCast(renderer, XYRenderer) != NULL);
}

double XYDataset::GetMaxY()
{
	double maxY = 0;

	for (size_t serie = 0; serie < GetSerieCount(); serie++) {
		for (size_t n = 0; n < GetCount(serie); n++) {
			double y = GetY(n, serie);
			if (n == 0 && serie == 0)
				maxY = y;
			else
				maxY = wxMax(maxY, y);
		}
	}
	return maxY;
}

double XYDataset::GetMinY()
{
	double minY = 0;

	for (size_t serie = 0; serie < GetSerieCount(); serie++) {
		for (size_t n = 0; n < GetCount(serie); n++) {
			double y = GetY(n, serie);
			if (n == 0 && serie == 0)
				minY = y;
			else
				minY = wxMin(minY, y);
		}
	}
	return minY;
}

double XYDataset::GetMaxX()
{
	double maxX = 0;

	for (size_t serie = 0; serie < GetSerieCount(); serie++) {
		for (size_t n = 0; n < GetCount(serie); n++) {
			double x = GetX(n, serie);
			if (n == 0 && serie == 0)
				maxX = x;
			else
				maxX = wxMax(maxX, x);
		}
	}
	return maxX;
}

double XYDataset::GetMinX()
{
	double minX = 0;

	for (size_t serie = 0; serie < GetSerieCount(); serie++) {
		for (size_t n = 0; n < GetCount(serie); n++) {
			double x = GetX(n, serie);
			if (n == 0 && serie == 0)
				minX = x;
			else
				minX = wxMin(minX, x);
		}
	}
	return minX;
}

double XYDataset::GetMinValue(bool verticalAxis)
{
	if (verticalAxis) {
		return GetMinY();
	}
	else {
		return GetMinX();
	}
}

double XYDataset::GetMaxValue(bool verticalAxis)
{
	if (verticalAxis) {
		return GetMaxY();
	}
	else {
		return GetMaxX();
	}
}
