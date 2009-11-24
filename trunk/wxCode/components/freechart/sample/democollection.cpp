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

extern ChartDemo *ganttDemos[];
extern int ganttDemosCount;

extern ChartDemo *bubbleDemos[];
extern int bubbleDemosCount;

extern ChartDemo *combinedAxisDemos[];
extern int combinedAxisDemosCount;

extern ChartDemo *timeSeriesDemos[];
extern int timeSeriesDemosCount;


static DemoCollection instance;

class Category
{
public:
	Category(wxString name, ChartDemo **charts, int chartCount)
	{
		m_name = name;
		m_chartDemos = charts;
		m_chartCount = chartCount;
	}

	const wxString &GetName()
	{
		return m_name;
	}

	const wxString &GetChartName(int chartIndex)
	{
		return m_chartDemos[chartIndex]->GetName();
	}

	ChartDemo *GetChartDemo(int chartIndex)
	{
		return m_chartDemos[chartIndex];
	}

	int GetChartCount()
	{
		return m_chartCount;
	}

private:
	wxString m_name;
	ChartDemo **m_chartDemos;
	int m_chartCount;
};

static Category *cats[] = {
	new Category(wxT("OHLC Charts"), ohlcDemos, ohlcDemosCount),
	new Category(wxT("Bar Charts"), barDemos, barDemosCount),
	new Category(wxT("XY Charts"), xyDemos, xyDemosCount),
	new Category(wxT("Gantt Charts"), ganttDemos, ganttDemosCount),
	new Category(wxT("Bubble Charts"), bubbleDemos, bubbleDemosCount),
	new Category(wxT("Combined axis"), combinedAxisDemos, combinedAxisDemosCount),
	new Category(wxT("Time series Charts"), timeSeriesDemos, timeSeriesDemosCount),
};

DemoCollection::DemoCollection()
{
}

DemoCollection::~DemoCollection()
{
}

int DemoCollection::GetCategoryCount()
{
	return WXSIZEOF(cats);
}

const wxString &DemoCollection::GetCategory(int index)
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

