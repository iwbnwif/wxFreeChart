/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcdemos.cpp
// Purpose: ohlc demos code
// Author:	Moskvichev Andrey V.
// Created:	30.11.2008
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/ohlc/ohlcplot.h>
#include <wx/ohlc/ohlcdataset.h>
#include <wx/ohlc/ohlcbarrenderer.h>
#include <wx/ohlc/ohlccandlestickrenderer.h>

// for moving average indicator
#include <wx/xy/xydataset.h>
#include <wx/xy/xylinerenderer.h>

#include <wx/axis/numberaxis.h>
#include <wx/axis/dateaxis.h>
#include <wx/axis/compdateaxis.h>

class OHLCDemoDataset : public OHLCDataset
{
public:
	OHLCDemoDataset(OHLCItem *items, size_t count)
	{
		m_items = new OHLCItem[count];
		memcpy(m_items, items, count * sizeof(*items));
		m_count = count;
	}

	virtual ~OHLCDemoDataset()
	{
		wxDELETEA(m_items);
	}

	virtual OHLCItem *GetItem(size_t index)
	{
		wxCHECK_MSG(index < m_count, NULL, wxT("GetItem"));
		return &m_items[index];
	}

	virtual size_t GetCount()
	{
		return m_count;
	}

private:
	OHLCItem *m_items;
	size_t m_count;
};

/**
 * Simple OHLC demo with bar renderer.
 */
class OHLCDemo1 : public ChartDemo
{
public:
	OHLCDemo1()
	: ChartDemo(wxT("OHLC Demo 1 - bars"))
	{
	}

	virtual Chart *Create()
	{
		// OHLC data
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

		// transform dates from string to time_t form
		wxDateTime dt;
		for (size_t n = 0; n < WXSIZEOF(data); n++) {
			dt.ParseFormat(dates[n], wxT("%Y%m%d"));
			data[n].date = dt.GetTicks();
		}

		// first step: create plot
		OHLCPlot *plot = new OHLCPlot();

		// create OHLC dataset
		OHLCDemoDataset *dataset = new OHLCDemoDataset(data, WXSIZEOF(data));

		// create and set OHLC bars renderer to our dataset
		dataset->SetRenderer(new OHLCBarRenderer());

		// add our dataset to plot
		plot->AddDataset(dataset);

		// create left number (for quotes) and bottom date axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);

		// setup window, so we will see 5 bars at once, not entire dataset
		bottomAxis->SetWindow(0, 5);
		bottomAxis->SetUseWindow(true);

		bottomAxis->SetVerticalLabelText(true);
		bottomAxis->SetDateFormat(wxT("%d-%m-%y"));

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		// set scrolling axis to chart, so it will be possible to scroll horizontally
		chart->SetScrolledAxis(bottomAxis);
		return chart;
	}
};

/**
 * Simple OHLC demo with candlestick renderer.
 */
class OHLCDemo2 : public ChartDemo
{
public:
	OHLCDemo2()
	: ChartDemo(wxT("OHLC Demo 2 - candlesticks"))
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
		for (size_t n = 0; n < WXSIZEOF(data); n++) {
			dt.ParseFormat(dates[n], wxT("%Y%m%d"));
			data[n].date = dt.GetTicks();
		}

		// first step: create plot
		OHLCPlot *plot = new OHLCPlot();

		OHLCDemoDataset *dataset = new OHLCDemoDataset(data, WXSIZEOF(data));

		dataset->SetRenderer(new OHLCCandlestickRenderer());

		plot->AddDataset(dataset);

		// add left number (for quotes) and bottom date axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);

		// setup window
		bottomAxis->SetWindow(0, 5);
		bottomAxis->SetUseWindow(true);

		bottomAxis->SetVerticalLabelText(true);
		bottomAxis->SetDateFormat(wxT("%d-%m-%y"));
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		chart->SetScrolledAxis(bottomAxis);
		return chart;
	}
};

/**
 * Simple OHLC demo with candlestick renderer, and composite date axis.
 */
class OHLCDemo3 : public ChartDemo
{
public:
	OHLCDemo3()
	: ChartDemo(wxT("OHLC Demo 3 - candlesticks"))
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
		for (size_t n = 0; n < WXSIZEOF(data); n++) {
			dt.ParseFormat(dates[n], wxT("%Y%m%d"));
			data[n].date = dt.GetTicks();
		}

		// first step: create plot
		OHLCPlot *plot = new OHLCPlot();

		OHLCDemoDataset *dataset = new OHLCDemoDataset(data, WXSIZEOF(data));

		dataset->SetRenderer(new OHLCCandlestickRenderer());

		plot->AddDataset(dataset);

		// add left number (for quotes) and bottom date axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		CompDateAxis *bottomAxis = new CompDateAxis(AXIS_BOTTOM);

