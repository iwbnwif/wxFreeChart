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

CategoryDataset::CategoryDataset()
{
}

CategoryDataset::~CategoryDataset()
{
}

bool CategoryDataset::AcceptRenderer(Renderer *renderer)
{
	return wxDynamicCast(renderer, BarRenderer);
}

bool CategoryDataset::HasValue(int index, int serie)
{
	return true;
}

double CategoryDataset::GetMinValue(bool WXUNUSED(verticalAxis))
{
	if (GetRenderer() == NULL) {
		return 0;
	}
	return GetRenderer()->GetMinValue(this);
}

double CategoryDataset::GetMaxValue(bool WXUNUSED(verticalAxis))
{
	if (GetRenderer() == NULL) {
		return 0;
	}
	return GetRenderer()->GetMaxValue(this);
}

// TODO deprecated functions.
//
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
