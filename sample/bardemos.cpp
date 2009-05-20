/////////////////////////////////////////////////////////////////////////////
// Name:	bardemos.cpp
// Purpose: Code for bar chart demos
// Author:	Moskvichev Andrey V.
// Created:	2008/11/12
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

/*
 * This file contains demos for Category type charts.
 */

#include "democollection.h"

#include <wx/bars/barplot.h>

#include <wx/axis/numberaxis.h>
#include <wx/axis/categoryaxis.h>

#include <wx/xy/xyhistorenderer.h>

#include <wx/arrstr.h>

/**
 * Simple multiserie category dataset implementation.
 */
class BarSampleDataset : public CategoryDataset
{
public:
	/**
	 * @param names is category names array
	 * @param values is double-dimension item values array
	 * @param serieCount serie count
	 * @param count item in serie, in category dataset all series have equal item count
	 */
	BarSampleDataset(wxString *names, double *values, int serieCount, int count)
	{
		m_count = count;
		m_serieCount = serieCount;

		m_values = new double[count * serieCount];

		for (int serie = 0; serie < m_serieCount; serie++) {
			for (int m = 0; m < m_count; m++) {
				m_values[m + serie * m_count] = values[m + serie * m_count];
			}
		}

		m_names.Alloc(m_count);
		for (int n = 0; n < count; n++) {
			m_names.Add(names[n]);
		}
	}

	virtual ~BarSampleDataset()
	{
		delete m_values;
	}

	virtual double GetValue(int index, int serie)
	{
		return m_values[index + serie * m_count];
	}

	virtual int GetSerieCount()
	{
		return m_serieCount;
	}

	virtual wxString GetName(int index)
	{
		return m_names[index];
	}

	virtual int GetCount()
	{
		return m_count;
	}

	virtual wxString GetSerieName(int serie)
	{
		return wxString::Format(wxT("Serie %i"), serie + 1);
	}

private:
	int m_count;
	int m_serieCount;
	wxArrayString m_names;
	double *m_values;
};

/**
 * Simple demo with one dataset, and left and bottom axes.
 */
class BarDemo1 : public ChartDemo
{
public:
	BarDemo1()
	: ChartDemo(wxT("Bar demo 1 - one serie"))
	{
	}

	virtual Chart *Create()
	{
		wxString names[] = { // category names
				wxT("Cat 1"),
				wxT("Cat 2"),
				wxT("Cat 3"),
				wxT("Cat 4"),
				wxT("Cat 5"),
		};
		double values[][5] = {
			{ // serie 1 values - we have only one serie
				10.0,
				20.0,
				5.0,
				50.0,
				25.0,
			},
		};

		// Create dataset
		CategoryDataset *dataset = new BarSampleDataset(names, (double *) values, N(values), N(values[0]));

		BarType *barType = new NormalBarType(10);
		barType->SetBarDraw(0, new FillAreaDraw(*wxBLACK_PEN, *wxRED_BRUSH));

		// Set histogram renderer for it
		dataset->SetRenderer(new BarRenderer(barType));

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add left number axis
		plot->AddAxis(new NumberAxis(AXIS_LEFT));

		// Add bottom axis
		CategoryAxis *bottomAxis = new CategoryAxis(AXIS_BOTTOM);
		bottomAxis->SetMargins(10, 10);
		plot->AddAxis(bottomAxis);

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, GetName());
	}
};

/**
 * Simple demo with one dataset, and left and bottom axes.
 */
class BarDemo2 : public ChartDemo
{
public:
	BarDemo2()
	: ChartDemo(wxT("Bar demo 2 - one category"))
	{
	}

