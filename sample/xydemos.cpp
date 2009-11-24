/////////////////////////////////////////////////////////////////////////////
// Name:	xydemos.cpp
// Purpose: xy demos
// Author:	Moskvichev Andrey V.
// Created:	2008/11/12
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>

// for histogram demo
#include <wx/xy/xyhistorenderer.h>

// for dynamic dataset
#include <wx/xy/vectordataset.h>

#include <wx/xy/functions/sinefunction.h>

#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>


#include <math.h>

/**
 * Holds data for one XY serie.
 */
class XYSerie
{
public:
	XYSerie(double *data, int count)
	{
		m_data = new double[2 * count];
		memcpy(m_data, data, 2 * count * sizeof(double));
		m_count = count;
	}

	virtual ~XYSerie()
	{
		wxDELETEA(m_data);
	}

	double GetX(int index)
	{
		wxCHECK_MSG(index < m_count, 0, wxT("XYSerie::GetX"));
		return m_data[index * 2];
	}

	double GetY(int index)
	{
		wxCHECK_MSG(index < m_count, 0, wxT("XYSerie::GetY"));
		return m_data[index * 2 + 1];
	}

	int GetCount()
	{
		return m_count;
	}

	const wxString &GetName()
	{
		return m_name;
	}

	void SetName(const wxString &name)
	{
		m_name = name;;
	}

private:
	double *m_data;
	int m_count;
	wxString m_name;
};

WX_DECLARE_OBJARRAY(XYSerie *, XYSerieArray);
WX_DEFINE_OBJARRAY(XYSerieArray);

class XYDemoDataset : public XYDataset
{
public:
	XYDemoDataset()
	{
	}

	virtual ~XYDemoDataset()
	{
		for (size_t n = 0; n < m_series.Count(); n++) {
			wxDELETE(m_series[n]);
		}
	}

	void AddSerie(double *data, int count)
	{
		m_series.Add(new XYSerie(data, count));
		DatasetChanged();
	}

	virtual double GetX(int index, int serie)
	{
		return m_series[serie]->GetX(index);
	}

	virtual double GetY(int index, int serie)
	{
		return m_series[serie]->GetY(index);
	}

	virtual int GetSerieCount()
	{
		return m_series.Count();
	}

	virtual int GetCount(int serie)
	{
		return m_series[serie]->GetCount();
	}

	virtual wxString GetSerieName(int serie)
	{
		return m_series[serie]->GetName();
		//return wxString::Format(wxT("serie %i"), serie);
	}

	void SetSerieName(int serie, const wxString &name)
	{
		m_series[serie]->SetName(name);
		DatasetChanged();
	}

private:
	XYSerieArray m_series;
};

class XYDemo1 : public ChartDemo
{
public:
	XYDemo1()
	: ChartDemo(wxT("XY Demo 1 - simple"))
	{
	}

	virtual Chart *Create()
	{
		double data[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		XYDemoDataset *dataset = new XYDemoDataset();
		dataset->AddSerie((double *) data, WXSIZEOF(data));

		dataset->SetRenderer(new XYLineRenderer());

		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// optional: set axis titles
		leftAxis->SetTitle(wxT("X"));
		bottomAxis->SetTitle(wxT("Y"));

		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		return new Chart(plot, GetName());
	}
};

/**
 * The same as XYDemo1, but with two series.
 */
class XYDemo2 : public ChartDemo
{
public:
	XYDemo2()
	: ChartDemo(wxT("XY Demo 2 - multiple series"))
	{
	}

	virtual Chart *Create()
	{
		double data1[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};
		double data2[][2] = {
				{ 45, 40, },
				{ 23, 16, },
				{ 43, 60, },
				{ 25, 7, },
				{ 66, 4, },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		XYDemoDataset *dataset = new XYDemoDataset();
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));

		dataset->SetRenderer(new XYLineRenderer());

		plot->AddDataset(dataset);

		// add left and bottom number axes
		plot->AddAxis(new NumberAxis(AXIS_LEFT));
		plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		return new Chart(plot, GetName());
	}
};

