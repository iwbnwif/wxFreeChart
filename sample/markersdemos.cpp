/////////////////////////////////////////////////////////////////////////////
// Name:        markersdemos.cpp
// Purpose:     markers usage demos
// Author:      Moskvichev Andrey V.
// Created:     2010/02/15
// Copyright:   (c) 2010 Moskvichev Andrey V.
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/marker.h>
#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>


class MarkersDemo1 : public ChartDemo
{
public:
    MarkersDemo1()
    : ChartDemo(wxT("Markers Demo 1 - Line Marker"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for series.
        DataSeries* series = new DataSeries("Series 1");
        series->AddPoint(new BiDataPoint(10.0, 20.0));
        series->AddPoint(new BiDataPoint(13.0, 16.0));
        series->AddPoint(new BiDataPoint(7.0, 30.0));
        series->AddPoint(new BiDataPoint(15.0, 34.0));
        series->AddPoint(new BiDataPoint(25.0, 4.0));

        BiDataSet* dataset = new BiDataSet("Markers Demo 1");

        // Add the series to the data set.
        dataset->AddSeries(series);

        // Set a XY line renderer for the dataset.
        dataset->SetRenderer(new XYLineRenderer());
        
        // Create a line marker and set the value to be marked (20 on the x-axis).
        LineMarker *lineMarker = new LineMarker(wxPen(*wxBLUE, 2, wxPENSTYLE_SOLID));
        lineMarker->SetVerticalLine(20);

        // Add the marker to dataset.
        dataset->AddMarker(lineMarker);

        // Create an XY plot.
        XYPlot *plot = new XYPlot();

        // Create left and bottom number axes.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        
        // Optional: set axis titles.
        leftAxis->SetTitle(wxT("X Values"));
        bottomAxis->SetTitle(wxT("Y Values"));

        // Add axes and dataset to plot.
        plot->AddObjects(dataset, leftAxis, bottomAxis);

        // Create the chart.
        return new Chart(plot, GetName());    
    }
};

class MarkersDemo2 : public ChartDemo
{
public:
    MarkersDemo2()
    : ChartDemo(wxT("Markers Demo 2 - Range and Line"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for series.
        DataSeries* series = new DataSeries("Series 1");
        series->AddPoint(new BiDataPoint(10.0, 20.0));
        series->AddPoint(new BiDataPoint(13.0, 16.0));
        series->AddPoint(new BiDataPoint(7.0, 30.0));
        series->AddPoint(new BiDataPoint(15.0, 34.0));
        series->AddPoint(new BiDataPoint(25.0, 4.0));

        BiDataSet* dataset = new BiDataSet("Markers Demo 2");

        // Add the series to the data set.
        dataset->AddSeries(series);

        // Set a XY line renderer for the dataset.
        dataset->SetRenderer(new XYLineRenderer());
        
        // Create a range marker and set the range to be marked (range 15 - 20 on the x-axis).
        RangeMarker *rangeMarker = new RangeMarker(new FillAreaDraw(wxColour(80, 80, 255), wxColour(200, 200, 250)));
        rangeMarker->SetVerticalRange(15, 20);

        // Create a line marker and set the value to be marked (20 on the x-axis).
        LineMarker *lineMarker = new LineMarker(wxPen(*wxRED, 2, wxPENSTYLE_DOT_DASH));
        lineMarker->SetVerticalLine(20);

        // Add the markers to dataset
        dataset->AddMarker(rangeMarker);
        dataset->AddMarker(lineMarker);

        // Create an XY plot.
        XYPlot *plot = new XYPlot();

        // Create left and bottom number axes.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        
        // Optional: set axis titles.
        leftAxis->SetTitle(wxT("X Values"));
        bottomAxis->SetTitle(wxT("Y Values"));

        // Add axes and dataset to plot.
        plot->AddObjects(dataset, leftAxis, bottomAxis);

        // Create the chart.
        return new Chart(plot, GetName());    
    }
};

ChartDemo *markersDemos[] = {
    new MarkersDemo1(),
    new MarkersDemo2(),
};
int markersDemosCount = WXSIZEOF(markersDemos);