	virtual Chart *Create()
	{
		wxString names[] = { // category names
				wxT("Cat 1"),
		};
		double values[][1] = {
			{ // serie 1 values - we have only one serie
				10.0,
			},
		};

		// Create dataset
		CategoryDataset *dataset = new BarSampleDataset(names, (double *) values, N(values), N(values[0]));

		BarType *barType = new NormalBarType(10);
		barType->SetBarDraw(0, new FillAreaDraw(*wxBLACK_PEN, *wxRED_BRUSH));

		// Set histogram renderer for it
		dataset->SetRenderer(new BarRenderer(barType));

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add left number axis
		plot->AddAxis(new NumberAxis(AXIS_LEFT));

		// Add bottom axis
		CategoryAxis *bottomAxis = new CategoryAxis(AXIS_BOTTOM);
		bottomAxis->SetMargins(10, 10);
		plot->AddAxis(bottomAxis);

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, GetName());
	}
};

/**
 * Simple demo with one dataset having 2 series, and left and bottom axes.
 * Bars are horizontal.
 */
class BarDemo3 : public ChartDemo
{
public:
	BarDemo3()
	: ChartDemo(wxT("Bar demo 3 - normal bars"))
	{
	}

	virtual Chart *Create()
	{
		wxString names[] = { // category names
				wxT("Cat 1"),
				wxT("Cat 2"),
				wxT("Cat 3"),
				wxT("Cat 4"),
				wxT("Cat 5"),
		};
		double values[][5] = {
			{ // serie 1 values
				10,
				20,
				5,
				50,
				25,
			},
			{ // serie 2 values
				16,
				10,
				15,
				30,
				45,
			},
		};

		// Create dataset
		CategoryDataset *dataset = new BarSampleDataset(names, (double *) values, N(values), N(values[0]));

		BarType *barType = new NormalBarType(10);
		// some eyes-candy: gradient bars
		barType->SetBarDraw(0, new GradientAreaDraw(*wxBLACK_PEN, wxColour(50, 0, 0), wxColour(255, 0, 0)));
		barType->SetBarDraw(1, new GradientAreaDraw(*wxBLACK_PEN, wxColour(0, 50, 0), wxColour(0, 255, 0)));

		// Set bar renderer for it, with normal bars
		BarRenderer *renderer = new BarRenderer(barType);

		// assign renderer to dataset - necessary step
		dataset->SetRenderer(renderer);

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add left category axis
		CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
		leftAxis->SetMargins(20, 20); // setup margins, so bars will fit to plot.
		plot->AddAxis(leftAxis);

		// Add bottom number axis
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
		bottomAxis->SetMargins(0, 5);
		plot->AddAxis(bottomAxis);

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, GetName());
	}
};

/**
 * Stacked bars demo.
 */
class BarDemo4 : public ChartDemo
{
public:
	BarDemo4()
	: ChartDemo(wxT("Bar demo 4 - stacked bars"))
	{
	}

	virtual Chart *Create()
	{
		wxString names[] = { // category names
				wxT("Cat 1"),
				wxT("Cat 2"),
				wxT("Cat 3"),
				wxT("Cat 4"),
				wxT("Cat 5"),
		};
		double values[][5] = {
			{ // serie 1 values
				10,
				20,
				5,
				50,
				25,
			},
			{ // serie 2 values
				16,
				10,
				15,
				30,
				45,
			},
		};

		// Create dataset
		CategoryDataset *dataset = new BarSampleDataset(names, (double *) values, N(values), N(values[0]));


		BarType *barType = new StackedBarType(10, 0);
		// some eyes-candy: gradient bars
		barType->SetBarDraw(0, new GradientAreaDraw(*wxBLACK_PEN, wxColour(50, 0, 0), wxColour(255, 0, 0)));
		barType->SetBarDraw(1, new GradientAreaDraw(*wxBLACK_PEN, wxColour(0, 50, 0), wxColour(0, 255, 0)));

		// Set bar renderer for it, with stacked bar type
		BarRenderer *renderer = new BarRenderer(barType);

		// assign renderer to dataset - necessary step
		dataset->SetRenderer(renderer);

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add left category axis
		CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
		leftAxis->SetMargins(10, 10);
		plot->AddAxis(leftAxis);

		// Add bottom number axis
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
		bottomAxis->SetMargins(0, 5);
		plot->AddAxis(bottomAxis);

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, GetName());
	}
};