/**
 * The same as XYDemo2, but draws symbols instead of lines.
 * With legend.
 */
class XYDemo3 : public ChartDemo
{
public:
	XYDemo3()
	: ChartDemo(wxT("XY Demo 3 - symbols"))
	{
	}

	virtual Chart *Create()
	{
		double data1[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};
		double data2[][2] = {
				{ 45, 40, },
				{ 23, 16, },
				{ 43, 60, },
				{ 25, 7, },
				{ 66, 4, },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		XYDemoDataset *dataset = new XYDemoDataset();
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));

		// set line renderer with symbols enabled and lines disabled
		dataset->SetRenderer(new XYLineRenderer(true, false));

		plot->AddDataset(dataset);

		// add left and bottom number axes
		plot->AddAxis(new NumberAxis(AXIS_LEFT));
		plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// set serie names to be displayed on legend
		dataset->SetSerieName(0, wxT("Serie 0"));
		dataset->SetSerieName(1, wxT("Serie 1"));

		// set legend to plot
		plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

		// and finally create chart
		return new Chart(plot, GetName());
	}
};

class XYDemo4 : public ChartDemo
{
public:
	XYDemo4()
	: ChartDemo(wxT("XY Demo 4 - window"))
	{
	}

	virtual Chart *Create()
	{
		double data[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		XYDemoDataset *dataset = new XYDemoDataset();
		dataset->AddSerie((double *) data, WXSIZEOF(data));

		dataset->SetRenderer(new XYLineRenderer());

		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// look at this code, we setup window, so
		// only part of data will be shown, not entire dataset as
		// in XYDemo1.
		bottomAxis->SetWindowPosition(10);
		bottomAxis->SetWindowWidth(10);
		bottomAxis->SetUseWindow(true);

		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		// set axis as scrolled, so chart panel can scroll its window.
		chart->SetScrolledAxis(bottomAxis);
		return chart;
	}
};

class DynamicDemoDataset : public VectorDataset, public wxEvtHandler
{
public:
	DynamicDemoDataset();
	virtual ~DynamicDemoDataset();

	void OnTimer(wxTimerEvent &ev);
private:
	wxTimer m_timer;

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(DynamicDemoDataset, wxEvtHandler)
	EVT_TIMER(wxID_ANY, DynamicDemoDataset::OnTimer)
END_EVENT_TABLE()

DynamicDemoDataset::DynamicDemoDataset()
{
	// start timer, that will add new data to dataset
	m_timer.SetOwner(this);
	m_timer.Start(1000);
}

DynamicDemoDataset::~DynamicDemoDataset()
{
	m_timer.Stop();
}

void DynamicDemoDataset::OnTimer(wxTimerEvent &ev)
{
	double r = rand();
	double y = 100.0 * r / (double) RAND_MAX;
	Add(y);
}

class XYDemo5 : public ChartDemo
{
public:
	XYDemo5()
	: ChartDemo(wxT("XY Demo 5 - dynamic"))
	{
	}

	virtual Chart *Create()
	{
		// first step: create plot
		XYPlot *plot = new XYPlot();

		DynamicDemoDataset *dataset = new DynamicDemoDataset();
		dataset->SetRenderer(new XYLineRenderer());

		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// we setup window
		//bottomAxis->SetWindow(0, 10);
		//bottomAxis->SetUseWindow(true);

		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		// set axis as scrolled, so chart panel can scroll its window.
		//chart->SetScrolledAxis(bottomAxis);
		return chart;
	}
};

/**
 * Histogram XY chart demo
 */
class XYDemo6 : public ChartDemo
{
public:
	XYDemo6()
	: ChartDemo(wxT("XY Demo 6 - histogram"))
	{
	}

