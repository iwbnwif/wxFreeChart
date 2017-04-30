/////////////////////////////////////////////////////////////////////////////
// Name:    timeseriesdemos.cpp
// Purpose: time series demos code
// Author:    Moskvichev Andrey V.
// Created:    30.11.2008
// Copyright:    (c) 2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>

#include <wx/axis/numberaxis.h>
#include <wx/axis/dateaxis.h>

#include <wx/xy/timeseriesdataset.h>

/**
 *
 */
class TimeSeriesDemo1 : public ChartDemo
{
public:
    TimeSeriesDemo1()
    : ChartDemo(wxT("Time Series Demo 1"))
    {
    }

    virtual Chart *Create()
    {
        // Data
        double data[] = 
        {
             64.09,
             63.34,
             61.41,
             62.00,
             61.71,
             63.39,
             63.64,
             63.61,
             65.11,
             65.72,
             66.89,
             66.68,
             66.51,
             66.40,
             67.27,
             67.66,
        };
        
        // Dates
        const wxChar *strDates[] = 
        {
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

        time_t times[WXSIZEOF(strDates)];

        wxDateTime dt;
        for (size_t n = 0; n < WXSIZEOF(strDates); n++) 
        {
            dt.ParseFormat(strDates[n], wxT("%Y%m%d"));
            times[n] = dt.GetTicks();
        }

        // First step: create a plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        TimeSeriesDataset *dataset = new TimeSeriesDataset(data, times, WXSIZEOF(data));

        // Third step: define a renderer for the dataset.
        Renderer* renderer = new XYLineRenderer();
        renderer->SetSerieColour(0, new wxColour(255,0,0));
        dataset->SetRenderer(renderer);
        

        // Fourth step: add the dataset to the plot.
        plot->AddDataset(dataset);

        // Add left number and bottom date axes.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        leftAxis->SetFixedBounds(61.0, 68.0);
        leftAxis->SetMinorIntervalCount(4);
        leftAxis->SetMajorGridlinePen(wxColour(100, 100, 100));
        leftAxis->SetMinorGridlinePen(wxColour(150, 150, 150));
        
        DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);
        bottomAxis->SetVerticalLabelText(true);
        bottomAxis->SetDateFormat(wxT("%d-%m"));
        bottomAxis->SetMajorGridlinePen(wxColour(100, 100, 100));

        // Add axes to plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // Link axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);
        
        // Define the plot background and legend.
        plot->SetBackground(new NoAreaDraw()); // new GradientAreaDraw(*wxTRANSPARENT_PEN, wxColour(100, 100, 250), wxColour(200, 220, 250)));
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // And finally create the chart.
        Chart *chart = new Chart(plot, GetName());
        chart->SetBackground(new GradientAreaDraw(*wxTRANSPARENT_PEN, wxColour(200, 220, 250), *wxWHITE, wxSOUTH));
        
        //chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

class TimeSeriesDemo2 : public ChartDemo
{
public:
    TimeSeriesDemo2()
    : ChartDemo(wxT("Time series Demo 2"))
    {
    }

    virtual Chart *Create()
    {
        // data
        double data[] = {
             64.09,
             63.34,
             61.41,
             62.00,
             61.71,
             63.39,
             63.64,
             63.61,
             65.11,
             65.72,
             66.89,
             66.68,
             66.51,
             66.40,
             67.27,
             67.66,
        };
        // dates
        const wxChar *strDates[] = {
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

        time_t times[WXSIZEOF(strDates)];

        wxDateTime dt;
        for (size_t n = 0; n < WXSIZEOF(strDates); n++) {
            dt.ParseFormat(strDates[n], wxT("%Y%m%d"));
            times[n] = dt.GetTicks();
        }

        // first step: create plot
        XYPlot *plot = new XYPlot();

        TimeSeriesDataset *dataset = new TimeSeriesDataset(data, times, WXSIZEOF(data));

        dataset->SetRenderer(new XYLineRenderer());

        plot->AddDataset(dataset);

        // add left number and bottom date axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);

        // setup window
        //bottomAxis->SetWindow(0, 10);
        //bottomAxis->SetUseWindow(true);

        bottomAxis->SetVerticalLabelText(true);
        bottomAxis->SetDateFormat(wxT("%d-%m"));

        // add axes to first plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());

        //chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

ChartDemo *timeSeriesDemos[] = {
    new TimeSeriesDemo1(),
};
int timeSeriesDemosCount = WXSIZEOF(timeSeriesDemos);
