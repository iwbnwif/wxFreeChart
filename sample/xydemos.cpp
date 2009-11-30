/////////////////////////////////////////////////////////////////////////////
// Name:	xydemos.cpp
// Purpose: xy demos
// Author:	Moskvichev Andrey V.
// Created:	2008/11/12
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xysimpledataset.h>

// for histogram demo
#include <wx/xy/xyhistorenderer.h>

// for dynamic dataset
#include <wx/xy/vectordataset.h>

#include <wx/xy/functions/sinefunction.h>

#include <math.h>


class XYDemo1 : public ChartDemo
{
public:
	XYDemo1()
	: ChartDemo(wxT("XY Demo 1 - simple"))
	{
	}

	virtual Chart *Create()
	{
		// serie xy data
		double data[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		// create dataset
		XYSimpleDataset *dataset = new XYSimpleDataset();

		// and add serie to it
		dataset->AddSerie((double *) data, WXSIZEOF(data));

		// set line renderer to dataset
		dataset->SetRenderer(new XYLineRenderer());

		// add our dataset to plot
		plot->AddDataset(dataset);

		// create left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// optional: set axis titles
		leftAxis->SetTitle(wxT("X"));
		bottomAxis->SetTitle(wxT("Y"));

		// add axes to plot
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
		// first serie xy data
		double data1[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};
		// second serie xy data
		double data2[][2] = {
				{ 45, 40, },
				{ 23, 16, },
				{ 43, 60, },
				{ 25, 7, },
				{ 66, 4, },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		// create dataset
		XYSimpleDataset *dataset = new XYSimpleDataset();

		// and add two series to it
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));

		// set line renderer to dataset
		dataset->SetRenderer(new XYLineRenderer());

		// add our dataset to plot
		plot->AddDataset(dataset);

		// create left and bottom number axes
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
		// first serie data
		double data1[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};
		// second serie data
		double data2[][2] = {
				{ 45, 40, },
				{ 23, 16, },
				{ 43, 60, },
				{ 25, 7, },
				{ 66, 4, },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		// create dataset
		XYSimpleDataset *dataset = new XYSimpleDataset();

		// and add to series to it
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));

		// set line renderer with symbols enabled and lines disabled
		dataset->SetRenderer(new XYLineRenderer(true, false));

		// add our dataset to plot
		plot->AddDataset(dataset);

		// create left and bottom number axes
		plot->AddAxis(new NumberAxis(AXIS_LEFT));
		plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// set serie names to be displayed on legend
		dataset->SetSerieName(0, wxT("First"));
		dataset->SetSerieName(1, wxT("Second"));

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
		// serie xy data
		double data[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		// create dataset and add serie to it
		XYSimpleDataset *dataset = new XYSimpleDataset();
		dataset->AddSerie((double *) data, WXSIZEOF(data));

		// set line renderer to dataset
		dataset->SetRenderer(new XYLineRenderer());

		// add our dataset to plot
		plot->AddDataset(dataset);

		// create left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// look at this code, we setup window, so
		// only part of data will be shown, not entire dataset as
		// in XYDemo1.
		bottomAxis->SetWindowPosition(10);
		bottomAxis->SetWindowWidth(10);
		bottomAxis->SetUseWindow(true);

		// add axes to plot
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

/**
 * Dataset for dynamic demo.
 */
class DynamicDemoDataset : public VectorDataset, public wxEvtHandler
{
public:
	DynamicDemoDataset();
	virtual ~DynamicDemoDataset();

private:
	wxTimer m_timer;

	void OnTimer(wxTimerEvent &ev);

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
	const double maxValue = 100.0;

	double r = rand();
	double y = maxValue * r / (double) RAND_MAX;
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

		// create dynamic dataset
		DynamicDemoDataset *dataset = new DynamicDemoDataset();

		// set line renderer to it
		dataset->SetRenderer(new XYLineRenderer());

		// add our dataset to plot
		plot->AddDataset(dataset);

		// create left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// we setup window
		//bottomAxis->SetWindow(0, 10);
		//bottomAxis->SetUseWindow(true);

		// add axes to plot
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

		// create dataset and add serie to it
		XYSimpleDataset *dataset = new XYSimpleDataset();
		dataset->AddSerie((double *) data, WXSIZEOF(data));

		// create histogram renderer with bar width = 10 and vertical bars
		XYHistoRenderer *histoRenderer = new XYHistoRenderer(10, true);

		// set bar areas to renderer
		// in this case, we set green bar with black outline for serie 0
		histoRenderer->SetBarArea(0, new FillAreaDraw(*wxBLACK_PEN, *wxGREEN_BRUSH));

		// set renderer to dataset
		dataset->SetRenderer(histoRenderer);

		// add our dataset to plot
		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// set bottom axis margins
		bottomAxis->SetMargins(15, 15);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());
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

		// create dataset
		XYSimpleDataset *dataset = new XYSimpleDataset();

		// add two series
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));

		// create histogram renderer with bar width = 10 and vertical bars
		XYHistoRenderer *histoRenderer = new XYHistoRenderer(10, true);

		// set bar area draw for two series
		histoRenderer->SetBarArea(0, new FillAreaDraw(*wxBLACK_PEN, *wxBLUE_BRUSH));
		histoRenderer->SetBarArea(1, new FillAreaDraw(*wxBLACK_PEN, *wxGREEN_BRUSH));

		// set renderer to dataset
		dataset->SetRenderer(histoRenderer);

		// add our dataset to plot
		plot->AddDataset(dataset);

		// add left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// set bottom axis margins
		bottomAxis->SetMargins(15, 15);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());
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

		// create dataset
		XYSimpleDataset *dataset = new XYSimpleDataset();

		// add two series
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));

		// create line renderer and set it to dataset
		XYLineRenderer *renderer = new XYLineRenderer();
		dataset->SetRenderer(renderer);

		// add our dataset to plot
		plot->AddDataset(dataset);

		// create left and bottom number axes
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

