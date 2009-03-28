/////////////////////////////////////////////////////////////////////////////
// Name:	democollection.cpp
// Purpose: Demo collection class implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/12
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

extern ChartDemo *ohlcDemos[];
extern int ohlcDemosCount;

extern ChartDemo *barDemos[];
extern int barDemosCount;

extern ChartDemo *xyDemos[];
extern int xyDemosCount;

static DemoCollection instance;

class Category
{
public:
	Category(wxString _name, ChartDemo **_charts, int _chartCount)
	{
		name = _name;
		chartDemos = _charts;
		chartCount = _chartCount;
	}

	wxString GetName()
	{
		return name;
	}

	wxString GetChartName(int chartIndex)
	{
		return chartDemos[chartIndex]->GetName();
	}

	ChartDemo *GetChartDemo(int chartIndex)
	{
		return chartDemos[chartIndex];
	}

	int GetChartCount()
	{
		return chartCount;
	}

private:
	wxString name;
	ChartDemo **chartDemos;
	int chartCount;
};

static Category *cats[] = {
	new Category(wxT("OHLC Charts"), ohlcDemos, ohlcDemosCount),
	new Category(wxT("Bar Charts"), barDemos, barDemosCount),
	new Category(wxT("XY Charts"), xyDemos, xyDemosCount),
};

DemoCollection::DemoCollection()
{
}

DemoCollection::~DemoCollection()
{
}

int DemoCollection::GetCategoryCount()
{
	return N(cats);
}

wxString DemoCollection::GetCategory(int index)
{
	return cats[index]->GetName();
}

int DemoCollection::GetCategoryDemoCount(int index)
{
	return cats[index]->GetChartCount();
}

ChartDemo *DemoCollection::GetCategoryDemo(int catIndex, int demoIndex)
{
	return cats[catIndex]->GetChartDemo(demoIndex);
}

DemoCollection *DemoCollection::Get()
{
	return &instance;
}

