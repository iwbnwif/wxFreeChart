/////////////////////////////////////////////////////////////////////////////
// Name:	vectordataset.cpp
// Purpose: vector dataset implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/vectordataset.h>

#include "wx/arrimpl.cpp"

WX_DEFINE_EXPORTED_OBJARRAY(wxDoubleArray);


VectorDataset::VectorDataset()
{
}

VectorDataset::~VectorDataset()
{
}

double VectorDataset::GetX(size_t index, size_t WXUNUSED(serie))
{
	return index + 1;
}

double VectorDataset::GetY(size_t index, size_t WXUNUSED(serie))
{
	return m_values[index];
}

size_t VectorDataset::GetCount(size_t WXUNUSED(serie))
{
	return m_values.Count();
}

size_t VectorDataset::GetSerieCount()
{
	return 1;
}

wxString VectorDataset::GetSerieName(size_t serie)
{
	return wxEmptyString;
}
