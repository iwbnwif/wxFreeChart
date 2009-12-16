/////////////////////////////////////////////////////////////////////////////
// Name:	multipleaxisdemos.cpp
// Purpose: This file contains source code, that demonstrates how to
//          multiple axis charts.
// Author:	Moskvichev Andrey V.
// Created:	2009/04/03
// Copyright:	(c) 2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////


#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/xy/xylinerenderer.h>

#include <wx/axis/numberaxis.h>

/**
 * Multiple axis demo.
 */
class MultipleAxisDemo1 : public ChartDemo
{
public:
	MultipleAxisDemo1()
	: ChartDemo(wxT("Multiple axis Demo 1"))
	{
	}

	virtual Chart *Create()
	{
		// first dataset values
		double values1[][2] = {
				{ 1, 1 },
				{ 2, 3 },
				{ 5, 4 },
				{ 6, 3 },
				{ 7, 6 },
				{ 8, 6 },
				{ 9, 4 },
		};

		// second dataset values
		double values2[][2] = {
				{ 0, 0 },
				{ 2, -1 },
				{ 4, 6 },
				{ 5, 2 },
				{ 7, 8 },
				{ 8, 4 },
				{ 9, -2 },
		};

		// colors for first and second datasets
		wxColour color1 = wxColour(255, 0, 0);
		wxColour color2 = wxColour(0, 0, 255);

		// create xy plot
		XYPlot *plot = new XYPlot();

		// create first dataset
		XYSimpleDataset *dataset1 = new XYSimpleDataset();
		// add serie to it
		dataset1->AddSerie((double *) values1, WXSIZEOF(values1));

		// create second dataset
		XYSimpleDataset *dataset2 = new XYSimpleDataset();
		// add serie to it
		dataset2->AddSerie((double *) values2, WXSIZEOF(values2));

		// create renderer for first dataset
		XYLineRenderer *renderer1 = new XYLineRenderer();
		renderer1->SetSerieColour(0, &color1);

		// add first dataset to plot
		plot->AddDataset(dataset1);

		// set it to first dataset
		dataset1->SetRenderer(renderer1);

		// create renderer for second dataset
		XYLineRenderer *renderer2 = new XYLineRenderer();
		renderer2->SetSerieColour(0, &color2);

		// set it to second dataset
		dataset2->SetRenderer(renderer2);

		// add second dataset to plot
		plot->AddDataset(dataset2);

		// create left axis for first dataset
		NumberAxis *leftAxis1 = new NumberAxis(AXIS_LEFT);
		// set label text colour same as lines
		leftAxis1->SetLabelTextColour(color1);
		// set label lines colour same as lines
		leftAxis1->SetLabelPen(*wxThePenList->FindOrCreatePen(color1, 1, wxSOLID));
		plot->AddAxis(leftAxis1);

		// create left axis for second dataset
		NumberAxis *leftAxis2 = new NumberAxis(AXIS_LEFT);
		// set label text colour same as lines
		leftAxis2->SetLabelTextColour(color2);
		// set label lines colour same as lines
		leftAxis2->SetLabelPen(*wxThePenList->FindOrCreatePen(color2, 1, wxSOLID));
		plot->AddAxis(leftAxis2);

		// create bottom axis for first and second dataset
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
		plot->AddAxis(bottomAxis);

		// link first dataset with first left axis
		plot->LinkDataVerticalAxis(0, 0);
		// link second dataset with second left axis
		plot->LinkDataVerticalAxis(1, 1);

		// link first and second datasets with bottom axis
		plot->LinkDataHorizontalAxis(0, 0);
		plot->LinkDataHorizontalAxis(1, 0);

		return new Chart(plot, GetName());
	}
};

/**
 * Multiple axis demo.
 */
class MultipleAxisDemo2 : public ChartDemo
{
public:
	MultipleAxisDemo2()
	: ChartDemo(wxT("Multiple axis Demo 2"))
	{
	}

	virtual Chart *Create()
	{
		// first dataset values
		double values1[][2] = {
				{ 1, 1 },
				{ 2, 3 },
				{ 5, 4 },
				{ 6, 3 },
				{ 7, 6 },
				{ 8, 6 },
				{ 9, 4 },
		};

		// second dataset values
		double values2[][2] = {
				{ 0, 0 },
				{ 2, -1 },
				{ 4, 6 },
				{ 5, 2 },
				{ 7, 8 },
				{ 8, 4 },
				{ 9, -2 },
		};

		// colors for first and second datasets
		wxColour color1 = wxColour(255, 0, 0);
		wxColour color2 = wxColour(0, 0, 255);

		// create xy plot
		XYPlot *plot = new XYPlot();

		// create first dataset
		XYSimpleDataset *dataset1 = new XYSimpleDataset();
		// add serie to it
		dataset1->AddSerie((double *) values1, WXSIZEOF(values1));

		// create second dataset
		XYSimpleDataset *dataset2 = new XYSimpleDataset();
		// add serie to it
		dataset2->AddSerie((double *) values2, WXSIZEOF(values2));

		// create renderer for first dataset
		XYLineRenderer *renderer1 = new XYLineRenderer();
		renderer1->SetSerieColour(0, &color1);

		// add first dataset to plot
		plot->AddDataset(dataset1);

		// set it to first dataset
		dataset1->SetRenderer(renderer1);

		// create renderer for second dataset
		XYLineRenderer *renderer2 = new XYLineRenderer();
		renderer2->SetSerieColour(0, &color2);

		// set it to second dataset
		dataset2->SetRenderer(renderer2);

		// add second dataset to plot
		plot->AddDataset(dataset2);

		// create left axis for first dataset
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		leftAxis->SetLabelTextColour(color1);
		plot->AddAxis(leftAxis);

		// create left axis for second dataset
		NumberAxis *rightAxis = new NumberAxis(AXIS_RIGHT);
		rightAxis->SetLabelTextColour(color2);
		plot->AddAxis(rightAxis);

		// create top axis for first dataset
		NumberAxis *topAxis = new NumberAxis(AXIS_TOP);
		topAxis->SetLabelTextColour(color1);
		plot->AddAxis(topAxis);

		// create bottom axis for second dataset
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
		bottomAxis->SetLabelTextColour(color2);
		plot->AddAxis(bottomAxis);

		// link first dataset with left axis
		plot->LinkDataVerticalAxis(0, 0);
		// link second dataset with right axis
		plot->LinkDataVerticalAxis(1, 1);

		// link first dataset with top axis
		plot->LinkDataHorizontalAxis(0, 0);

		// link second dataset with bottom axis
		plot->LinkDataHorizontalAxis(1, 1);

		return new Chart(plot, GetName());
	}
};

ChartDemo *multipleAxisDemos[] = {
		new MultipleAxisDemo1(),
		new MultipleAxisDemo2(),
};
int multipleAxisDemosCount = WXSIZEOF(multipleAxisDemos);