		// setup window
		bottomAxis->SetWindow(0, 10);
		bottomAxis->SetUseWindow(true);

		// set date spans
		bottomAxis->AddInterval(wxDateSpan::Day());
		bottomAxis->AddInterval(wxDateSpan::Week());
		bottomAxis->AddInterval(wxDateSpan::Month());
		bottomAxis->AddInterval(wxDateSpan::Year());

		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		chart->SetScrolledAxis(bottomAxis);
		return chart;
	}
};

/**
 * Simple moving average indicator.
 * TODO: move it from demos to library
 */
class MovingAverage : public XYDataset, public DatasetObserver
{
	DECLARE_CLASS(MovingAverage)
public:
	MovingAverage(OHLCDataset *ohlcDataset, int period);
	virtual ~MovingAverage();

	virtual size_t GetSerieCount();

	virtual wxString GetSerieName(size_t serie);

	virtual size_t GetCount(size_t serie);

	virtual double GetX(size_t index, size_t serie);

	virtual double GetY(size_t index, size_t serie);

	//
	// DatasetObserver
	//
	virtual void DatasetChanged(Dataset *dataset);

private:
	OHLCDataset *m_ohlcDataset;
	int m_period;
};

IMPLEMENT_CLASS(MovingAverage, XYDataset)

MovingAverage::MovingAverage(OHLCDataset *ohlcDataset, int period)
{
	m_ohlcDataset = ohlcDataset;
	m_period = period;

	m_ohlcDataset->AddRef();
	m_ohlcDataset->AddObserver(this);
}

MovingAverage::~MovingAverage()
{
	SAFE_REMOVE_OBSERVER(this, m_ohlcDataset);
	SAFE_UNREF(m_ohlcDataset);
}

size_t MovingAverage::GetSerieCount()
{
	return 1;
}

size_t MovingAverage::GetCount(size_t WXUNUSED(serie))
{
	int count = m_ohlcDataset->GetCount() - m_period + 1;
	if (count < 0) {
		count = 0; // period is larger than OHLC data
	}
	return count;
}

wxString MovingAverage::GetSerieName(size_t WXUNUSED(serie))
{
	return wxT("Moving average");
}

double MovingAverage::GetX(size_t index, size_t WXUNUSED(serie))
{
	return index + m_period - 1;
}

double MovingAverage::GetY(size_t index, size_t WXUNUSED(serie))
{
	wxCHECK_MSG(m_period != 0, 0, wxT("MovingAverage::GetX"));

	double sum = 0;

	for (size_t n = index; n < index + m_period; n++) {
		OHLCItem *item = m_ohlcDataset->GetItem(n);

		sum += item->close;
	}
	return sum / m_period;
}

void MovingAverage::DatasetChanged(Dataset *dataset)
{
	Dataset::DatasetChanged();
}

/**
 * OHLC demo with candlestick renderer and moving average indicator.
 */
class OHLCDemo4 : public ChartDemo
{
public:
	OHLCDemo4()
	: ChartDemo(wxT("OHLC Demo 2 - with moving average"))
	{
	}

	virtual Chart *Create()
	{
		// quotes
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

		// trade dates
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

		// transform dates from string to time_t representation
		wxDateTime dt;
		for (size_t n = 0; n < WXSIZEOF(data); n++) {
			dt.ParseFormat(dates[n], wxT("%Y%m%d"));
			data[n].date = dt.GetTicks();
		}

		// first step: create plot
		OHLCPlot *plot = new OHLCPlot();

		OHLCDemoDataset *dataset = new OHLCDemoDataset(data, WXSIZEOF(data));

		dataset->SetRenderer(new OHLCCandlestickRenderer());

		plot->AddDataset(dataset);

		// add moving average dataset with period = 5
		MovingAverage *ma = new MovingAverage(dataset, 5);
		ma->SetRenderer(new XYLineRenderer());

		plot->AddDataset(ma);

		// add left number (for quotes) and bottom date axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);

		// setup window
		bottomAxis->SetWindow(0, 10);
		bottomAxis->SetUseWindow(true);

		bottomAxis->SetVerticalLabelText(true);
		bottomAxis->SetDateFormat(wxT("%d-%m"));
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and OHLC dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// link axes with moving average
		plot->LinkDataVerticalAxis(1, 0);
		plot->LinkDataHorizontalAxis(1, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		chart->SetScrolledAxis(bottomAxis);
		return chart;
	}
};

ChartDemo *ohlcDemos[] = {
	new OHLCDemo1(),
	new OHLCDemo2(),
	//new OHLCDemo3(), // XXX: compdateaxis is broken!
	new OHLCDemo4(),
};
int ohlcDemosCount = WXSIZEOF(ohlcDemos);
