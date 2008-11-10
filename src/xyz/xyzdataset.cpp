
/////////////////////////////////////////////////////////////////////////////
// Name:	xyzdataset.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xyz/xyzdataset.h>

XYZDataset::XYZDataset()
{
}

XYZDataset::~XYZDataset()
{
}

double XYZDataset::GetMinZ()
{
	double minZ = 0;

	for (int serie = 0; serie < GetSerieCount(); serie++) {
		for (int n = 0; n < GetCount(serie); n++) {
			double z = GetZ(n, serie);
			if (n == 0 && serie == 0)
				minZ = z;
			else
				minZ = MIN(minZ, z);
		}
	}
	return minZ;
}

double XYZDataset::GetMaxZ()
{
	double maxZ = 0;

	for (int serie = 0; serie < GetSerieCount(); serie++) {
		for (int n = 0; n < GetCount(serie); n++) {
			double z = GetZ(n, serie);
			if (n == 0 && serie == 0)
				maxZ = z;
			else
				maxZ = MAX(maxZ, z);
		}
	}
	return maxZ;
}