/**
 * Multiseries line xy chart demo.
 * Also it shows how to use legend.
 */
class XYDemo10 : public ChartDemo
{
public:
	XYDemo10()
	: ChartDemo(wxT("XY Demo 10 - lines"))
	{
	}

	virtual Chart *Create()
	{
		// serie 1 data
		double data1[][2] = {
				{ 1, 1 },
				{ 2, 4 },
				{ 3, 3 },
				{ 4, 5 },
				{ 5, 5 },
				{ 6, 7 },
				{ 7, 7 },
				{ 8, 8 },
		};
		// serie 2 data
		double data2[][2] = {
				{ 3, 4 },
				{ 4, 3 },
				{ 5, 2 },
				{ 6, 3 },
				{ 7, 6 },
				{ 8, 3 },
				{ 9, 4 },
				{ 10, 3 },
		};
		// serie 3 data
		double data3[][2] = {
				{ 1, 5 },
				{ 2, 7 },
				{ 3, 6 },
				{ 4, 8 },
				{ 5, 4 },
				{ 6, 4 },
				{ 7, 2 },
				{ 8, 1 },
		};

		// first step: create plot
		XYPlot *plot = new XYPlot();

		XYSimpleDataset *dataset = new XYSimpleDataset();

		// add three series
		dataset->AddSerie((double *) data1, WXSIZEOF(data1));
		dataset->AddSerie((double *) data2, WXSIZEOF(data2));
		dataset->AddSerie((double *) data3, WXSIZEOF(data3));

		// create line renderer
		// set it to draw lines and symbols.
		XYLineRenderer *renderer = new XYLineRenderer(true, true);

		// we can change line pen for serie, for example set short-dash
		// line style and width=2 for third serie
		renderer->SetSeriePen(1, wxThePenList->FindOrCreatePen(*wxGREEN, 2, wxSHORT_DASH));
		dataset->SetRenderer(renderer);

		// add dataset to plot
		plot->AddDataset(dataset);

		// create left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// set serie names to be displayed on legend
		dataset->SetSerieName(0, wxT("First"));
		dataset->SetSerieName(1, wxT("Second"));
		dataset->SetSerieName(2, wxT("Third"));

		// set legend
		plot->SetLegend(new Legend(wxBOTTOM, wxCENTER));

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
	new XYDemo10(),
};
int xyDemosCount = WXSIZEOF(xyDemos);