	virtual Chart *Create()
	{
		double data[][2] = {
				{ -2.75	, 0.01 },
				{ -2.5	, 0.02 },
				{ -2.25	, 0.03 },
				{ -2	, 0.05 },
				{ -1.75	, 0.09 },
				{ -1.5	, 0.13 },
				{ -1.25	, 0.18 },
				{ -1	, 0.24 },
				{ -0.75	, 0.3 },
				{ -0.5	, 0.35 },
				{ -0.25	, 0.39 },
				{ 0	, 0.4 },
				{ 0.25	, 0.39 },
				{ 0.5	, 0.35 },
				{ 0.75	, 0.3 },
				{ 1	, 0.24 },
				{ 1.25	, 0.18 },
				{ 1.5	, 0.13 },
				{ 1.75	, 0.09 },
				{ 2	, 0.05 },
				{ 2.25	, 0.03 },
				{ 2.5	, 0.02 },
				{ 2.75	, 0.01 },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		XYDemoDataset *dataset = new XYDemoDataset();
		dataset->AddSerie((double *) data, WXSIZEOF(data));

		// create histogram renderer with bar width = 10 and vertical bars
		XYHistoRenderer *histoRenderer = new XYHistoRenderer(10, true);

		histoRenderer->SetBarArea(0, new FillAreaDraw(*wxBLACK_PEN, *wxGREEN_BRUSH));

		dataset->SetRenderer(histoRenderer);

		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		bottomAxis->SetMargins(15, 15);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		// set axis as scrolled, so chart panel can scroll its window.
		return chart;
	}
};

/**
 * Histogram XY chart demo
 */
class XYDemo7 : public ChartDemo
{
public:
	XYDemo7()
	: ChartDemo(wxT("XY Demo 7 - two histograms"))
	{
	}

	virtual Chart *Create()
	{
		// serie 1 data
		double data1[][2] = {
				{ -2.75	, 0.01 },
				{ -2.5	, 0.02 },
				{ -2.25	, 0.03 },
				{ -2	, 0.05 },
				{ -1.75	, 0.09 },
				{ -1.5	, 0.13 },
				{ -1.25	, 0.18 },
				{ -1	, 0.24 },
				{ -0.75	, 0.3 },
				{ -0.5	, 0.35 },
				{ -0.25	, 0.39 },
				{ 0	, 0.4 },
				{ 0.25	, 0.39 },
				{ 0.5	, 0.35 },
				{ 0.75	, 0.3 },
				{ 1	, 0.24 },
				{ 1.25	, 0.18 },
				{ 1.5	, 0.13 },
				{ 1.75	, 0.09 },
				{ 2	, 0.05 },
				{ 2.25	, 0.03 },
				{ 2.5	, 0.02 },
				{ 2.75	, 0.01 },
		};
		// serie 2 data
		double data2[][2] = {
				{ -3.75	, 0.01 },
				{ -3.5	, 0.02 },
				{ -3.25	, 0.03 },
				{ -3	, 0.05 },
				{ -2.75	, 0.09 },
				{ -2.5	, 0.13 },
				{ -2.25	, 0.18 },
				{ -2	, 0.24 },
				{ -1.75	, 0.3 },
				{ -1.5	, 0.35 },
				{ -1.25	, 0.39 },
				{-1	, 0.4 },
				{ -0.75	, 0.39 },
				{ -0.5	, 0.35 },
				{ -0.25	, 0.3 },
				{ 0	, 0.24 },
				{ 0.25	, 0.18 },
				{ 0.5	, 0.13 },
				{ 0.75	, 0.09 },
				{ 1	, 0.05 },
				{ 1.25	, 0.03 },
				{ 1.5	, 0.02 },
				{ 1.75	, 0.01 },
		};


		// first step: create plot
		XYPlot *plot = new XYPlot();

		XYDemoDataset *dataset = new XYDemoDataset();

		// add two series
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));

		// create histogram renderer with bar width = 10 and vertical bars
		XYHistoRenderer *histoRenderer = new XYHistoRenderer(10, true);

		// set bar area draw for two series
		histoRenderer->SetBarArea(0, new FillAreaDraw(*wxBLACK_PEN, *wxBLUE_BRUSH));
		histoRenderer->SetBarArea(1, new FillAreaDraw(*wxBLACK_PEN, *wxGREEN_BRUSH));

