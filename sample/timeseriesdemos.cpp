/////////////////////////////////////////////////////////////////////////////
// Name:    timeseriesdemos.cpp
// Purpose: time series demos code
// Author:    Moskvichev Andrey V.
// Created:    30.11.2008
// Copyright:    (c) 2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/axis/numberaxis.h>
#include <wx/axis/dateaxis.h>
#include <wx/axis/juliandateaxis.h>
#include <wx/xy/juliantimeseriesdataset.h>
#include <wx/xy/timeseriesdataset.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xyplot.h>

/**
 *
 */
class TimeSeriesDemo1 : public ChartDemo
{
public:
    TimeSeriesDemo1()
    : ChartDemo(wxT("Time Series Demo 1 - Simple Time Series"))
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
        plot->SetBackground(new GradientAreaDraw(*wxTRANSPARENT_PEN, wxColour(100, 100, 250), wxColour(200, 220, 250)));
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // And finally create the chart.
        Chart *chart = new Chart(plot, GetName());
        chart->SetBackground(new GradientAreaDraw(*wxTRANSPARENT_PEN, wxColour(200, 220, 250), *wxWHITE, wxSOUTH));
        
        //chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

/**
 * The following demo shows how to use a Julian time series axis on a normal XY plot.
 */
class TimeSeriesDemo2 : public ChartDemo
{
public:
    TimeSeriesDemo2()
    : ChartDemo(wxT("Time Series Demo 2 - Julian Date Axis"))
    {
    }

    virtual Chart *Create()
    {
        wxVector<TimePair> times;

        // Find the Julian Date Number (JDN) for 100 years ago.
        wxDateTime dt = wxDateTime::Now().GetDateOnly() - wxDateSpan(100, 0, 0, 0);
        
        // Find the number of days elapsed between dt and now and generate random data for that period.
        size_t days = wxDateTime::Now().GetDateOnly().GetJDN() - dt.GetJDN();

        for (size_t i = 0; i < days; i++)
        {
            double val = (rand() % 10000) / 100.0;
            times.push_back(TimePair(dt.GetJDN(), val));
            dt.Add(wxDateSpan(0, 0, 0, 1));
        }

        // first step: create plot
        XYPlot *plot = new XYPlot();

        JulianTimeSeriesDataset *dataset = new JulianTimeSeriesDataset(times);

        dataset->SetRenderer(new XYLineRenderer());

        plot->AddDataset(dataset);

        // Add left number and bottom date axes.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        JulianDateAxis *bottomAxis = new JulianDateAxis(AXIS_BOTTOM);

        // Display the data 4 weeks at a time.
        bottomAxis->SetWindow(times.front().first, 28);
        bottomAxis->SetUseWindow(true);
        bottomAxis->SetVerticalLabelText(true);
        bottomAxis->SetDateFormat("%Y/%m/%d");

        // Set the bounds to match exactly the date range for which we have data.
        // TODO: THis should probably be the default on all time axis.
        bottomAxis->SetFixedBounds(times.front().first, times.back().first);

        // Add axes to the plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // Link axes and the dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Create the chart and set the bottom axis (windowed) to be scrolled.
        Chart *chart = new Chart(plot, GetName());
        chart->SetScrolledAxis(bottomAxis);

        return chart;
    }
};

ChartDemo *timeSeriesDemos[] = 
{
    new TimeSeriesDemo1(),
    new TimeSeriesDemo2()
};

int timeSeriesDemosCount = WXSIZEOF(timeSeriesDemos);
