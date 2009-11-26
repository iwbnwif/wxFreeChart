/////////////////////////////////////////////////////////////////////////////
// Name:	vectordataset.cpp
// Purpose: vector dataset implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/vectordataset.h>

VectorDataset::VectorDataset()
{
}

VectorDataset::~VectorDataset()
{
}

double VectorDataset::GetX(int index, int WXUNUSED(serie))
{
	return index + 1;
}

double VectorDataset::GetY(int index, int WXUNUSED(serie))
{
	return values[index];
}

int VectorDataset::GetCount(int WXUNUSED(serie))
{
	return (int) values.size();
}

int VectorDataset::GetSerieCount()
{
	return 1;
}

wxString VectorDataset::GetSerieName(int serie)
{
	return wxEmptyString;
}