/**
 * Layered bars demo.
 */
class BarDemo5 : public ChartDemo
{
public:
	BarDemo5()
	: ChartDemo(wxT("Bar demo 5 - layered bars"))
	{
	}

	virtual Chart *Create()
	{
		wxString names[] = { // category names
				wxT("Cat 1"),
				wxT("Cat 2"),
				wxT("Cat 3"),
				wxT("Cat 4"),
				wxT("Cat 5"),
		};
		double values[][5] = {
			{ // serie 1 values
				10,
				20,
				5,
				50,
				25,
			},
			{ // serie 2 values
				16,
				10,
				15,
				30,
				45,
			},
		};

		// Create dataset
		CategoryDataset *dataset = new BarSampleDataset(names, (double *) values, N(values), N(values[0]));

		// create layered bar type with width=20 and base=0
		BarType *barType = new LayeredBarType(20, 0);

		// some eyes-candy: gradient bars
		barType->SetBarDraw(0, new GradientAreaDraw(*wxBLACK_PEN, wxColour(50, 0, 0), wxColour(255, 0, 0)));
		barType->SetBarDraw(1, new GradientAreaDraw(*wxBLACK_PEN, wxColour(0, 50, 0), wxColour(0, 255, 0)));

		// Set bar renderer for it, with layered bar type
		BarRenderer *renderer = new BarRenderer(barType);

		// assign renderer to dataset
		dataset->SetRenderer(renderer);

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add left category axis
		CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
		leftAxis->SetMargins(20, 20);
		plot->AddAxis(leftAxis);

		// Add bottom number axis
		plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, GetName());
	}
};

/**
 * Layered date bars demo.
 */
class BarDemo6 : public ChartDemo
{
public:
	BarDemo6()
	: ChartDemo(wxT("Bar demo 6 - layered date bars"))
	{
	}

	virtual Chart *Create()
	{
		// TODO: !!! remake this demo to use dates, not string representation of years!
		wxString names[] = { // category names
				wxT("2000"),
				wxT("2001"),
				wxT("2002"),
				wxT("2003"),
				wxT("2004"),
				wxT("2005"),
				wxT("2006"),
				wxT("2007"),
		};
		double values[][8] = {
			{ // serie 1 values
					771994,	718712,	682422,	713415,	807516,	894631,	1023109, 1148481,
			},
			{ // serie 2 values
					298603,	286184,	292299,	304342,	353072,	389122,	433905,	497245,
			},
		};

		// Create dataset
		CategoryDataset *dataset = new BarSampleDataset(names, (double *) values, N(values), N(values[0]));

		// create layered bar type with width=20 and base=0
		BarType *barType = new LayeredBarType(20, 0);

		// some eyes-candy: gradient bars
		barType->SetBarDraw(0, new GradientAreaDraw(*wxBLACK_PEN, wxColour(50, 0, 0), wxColour(255, 0, 0)));
		barType->SetBarDraw(1, new GradientAreaDraw(*wxBLACK_PEN, wxColour(0, 50, 0), wxColour(0, 255, 0)));

		// Set bar renderer for it, with layered bar type
		BarRenderer *renderer = new BarRenderer(barType);

		// assign renderer to dataset
		dataset->SetRenderer(renderer);

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add bottom category axis
		CategoryAxis *bottomAxis = new CategoryAxis(AXIS_BOTTOM);
		bottomAxis->SetMargins(20, 20);
		plot->AddAxis(bottomAxis);

		// Add left number axis
		plot->AddAxis(new NumberAxis(AXIS_LEFT));

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, wxT("USA export goods/services"));
	}
};

ChartDemo *barDemos[] = {
		new BarDemo1(),
		//new BarDemo2(),
		new BarDemo3(),
		new BarDemo4(),
		new BarDemo5(),
		new BarDemo6(),
};
int barDemosCount = N(barDemos);