		dataset->SetRenderer(histoRenderer);

		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		bottomAxis->SetMargins(15, 15);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		// set axis as scrolled, so chart panel can scroll its window.
		return chart;
	}
};


/**
 * Multiseries line xy chart demo.
 * Also it shows how to use legend.
 */
class XYDemo8 : public ChartDemo
{
public:
	XYDemo8()
	: ChartDemo(wxT("XY Demo 8 - multiseries"))
	{
	}

	virtual Chart *Create()
	{
		// serie 1 data
		double data1[][2] = {
				{ -2.75	, 0.01 },
				{ -2.5	, 0.02 },
				{ -2.25	, 0.03 },
				{ -2	, 0.05 },
				{ -1.75	, 0.09 },
				{ -1.5	, 0.13 },
				{ -1.25	, 0.18 },
				{ -1	, 0.24 },
				{ -0.75	, 0.3 },
				{ -0.5	, 0.35 },
				{ -0.25	, 0.39 },
				{ 0	, 0.4 },
				{ 0.25	, 0.39 },
				{ 0.5	, 0.35 },
				{ 0.75	, 0.3 },
				{ 1	, 0.24 },
				{ 1.25	, 0.18 },
				{ 1.5	, 0.13 },
				{ 1.75	, 0.09 },
				{ 2	, 0.05 },
				{ 2.25	, 0.03 },
				{ 2.5	, 0.02 },
				{ 2.75	, 0.01 },
		};
		// serie 2 data
		double data2[][2] = {
				{ -3.75	, 0.01 },
				{ -3.5	, 0.02 },
				{ -3.25	, 0.03 },
				{ -3	, 0.05 },
				{ -2.75	, 0.09 },
				{ -2.5	, 0.13 },
				{ -2.25	, 0.18 },
				{ -2	, 0.24 },
				{ -1.75	, 0.3 },
				{ -1.5	, 0.35 },
				{ -1.25	, 0.39 },
				{-1	, 0.4 },
				{ -0.75	, 0.39 },
				{ -0.5	, 0.35 },
				{ -0.25	, 0.3 },
				{ 0	, 0.24 },
				{ 0.25	, 0.18 },
				{ 0.5	, 0.13 },
				{ 0.75	, 0.09 },
				{ 1	, 0.05 },
				{ 1.25	, 0.03 },
				{ 1.5	, 0.02 },
				{ 1.75	, 0.01 },
		};


		// first step: create plot
		XYPlot *plot = new XYPlot();

		XYDemoDataset *dataset = new XYDemoDataset();

		// add two series
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));

		// create line renderer
		XYLineRenderer *renderer = new XYLineRenderer();
		dataset->SetRenderer(renderer);

		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// set serie names to be displayed on legend
		dataset->SetSerieName(0, wxT("Serie 0"));
		dataset->SetSerieName(1, wxT("Serie 1"));

		// set legend
		plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		// set axis as scrolled, so chart panel can scroll its window.
		return chart;
	}
};

/**
 * Multiseries line xy chart demo.
 */
class XYDemo9 : public ChartDemo
{
public:
	XYDemo9()
	: ChartDemo(wxT("XY Demo 9 - sine"))
	{
	}

	virtual Chart *Create()
	{
		// first step: create plot
		XYPlot *plot = new XYPlot();

		SineFunction *dataset = new SineFunction(1, -10, 10, 0.1);

		// create line renderer
		XYLineRenderer *renderer = new XYLineRenderer();
		dataset->SetRenderer(renderer);

		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());

		// set axis as scrolled, so chart panel can scroll its window.
		return chart;
	}
};

ChartDemo *xyDemos[] = {
	new XYDemo1(),
	new XYDemo2(),
	new XYDemo3(),
	new XYDemo4(),
	new XYDemo5(),
	new XYDemo6(),
	new XYDemo7(),
	new XYDemo8(),
	new XYDemo9(),
};
int xyDemosCount = WXSIZEOF(xyDemos);
