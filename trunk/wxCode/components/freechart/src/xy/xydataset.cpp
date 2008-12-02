/////////////////////////////////////////////////////////////////////////////
// Name:	xydataset.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/xydataset.h>
#include <wx/xy/xyrenderer.h>

XYDataset::XYDataset()
{
}

XYDataset::~XYDataset()
{
}

bool XYDataset::AcceptRenderer(Renderer *_renderer)
{
	return (dynamic_cast<XYRenderer *>(_renderer) != NULL);
}

double XYDataset::GetMaxY()
{
	double maxY = 0;

	for (int serie = 0; serie < GetSerieCount(); serie++) {
		for (int n = 0; n < GetCount(serie); n++) {
			double y = GetY(n, serie);
			if (n == 0 && serie == 0)
				maxY = y;
			else
				maxY = MAX(maxY, y);
		}
	}
	return maxY;
}

double XYDataset::GetMinY()
{
	double minY = 0;

	for (int serie = 0; serie < GetSerieCount(); serie++) {
		for (int n = 0; n < GetCount(serie); n++) {
			double y = GetY(n, serie);
			if (n == 0 && serie == 0)
				minY = y;
			else
				minY = MIN(minY, y);
		}
	}
	return minY;
}

double XYDataset::GetMaxX()
{
	double maxX = 0;

	for (int serie = 0; serie < GetSerieCount(); serie++) {
		for (int n = 0; n < GetCount(serie); n++) {
			double x = GetX(n, serie);
			if (n == 0 && serie == 0)
				maxX = x;
			else
				maxX = MAX(maxX, x);
		}
	}
	return maxX;
}

double XYDataset::GetMinX()
{
	double minX = 0;

	for (int serie = 0; serie < GetSerieCount(); serie++) {
		for (int n = 0; n < GetCount(serie); n++) {
			double x = GetX(n, serie);
			if (n == 0 && serie == 0)
				minX = x;
			else
				minX = MIN(minX, x);
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
