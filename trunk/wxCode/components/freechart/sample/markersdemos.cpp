/////////////////////////////////////////////////////////////////////////////
// Name:	markersdemos.cpp
// Purpose: markers usage demos
// Author:	Moskvichev Andrey V.
// Created:	2010/02/15
// Copyright:	(c) 2010 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xysimpledataset.h>

#include <wx/marker.h>

#include <math.h>


class MarkersDemo1 : public ChartDemo
{
public:
	MarkersDemo1()
	: ChartDemo(wxT("Markers Demo 1 - line"))
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

		// create line marker
		LineMarker *lineMarker = new LineMarker(wxPen(*wxBLUE, 2, wxSOLID));

		// set value to be marked, in our case vertical line with x=20
		lineMarker->SetVerticalLine(20);

		// and add marker to dataset
		dataset->AddMarker(lineMarker);

		// create left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// add axes and dataset to plot
		plot->AddObjects(dataset, leftAxis, bottomAxis);

		// and finally create chart
		return new Chart(plot, GetName());
	}
};


class MarkersDemo2 : public ChartDemo
{
public:
	MarkersDemo2()
	: ChartDemo(wxT("Markers Demo 2 - range"))
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

		// create line marker
		RangeMarker *rangeMarker = new RangeMarker(new FillAreaDraw(wxColour(80, 80, 255), wxColour(200, 200, 250)));

		// set value to be marked, in our case vertical line with x=20
		rangeMarker->SetVerticalRange(15, 20);

		// and add marker to dataset
		dataset->AddMarker(rangeMarker);

		// create left and bottom number axes
		NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
		NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

		// add axes and dataset to plot
		plot->AddObjects(dataset, leftAxis, bottomAxis);

		// and finally create chart
		return new Chart(plot, GetName());
	}
};

ChartDemo *markersDemos[] = {
	new MarkersDemo1(),
	new MarkersDemo2(),
};
int markersDemosCount = WXSIZEOF(markersDemos);
