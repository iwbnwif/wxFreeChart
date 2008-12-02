/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcdemos.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	30.11.2008
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/ohlc/ohlcplot.h"
#include "wx/ohlc/ohlcdataset.h"
#include "wx/ohlc/ohlcbarrenderer.h"

class OHLCDemoDataset : public OHLCDataset
{
public:
	OHLCDemoDataset(OHLCItem *items, int count)
	{
		m_items = new OHLCItem[count];
		memcpy(m_items, items, count * sizeof(*items));
		m_count = count;
	}

	virtual ~OHLCDemoDataset()
	{
		delete m_items;
	}

	virtual OHLCItem *GetItem(int index)
	{
		wxCHECK_MSG(index < m_count, NULL, wxT("GetItem"));
		return &m_items[index];
	}

	virtual int GetCount()
	{
		return m_count;
	}

private:
	OHLCItem *m_items;
	int m_count;
};

/**
 * Simple OHLC demo with bar renderer.
 */
class OHLCDemo1 : public ChartDemo
{
public:
	OHLCDemo1()
	: ChartDemo(wxT("OHLC Demo 1"))
	{
	}

	virtual Chart *Create()
	{
		OHLCItem data[] = {
			{ 64.09,64.34,63.17,63.42,0, 0, },
			{ 63.34,63.52,61.08,61.50,0, 0, },
			{ 61.41,62.40,60.97,62.09,0, 0, },
			{ 62.00,62.79,61.39,61.72,0, 0, },
			{ 61.71,63.39,61.41,63.36,0, 0, },
			{ 63.39,63.89,62.75,63.54,0, 0, },
			{ 63.64,63.79,62.79,63.66,0, 0, },
			{ 63.61,65.26,63.49,65.11,0, 0, },
			{ 65.11,65.86,64.68,65.73,0, 0, },
			{ 65.72,66.76,65.26,66.75,0, 0, },
			{ 66.89,66.91,65.51,65.88,0, 0, },
			{ 66.68,67.92,66.58,66.75,0, 0, },
			{ 66.51,66.86,65.72,66.38,0, 0, },
			{ 66.40,67.37,65.83,67.15,0, 0, },
			{ 67.27,68.23,67.27,67.78,0, 0, },
			{ 67.66,67.68,66.61,67.24,0, 0, },
		};

		const wxChar *dates[] = {
			wxT("20060317"),
			wxT("20060320"),
			wxT("20060321"),
			wxT("20060322"),
			wxT("20060323"),
			wxT("20060324"),
			wxT("20060327"),
			wxT("20060328"),
			wxT("20060329"),
			wxT("20060330"),
			wxT("20060331"),
			wxT("20060403"),
			wxT("20060404"),
			wxT("20060405"),
			wxT("20060406"),
			wxT("20060407"),
		};

		wxDateTime dt;
		for (size_t n = 0; n < N(data); n++) {
			dt.ParseFormat(wxT("%Y%m%d"), dates[n]);
			data[n].date = dt.GetTicks();
		}

		// first step: create plot
		OHLCPlot *plot = new OHLCPlot();

		OHLCDemoDataset *dataset = new OHLCDemoDataset(data, N(data));

		dataset->SetRenderer(new OHLCBarRenderer());

		plot->AddDataset(dataset);

		// add left number (for quotes) and bottom date axes
		plot->AddAxis(new NumberAxis(AXIS_LEFT));
		plot->AddAxis(new DateAxis(AXIS_BOTTOM));

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		return new Chart(plot, GetName());
	}
};


ChartDemo *ohlcDemos[] = {
	new OHLCDemo1(),
};
int ohlcDemosCount = N(ohlcDemos);
