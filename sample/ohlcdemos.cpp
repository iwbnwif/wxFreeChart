/////////////////////////////////////////////////////////////////////////////
// Name:    ohlcdemos.cpp
// Purpose: ohlc demos code
// Author:    Moskvichev Andrey V.
// Created:    30.11.2008
// Copyright:    (c) 2008-2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"


#include <wx/axis/dateaxis.h>
#include <wx/axis/numberaxis.h>

#include <wx/plot/ohlcplot.h>

#include <wx/render/movingaverage.h>
#include <wx/render/ohlcbarrenderer.h>
#include <wx/render/ohlccandlestickrenderer.h>
#include <wx/render/xylinerenderer.h>

/**
 * Simple OHLC demo with bar renderer.
 */
class OHLCDemo1 : public ChartDemo
{
public:
    OHLCDemo1()
    : ChartDemo(wxT("OHLC Demo 1 - Bars"))
    {
    }

    virtual Chart *Create()
    {
        // Generate some quote data.
        wxVector<OHLCItem> quotes;
        quotes.push_back(OHLCItem(64.09,64.34,63.17,63.42));
        quotes.push_back(OHLCItem(63.34,63.52,61.08,61.50));
        quotes.push_back(OHLCItem(61.41,62.40,60.97,62.09));
        quotes.push_back(OHLCItem(61.71,63.39,61.41,63.36));
        quotes.push_back(OHLCItem(63.39,63.89,62.75,63.54));
        quotes.push_back(OHLCItem(63.64,63.79,62.79,63.66));
        quotes.push_back(OHLCItem(63.61,65.26,63.49,65.11));
        quotes.push_back(OHLCItem(65.11,65.86,64.68,65.73));
        quotes.push_back(OHLCItem(65.72,66.76,65.26,66.75));
        quotes.push_back(OHLCItem(66.89,66.91,65.51,65.88));
        quotes.push_back(OHLCItem(66.68,67.92,66.58,66.75));
        quotes.push_back(OHLCItem(66.51,66.86,65.72,66.38));
        quotes.push_back(OHLCItem(66.40,67.37,65.83,67.15));
        quotes.push_back(OHLCItem(67.27,68.23,67.27,67.78));
        quotes.push_back(OHLCItem(67.66,67.68,66.61,67.24));

        // Create a series.
        DataSeries* series = new DataSeries("Series 1");
        
        // Set the start date and populate the series.
        wxDateTime dt = wxDateTime::Today() - wxDateSpan(0, 0, 0, 15);
        wxDateTime startDate = dt;

        for (size_t i = 0; i < quotes.size(); i++, dt += wxDateSpan(0, 0, 0, 1))
            series->AddPoint(new BiDataPoint(dt, quotes[i]));

        // Create the dataset.
        BiDataSet* dataset = new BiDataSet("OHLC Demo 1");
        
        // Add the series to the dataset.
        dataset->AddSeries(series);

        // create and set OHLC bars renderer to our dataset
        dataset->SetRenderer(new OHLCBarRenderer());

        // Create the plot.
        OHLCPlot* plot = new OHLCPlot();

        // add our dataset to plot
        plot->AddDataset(dataset);

        // create left number (for quotes) and bottom date axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);
        
        // Don't start the left axis at zero.
        leftAxis->ZeroOrigin(false);

        // Setup window, to show 5 days at once (not entire dataset).
        bottomAxis->SetWindow(startDate.GetTicks(), 5 * 24 * 60 * 60);
        bottomAxis->SetUseWindow(true);

        // Configure bottom axis formatting.
        bottomAxis->SetVerticalLabelText(true);
        bottomAxis->SetDateFormat(wxT("%d-%m-%y"));

        // Add axes to plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // Link axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Create the chart. 
        Chart *chart = new Chart(plot, GetName());

        // Set scrolling axis to chart.
        chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

/**
 * Simple OHLC demo with candlestick renderer.
 */
class OHLCDemo2 : public ChartDemo
{
public:
    OHLCDemo2()
    : ChartDemo(wxT("OHLC Demo 2 - Candlesticks"))
    {
    }

    virtual Chart *Create()
    {
        // Generate some quote data.
        wxVector<OHLCItem> quotes;
        quotes.push_back(OHLCItem(64.09,64.34,63.17,63.42));
        quotes.push_back(OHLCItem(63.34,63.52,61.08,61.50));
        quotes.push_back(OHLCItem(61.41,62.40,60.97,62.09));
        quotes.push_back(OHLCItem(61.71,63.39,61.41,63.36));
        quotes.push_back(OHLCItem(63.39,63.89,62.75,63.54));
        quotes.push_back(OHLCItem(63.64,63.79,62.79,63.66));
        quotes.push_back(OHLCItem(63.61,65.26,63.49,65.11));
        quotes.push_back(OHLCItem(65.11,65.86,64.68,65.73));
        quotes.push_back(OHLCItem(65.72,66.76,65.26,66.75));
        quotes.push_back(OHLCItem(66.89,66.91,65.51,65.88));
        quotes.push_back(OHLCItem(66.68,67.92,66.58,66.75));
        quotes.push_back(OHLCItem(66.51,66.86,65.72,66.38));
        quotes.push_back(OHLCItem(66.40,67.37,65.83,67.15));
        quotes.push_back(OHLCItem(67.27,68.23,67.27,67.78));
        quotes.push_back(OHLCItem(67.66,67.68,66.61,67.24));

        // Create a series.
        DataSeries* series = new DataSeries("Series 1");
        
        // Set the start date and populate the series.
        wxDateTime dt = wxDateTime::Today() - wxDateSpan(0, 0, 0, 15);

        for (size_t i = 0; i < quotes.size(); i++, dt += wxDateSpan(0, 0, 0, 1))
            series->AddPoint(new BiDataPoint(dt, quotes[i]));

        // Create the dataset.
        BiDataSet* dataset = new BiDataSet("OHLC Demo 2");
        
        // Add the series to the dataset.
        dataset->AddSeries(series);

        // Create an OHLC bars renderer for the dataset.
        dataset->SetRenderer(new OHLCCandlestickRenderer());

        // Create the plot.
        OHLCPlot* plot = new OHLCPlot();

        // Add the dataset to plot.
        plot->AddDataset(dataset);

        // Create the left number (quote) axis and a horizontal date axis.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);
        
        // Don't start the left axis at zero.
        leftAxis->ZeroOrigin(false);

        // Setup window, to show 5 days with starting point at the third data point.
        bottomAxis->SetWindowPosition(dataset->GetPointData(0, 2, 0).As<wxDateTime>().GetTicks()); 
        bottomAxis->SetWindowWidth(5 * 24 * 60 * 60);
        bottomAxis->SetUseWindow(true);

        // Configure bottom axis formatting.
        bottomAxis->SetVerticalLabelText(true);
        bottomAxis->SetDateFormat(wxT("%d-%m-%y"));

        // Add axes to plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // Link axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Create the chart. 
        Chart *chart = new Chart(plot, GetName());

        // Set scrolling axis to chart.
        chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

/**
 * Simple OHLC demo with candlestick renderer, and composite date axis.
 */
class OHLCDemo3 : public ChartDemo
{
public:
    OHLCDemo3()
    : ChartDemo(wxT("OHLC Demo 3 - Composite Date Axis"))
    {
    }

    virtual Chart *Create()
    {
        // Generate some quote data.
        wxVector<OHLCItem> quotes;
        quotes.push_back(OHLCItem(64.09,64.34,63.17,63.42));
        quotes.push_back(OHLCItem(63.34,63.52,61.08,61.50));
        quotes.push_back(OHLCItem(61.41,62.40,60.97,62.09));
        quotes.push_back(OHLCItem(61.71,63.39,61.41,63.36));
        quotes.push_back(OHLCItem(63.39,63.89,62.75,63.54));
        quotes.push_back(OHLCItem(63.64,63.79,62.79,63.66));
        quotes.push_back(OHLCItem(63.61,65.26,63.49,65.11));
        quotes.push_back(OHLCItem(65.11,65.86,64.68,65.73));
        quotes.push_back(OHLCItem(65.72,66.76,65.26,66.75));
        quotes.push_back(OHLCItem(66.89,66.91,65.51,65.88));
        quotes.push_back(OHLCItem(66.68,67.92,66.58,66.75));
        quotes.push_back(OHLCItem(66.51,66.86,65.72,66.38));
        quotes.push_back(OHLCItem(66.40,67.37,65.83,67.15));
        quotes.push_back(OHLCItem(67.27,68.23,67.27,67.78));
        quotes.push_back(OHLCItem(67.66,67.68,66.61,67.24));

        // Create a series.
        DataSeries* series = new DataSeries("Series 1");
        
        // Set the start date and populate the series.
        wxDateTime dt = wxDateTime::Today() - wxDateSpan(0, 0, 0, 15);

        for (size_t i = 0; i < quotes.size(); i++, dt += wxDateSpan(0, 0, 0, 1))
            series->AddPoint(new BiDataPoint(dt, quotes[i]));

        // Create the dataset.
        BiDataSet* dataset = new BiDataSet("OHLC Demo 3");
        
        // Add the series to the dataset.
        dataset->AddSeries(series);

        // Create an OHLC bars renderer for the dataset.
        dataset->SetRenderer(new OHLCCandlestickRenderer());

        // Create the plot.
        OHLCPlot* plot = new OHLCPlot();

        // Add the dataset to plot.
        plot->AddDataset(dataset);

        // Create the left number (quote) axis and a horizontal composite date axis.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        // CompDateAxis *bottomAxis = new CompDateAxis(AXIS_BOTTOM);
        
        // Don't start the left axis at zero.
        leftAxis->ZeroOrigin(false);

        // Setup window, to show 5 days with starting point at the third data point.
        /*
        bottomAxis->SetWindowPosition(dataset->GetPointData(0, 2, 0).As<wxDateTime>().GetTicks()); 
        bottomAxis->SetWindowWidth(5 * 24 * 60 * 60);
        bottomAxis->SetUseWindow(true);

        // Set date spans.
        bottomAxis->AddInterval(wxDateSpan::Day());
        bottomAxis->AddInterval(wxDateSpan::Week());
        bottomAxis->AddInterval(wxDateSpan::Month());
        bottomAxis->AddInterval(wxDateSpan::Year());

        // Add axes to plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);
        */
        // Link axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Create the chart. 
        Chart *chart = new Chart(plot, GetName());

        // Set scrolling axis to chart.
        // chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

/**
 * OHLC demo with candlestick renderer and moving average indicator.
 */
class OHLCDemo4 : public ChartDemo
{
public:
    OHLCDemo4()
    : ChartDemo(wxT("OHLC Demo 4 - Candlesticks with Moving Average"))
    {
    }

    virtual Chart *Create()
    {
        // Generate some quote data.
        wxVector<OHLCItem> quotes;
        quotes.push_back(OHLCItem(64.09,64.34,63.17,63.42));
        quotes.push_back(OHLCItem(63.34,63.52,61.08,61.50));
        quotes.push_back(OHLCItem(61.41,62.40,60.97,62.09));
        quotes.push_back(OHLCItem(61.71,63.39,61.41,63.36));
        quotes.push_back(OHLCItem(63.39,63.89,62.75,63.54));
        quotes.push_back(OHLCItem(63.64,63.79,62.79,63.66));
        quotes.push_back(OHLCItem(63.61,65.26,63.49,65.11));
        quotes.push_back(OHLCItem(65.11,65.86,64.68,65.73));
        quotes.push_back(OHLCItem(65.72,66.76,65.26,66.75));
        quotes.push_back(OHLCItem(66.89,66.91,65.51,65.88));
        quotes.push_back(OHLCItem(66.68,67.92,66.58,66.75));
        quotes.push_back(OHLCItem(66.51,66.86,65.72,66.38));
        quotes.push_back(OHLCItem(66.40,67.37,65.83,67.15));
        quotes.push_back(OHLCItem(67.27,68.23,67.27,67.78));
        quotes.push_back(OHLCItem(67.66,67.68,66.61,67.24));

        // Create a series.
        DataSeries* series = new DataSeries("Series 1");
        
        // Set the start date and populate the series.
        wxDateTime dt = wxDateTime::Today() - wxDateSpan(0, 0, 0, 15);

        for (size_t i = 0; i < quotes.size(); i++, dt += wxDateSpan(0, 0, 0, 1))
            series->AddPoint(new BiDataPoint(dt, quotes[i]));

        // Create the dataset.
        BiDataSet* dataset = new BiDataSet("OHLC Demo 2");
        
        // Add the series to the dataset.
        dataset->AddSeries(series);

        // Create an OHLC bars renderer for the dataset.
        dataset->SetRenderer(new OHLCCandlestickRenderer());

        // Create the plot.
        OHLCPlot* plot = new OHLCPlot();

        // Add the dataset to plot.
        plot->AddDataset(dataset);

        // add moving average dataset with period = 5
        // MovingAverage* maDataset = new MovingAverage(dataset, 5);
        // maDataset->SetRenderer(new XYLineRenderer());

        // plot->AddDataset(maDataset);


        // Create the left number (quote) axis and a horizontal date axis.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);
        
        // Don't start the left axis at zero.
        leftAxis->ZeroOrigin(false);

        // Setup window, to show 5 days with starting point at the third data point.
        bottomAxis->SetWindowPosition(dataset->GetPointData(0, 2, 0).As<wxDateTime>().GetTicks()); 
        bottomAxis->SetWindowWidth(5 * 24 * 60 * 60);
        bottomAxis->SetUseWindow(true);

        // Configure bottom axis formatting.
        bottomAxis->SetVerticalLabelText(true);
        bottomAxis->SetDateFormat(wxT("%d-%m-%y"));

        // Add axes to plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // Link axes and main dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Link axes with moving average dataset.
        // plot->LinkDataVerticalAxis(1, 0);
        // plot->LinkDataHorizontalAxis(1, 0);

        // Create the chart. 
        Chart *chart = new Chart(plot, GetName());

        // Set scrolling axis to chart.
        chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

class OHLCDemo5 : public ChartDemo
{
public:
    OHLCDemo5()
    : ChartDemo(wxT("OHLC Demo 5 - Colour Bars"))
    {
    }

    virtual Chart *Create()
    {
         // Generate some quote data.
        wxVector<OHLCItem> quotes;
        quotes.push_back(OHLCItem(64.09,64.34,63.17,63.42));
        quotes.push_back(OHLCItem(63.34,63.52,61.08,61.50));
        quotes.push_back(OHLCItem(61.41,62.40,60.97,62.09));
        quotes.push_back(OHLCItem(61.71,63.39,61.41,63.36));
        quotes.push_back(OHLCItem(63.39,63.89,62.75,63.54));
        quotes.push_back(OHLCItem(63.64,63.79,62.79,63.66));
        quotes.push_back(OHLCItem(63.61,65.26,63.49,65.11));
        quotes.push_back(OHLCItem(65.11,65.86,64.68,65.73));
        quotes.push_back(OHLCItem(65.72,66.76,65.26,66.75));
        quotes.push_back(OHLCItem(66.89,66.91,65.51,65.88));
        quotes.push_back(OHLCItem(66.68,67.92,66.58,66.75));
        quotes.push_back(OHLCItem(66.51,66.86,65.72,66.38));
        quotes.push_back(OHLCItem(66.40,67.37,65.83,67.15));
        quotes.push_back(OHLCItem(67.27,68.23,67.27,67.78));
        quotes.push_back(OHLCItem(67.66,67.68,66.61,67.24));

        // Create a series.
        DataSeries* series = new DataSeries("Series 1");
        
        // Set the start date and populate the series.
        wxDateTime dt = wxDateTime::Today() - wxDateSpan(0, 0, 0, 15);

        for (size_t i = 0; i < quotes.size(); i++, dt += wxDateSpan(0, 0, 0, 1))
            series->AddPoint(new BiDataPoint(dt, quotes[i]));

        // Create the dataset.
        BiDataSet* dataset = new BiDataSet("OHLC Demo 5");
        
        // Add the series to the dataset.
        dataset->AddSeries(series);

        // Create an OHLC bars renderer for the dataset.
        OHLCCandlestickRenderer* renderer = new OHLCCandlestickRenderer();
        renderer->SetHigherBrush(*wxGREEN_BRUSH);
        renderer->SetLowerBrush(*wxRED_BRUSH);
        dataset->SetRenderer(renderer);

        // Create the plot.
        OHLCPlot* plot = new OHLCPlot();

        // Add the dataset to plot.
        plot->AddDataset(dataset);

        // Create the left number (quote) axis and a horizontal date axis.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        DateAxis *bottomAxis = new DateAxis(AXIS_BOTTOM);
        
        // Don't start the left axis at zero.
        leftAxis->ZeroOrigin(false);

        // Setup window, to show 5 days with starting point at the third data point.
        bottomAxis->SetWindowPosition(dataset->GetPointData(0, 2, 0).As<wxDateTime>().GetTicks()); 
        bottomAxis->SetWindowWidth(5 * 24 * 60 * 60);
        bottomAxis->SetUseWindow(true);

        // Configure bottom axis formatting.
        bottomAxis->SetVerticalLabelText(true);
        bottomAxis->SetDateFormat(wxT("%d-%m-%y"));

        // Add axes to plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // Link axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Create the chart. 
        Chart *chart = new Chart(plot, GetName());

        // Set scrolling axis to chart.
        chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

ChartDemo *ohlcDemos[] = {
    new OHLCDemo1(),
    new OHLCDemo2(),
    // new OHLCDemo3() // TODO: Make CompDateAxis work with new datasets.
    new OHLCDemo4(), // TODO: Make MovingAverage work with new datasets.
    new OHLCDemo5()
};
int ohlcDemosCount = WXSIZEOF(ohlcDemos);
