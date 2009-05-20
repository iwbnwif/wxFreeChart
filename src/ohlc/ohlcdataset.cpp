/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcdataset.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/ohlc/ohlcdataset.h>

OHLCDataset::OHLCDataset()
{
	m_serieName = wxT("OHLC");
}

OHLCDataset::~OHLCDataset()
{
}

bool OHLCDataset::AcceptRenderer(Renderer *_renderer)
{
	return (wxDynamicCast(_renderer, OHLCRenderer) != NULL);
}

double OHLCDataset::GetMaxValue(bool unused)
{
	double maxValue = 0;

	for (int n = 0; n < GetCount(); n++) {
		OHLCItem *item = GetItem(n);

		if (n == 0)
			maxValue = item->high;
		else
			maxValue = wxMax(maxValue, item->high);
	}
	return maxValue;
}

double OHLCDataset::GetMinValue(bool unused)
{
	double minValue = 0;

	for (int n = 0; n < GetCount(); n++) {
		OHLCItem *item = GetItem(n);

		if (n == 0)
			minValue = item->low;
		else
			minValue = wxMin(minValue, item->low);
	}
	return minValue;
}


time_t OHLCDataset::GetDate(int index)
{
	return GetItem(index)->date;
}


int OHLCDataset::GetCount(int serie)
{
	return GetCount();
}

int OHLCDataset::GetSerieCount()
{
	return 1;
}

wxString OHLCDataset::GetSerieName(int serie)
{
	return m_serieName;
}

DateTimeDataset *OHLCDataset::AsDateTimeDataset()
{
	return this;
}
