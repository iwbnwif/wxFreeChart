/////////////////////////////////////////////////////////////////////////////
// Name:	combinedaxisdemos.cpp
// Purpose: This file contains source code, that demonstrates how to
//          combined axis charts.
// Author:	Moskvichev Andrey V.
// Created:	2009/04/03
// Copyright:	(c) 2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xyhistorenderer.h>
#include <wx/xy/xysimpledataset.h>

#include <wx/multiplot.h>

/**
 * Combined axis demo.
 */
class CombinedAxisDemo1 : public ChartDemo
{
public:
	CombinedAxisDemo1()
	: ChartDemo(wxT("Combined axis Demo 1 - left axis"))
	{
	}

	virtual Chart *Create()
	{
		// first plot data
		double data1[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 7, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};
		// second plot data
		double data2[][2] = {
				{ 45, 40, },
				{ 23, 16, },
				{ 43, 60, },
				{ 25, 7, },
				{ 66, 4, },
		};

		MultiPlot *multiPlot = new MultiPlot(1, 0, 5, 5);

		// create left axis, that will be shared between two plots
		NumberAxis *sharedLeftAxis = new NumberAxis(AXIS_LEFT);

		// create first plot
		XYPlot *plot1 = new XYPlot();

		// create dataset
		XYSimpleDataset *dataset1 = new XYSimpleDataset();

		// and add serie to it
		dataset1->AddSerie((double *) data1, WXSIZEOF(data1));

		// set line renderer to dataset
		dataset1->SetRenderer(new XYLineRenderer());

		// add our dataset to plot
		plot1->AddDataset(dataset1);

		// create axis share for first plot to share leftAxis between plots
		AxisShare *leftAxis1 = new AxisShare(sharedLeftAxis);
		// and make it visible for first plot
		leftAxis1->SetShareVisible(true);

		// create bottom number axes
		NumberAxis *bottomAxis1 = new NumberAxis(AXIS_BOTTOM);
		bottomAxis1->SetVerticalLabelText(true);
		bottomAxis1->SetMargins(10, 15);

		// add axes to plot
		plot1->AddAxis(leftAxis1);
		plot1->AddAxis(bottomAxis1);

		// link axes and dataset
		plot1->LinkDataVerticalAxis(0, 0);
		plot1->LinkDataHorizontalAxis(0, 0);

		//
		// create second plot
		//
		XYPlot *plot2 = new XYPlot();

		// create dataset
		XYSimpleDataset *dataset2 = new XYSimpleDataset();

		// and add serie to it
		dataset2->AddSerie((double *) data2, WXSIZEOF(data2));

		// set line renderer to dataset
		dataset2->SetRenderer(new XYLineRenderer());

		// add our dataset to plot
		plot2->AddDataset(dataset2);

		// create axis share for second plot to share leftAxis between plots
		// by default it will be invisible
		AxisShare *leftAxis2 = new AxisShare(sharedLeftAxis);

		// create bottom number axes
		NumberAxis *bottomAxis2 = new NumberAxis(AXIS_BOTTOM);
		bottomAxis2->SetMargins(15, 10);
		bottomAxis2->SetVerticalLabelText(true);

		// add axes to plot
		plot2->AddAxis(leftAxis2);
		plot2->AddAxis(bottomAxis2);

		// link axes and dataset
		plot2->LinkDataVerticalAxis(0, 0);
		plot2->LinkDataHorizontalAxis(0, 0);

		// add first plot to multiplot
		multiPlot->AddPlot(plot1);

		// add second plot to multiplot
		multiPlot->AddPlot(plot2);

		// and finally create chart
		return new Chart(multiPlot, GetName());
	}
};

class CombinedAxisDemo2 : public ChartDemo
{
public:
	CombinedAxisDemo2()
	: ChartDemo(wxT("Combined axis Demo 2 - bottom axis"))
	{
	}

	virtual Chart *Create()
	{
		// first plot data
		double data1[][2] = {
				{ 10, 20, },
				{ 13, 16, },
				{ 17, 30, },
				{ 15, 34, },
				{ 25, 4, },
		};
		// second plot data
		double data2[][2] = {
				{ 45, 40, },
				{ 23, 16, },
				{ 35, 60, },
				{ 15, 7, },
				{ 5, 20 },
				{ 66, 4, },
		};

		MultiPlot *multiPlot = new MultiPlot(0, 1, 5, 5);

		// create left axis, that will be shared between two plots
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// create first plot
		XYPlot *plot1 = new XYPlot();

		// create dataset
		XYSimpleDataset *dataset1 = new XYSimpleDataset();

		// and add serie to it
		dataset1->AddSerie((double *) data1, WXSIZEOF(data1));

		// set line renderer to dataset
		dataset1->SetRenderer(new XYLineRenderer());

		// add our dataset to plot
		plot1->AddDataset(dataset1);

		// create left number axes
		NumberAxis *leftAxis1 = new NumberAxis(AXIS_LEFT);

		// create axis share for second plot to share leftAxis between plots
		// by default it will be invisible
		AxisShare *bottomAxis1 = new AxisShare(bottomAxis);

		// add axes to plot
		plot1->AddAxis(leftAxis1);
		plot1->AddAxis(bottomAxis1);

		// link axes and dataset
		plot1->LinkDataVerticalAxis(0, 0);
		plot1->LinkDataHorizontalAxis(0, 0);

		//
		// create second plot
		//
		XYPlot *plot2 = new XYPlot();

		// create dataset
		XYSimpleDataset *dataset2 = new XYSimpleDataset();

		// and add serie to it
		dataset2->AddSerie((double *) data2, WXSIZEOF(data2));

		// set histogram renderer to dataset
		XYHistoRenderer *renderer2 = new XYHistoRenderer();
		renderer2->SetBarArea(0, new FillAreaDraw(*wxBLACK, *wxGREEN));

		dataset2->SetRenderer(renderer2);

		// add our dataset to plot
		plot2->AddDataset(dataset2);

		// create left number axes
		NumberAxis *leftAxis2 = new NumberAxis(AXIS_LEFT);

		// create axis share for second plot to share leftAxis between plots
		AxisShare *bottomAxis2 = new AxisShare(bottomAxis);
		// and make it visible for second plot
		bottomAxis2->SetShareVisible(true);

		// add axes to plot
		plot2->AddAxis(leftAxis2);
		plot2->AddAxis(bottomAxis2);

		// link axes and dataset
		plot2->LinkDataVerticalAxis(0, 0);
		plot2->LinkDataHorizontalAxis(0, 0);

		// add first plot to multiplot
		multiPlot->AddPlot(plot1);

		// add second plot to multiplot
		multiPlot->AddPlot(plot2);

		// and finally create chart
		return new Chart(multiPlot, GetName());
	}
};

ChartDemo *combinedAxisDemos[] = {
		new CombinedAxisDemo1(),
		new CombinedAxisDemo2(),
};
int combinedAxisDemosCount = WXSIZEOF(combinedAxisDemos);
