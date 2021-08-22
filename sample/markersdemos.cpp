/////////////////////////////////////////////////////////////////////////////
// Name:    markersdemos.cpp
// Purpose: markers usage demos
// Author:    Moskvichev Andrey V.
// Created:    2010/02/15
// Copyright:    (c) 2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
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
        wxVector<wxRealPoint> datapoints;
        datapoints.push_back(wxRealPoint(10, 20));
        datapoints.push_back(wxRealPoint(13, 16));
        datapoints.push_back(wxRealPoint(7, 30));
        datapoints.push_back(wxRealPoint(15, 34));
        datapoints.push_back(wxRealPoint(25, 4));

        // first step: create plot
        XYPlot *plot = new XYPlot();

        // create dataset
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // and add serie to it
        dataset->AddSerie(new XYSerie(datapoints));

        // set line renderer to dataset
        dataset->SetRenderer(new XYLineRenderer());

        // create line marker
        LineMarker *lineMarker = new LineMarker(wxPen(*wxBLUE, 2, wxPENSTYLE_SOLID));

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
    : ChartDemo(wxT("Markers Demo 2 - range and line"))
    {
    }

    virtual Chart *Create()
    {
        // serie xy data
        wxVector<wxRealPoint> datapoints;
        datapoints.push_back(wxRealPoint(10, 20));
        datapoints.push_back(wxRealPoint(13, 16));
        datapoints.push_back(wxRealPoint(14, 30));
        datapoints.push_back(wxRealPoint(15, 34));
        datapoints.push_back(wxRealPoint(25, 4));

        // first step: create plot
        XYPlot *plot = new XYPlot();

        // create dataset
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // and add serie to it
        dataset->AddSerie(new XYSerie(datapoints));

        // set line renderer to dataset
        dataset->SetRenderer(new XYLineRenderer());

        // create first range marker
        RangeMarker *rangeMarker1 = new RangeMarker(new FillAreaDraw(wxColour(80, 80, 255), wxColour(200, 200, 250)));

        // set value to be marked, in our case vertical range [15; 20]
        rangeMarker1->SetVerticalRange(15, 20);

        // and add marker to dataset
        dataset->AddMarker(rangeMarker1);

        // create line marker
        LineMarker *lineMarker = new LineMarker(wxColour(80, 80, 255), 2);

        // set value to be marked, in our case horizontal value 15
        lineMarker->SetHorizontalLine(25);

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

ChartDemo *markersDemos[] = {
    new MarkersDemo1(),
    new MarkersDemo2(),
};
int markersDemosCount = WXSIZEOF(markersDemos);
