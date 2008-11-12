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

#include "wx/bars/barplot.h"

#include "wx/axis/numberaxis.h"
#include "wx/axis/categoryaxis.h"

#include "wx/xy/xyhistorenderer.h"

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
 * Simple sample with one dataset, and one left, right and bottom axes.
 */
class BarDemo1 : public ChartDemo
{
public:
	BarDemo1()
	: ChartDemo(wxT("Bar demo 1"))
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

		// Set histogram renderer for it
		dataset->SetRenderer(new XYHistoRenderer());

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add left number axis
		plot->AddAxis(new NumberAxis(AXIS_LEFT));

		// Add bottom axis
		plot->AddAxis(new CategoryAxis(AXIS_BOTTOM));

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, wxT("Bar demo 1"));
	}
};

/**
 * Simple sample with one dataset, and one left, right and bottom axes.
 */
class BarDemo2 : public ChartDemo
{
public:
	BarDemo2()
	: ChartDemo(wxT("Bar demo 2"))
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

		// Set histogram renderer for it, with horizontal bars
		dataset->SetRenderer(new XYHistoRenderer(10, true));

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add bottom category axis
		plot->AddAxis(new CategoryAxis(AXIS_BOTTOM));

		// Add left number axis
		plot->AddAxis(new NumberAxis(AXIS_LEFT));

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, wxT("Bar demo 2"));
	}
};

class BarDemo3 : public ChartDemo
{
public:
	BarDemo3()
	: ChartDemo(wxT("Bar demo 3"))
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
				10,
				20,
				5,
				50,
				25,
			}
		};

		// Create dataset
		CategoryDataset *dataset = new BarSampleDataset(names, (double *) values, N(values), N(values[0]));

		// Set histogram renderer for it, with horizontal bars
		XYHistoRenderer *renderer = new XYHistoRenderer(10, false);
		renderer->SetBarArea(0, new GradientAreaBackground(*wxBLACK_PEN, wxColour(50, 0, 0), wxColour(255, 0, 0)));

		dataset->SetRenderer(renderer);

		// Create bar plot
		BarPlot *plot = new BarPlot();

		// Add left category axis
		plot->AddAxis(new CategoryAxis(AXIS_LEFT));

		// Add bottom number axis
		plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

		// Add dataset to plot
		plot->AddDataset(dataset);

		// Link first dataset with first horizontal axis
		plot->LinkDataHorizontalAxis(0, 0);

		// Link first dataset with first vertical axis
		plot->LinkDataVerticalAxis(0, 0);

		// and finally construct and return chart
		return new Chart(plot, wxT("Bar demo 3"));
	}
};

static ChartDemo *barDemos[] = {
		new BarDemo1(),
		new BarDemo2(),
		new BarDemo3(),
};
