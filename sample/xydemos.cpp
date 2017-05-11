/////////////////////////////////////////////////////////////////////////////
// Name:    xydemos.cpp
// Purpose: xy demos
// Author:    Moskvichev Andrey V.
// Created:    2008/11/12
// Copyright:    (c) 2008-2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/axis/logarithmicnumberaxis.h>

#include <wx/xy/xyhistorenderer.h>

#include <wx/xy/xyarearenderer.h>

#include <cmath>


class XYDemo1 : public ChartDemo
{
public:
    XYDemo1()
    : ChartDemo(wxT("XY Demo 1 - Simple Line Graph"))
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

        BiDataSet* dataset = new BiDataSet("XY Demo 1");

        // Add the series to the data set.
        dataset->AddSeries(series);

        // Set a XY line renderer for the dataset.
        dataset->SetRenderer(new XYLineRenderer());
        
        // Create an XY plot.
        XYPlot *plot = new XYPlot();

        // create left and bottom number axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetFixedBounds(-10, 200);
        
        // optional: set axis titles
        leftAxis->SetTitle(wxT("X Values"));
        bottomAxis->SetTitle(wxT("Y Values"));

        // add axes and dataset to plot
        plot->AddObjects(dataset, leftAxis, bottomAxis);

        // and finally create chart
        return new Chart(plot, GetName());
    }
};

/**
 * The same as XYDemo1, but with two series.
 */
class XYDemo2 : public ChartDemo
{
public:
    XYDemo2()
    : ChartDemo(wxT("XY Demo 2 - Multiple Series with legend"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(10.0, 20.0));
        series1->AddPoint(new BiDataPoint(13.0, 16.0));
        series1->AddPoint(new BiDataPoint(7.0, 30.0));
        series1->AddPoint(new BiDataPoint(15.0, 34.0));
        series1->AddPoint(new BiDataPoint(25.0, 4.0));

        // XY data for first series.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new BiDataPoint(45.0, 40.0));
        series2->AddPoint(new BiDataPoint(23.0, 16.0));
        series2->AddPoint(new BiDataPoint(43.0, 60.0));
        series2->AddPoint(new BiDataPoint(25.0, 7.0));
        series2->AddPoint(new BiDataPoint(66.0, 4.0));

        BiDataSet* dataset = new BiDataSet("XY Demo 2");
        
        // Add the series to the data set.
        dataset->AddSeries(series1);  
        dataset->AddSeries(series2);  
        
        // Set line renderer for the dataset.
        dataset->SetRenderer(new XYLineRenderer());

        // Create the plot.
        XYPlot *plot = new XYPlot();

        // Add our dataset to plot.
        plot->AddDataset(dataset);

        // Create left and bottom number axes.
        plot->AddAxis(new NumberAxis(AXIS_LEFT));
        plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

        // Link the axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Create the legend and add it to the plot.
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // ... and finally create chart.
        return new Chart(plot, GetName());
    }
};

/**
 * The same as XYDemo2, but draws symbols instead of lines.
 * With legend.
 */
class XYDemo3 : public ChartDemo
{
public:
    XYDemo3()
    : ChartDemo(wxT("XY Demo 3 - Symbols"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(10.0, 20.0));
        series1->AddPoint(new BiDataPoint(13.0, 16.0));
        series1->AddPoint(new BiDataPoint(7.0, 30.0));
        series1->AddPoint(new BiDataPoint(15.0, 34.0));
        series1->AddPoint(new BiDataPoint(25.0, 4.0));

        // XY data for first series.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new BiDataPoint(45.0, 40.0));
        series2->AddPoint(new BiDataPoint(23.0, 16.0));
        series2->AddPoint(new BiDataPoint(43.0, 60.0));
        series2->AddPoint(new BiDataPoint(25.0, 7.0));
        series2->AddPoint(new BiDataPoint(66.0, 4.0));

        BiDataSet* dataset = new BiDataSet("XY Demo 3");
        
        // Add the series to the data set.
        dataset->AddSeries(series1);  
        dataset->AddSeries(series2);  
        
        // Set line renderer with symbols enabled and lines disabled.
        dataset->SetRenderer(new XYLineRenderer(true, false));

        // Create the plot.
        XYPlot *plot = new XYPlot();
        
        // Add our dataset to the plot.
        plot->AddDataset(dataset);

        // Create left and bottom number axes.
        plot->AddAxis(new NumberAxis(AXIS_LEFT));
        plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

        // Link the axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Add the legend to the plot.
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // ... and finally create chart.
        return new Chart(plot, GetName());
    }
};

class XYDemo4 : public ChartDemo
{
public:
    XYDemo4()
    : ChartDemo(wxT("XY Demo 4 - Windowed"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for the series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(10.0, 20.0));
        series1->AddPoint(new BiDataPoint(13.0, 16.0));
        series1->AddPoint(new BiDataPoint(7.0, 30.0));
        series1->AddPoint(new BiDataPoint(15.0, 34.0));
        series1->AddPoint(new BiDataPoint(25.0, 4.0));

        BiDataSet* dataset = new BiDataSet("XY Demo 4");
        
        // Add the series to the data set.
        dataset->AddSeries(series1);  
        
        // Set line renderer with symbols enabled and lines disabled.
        dataset->SetRenderer(new XYLineRenderer());

        // Create the plot.
        XYPlot *plot = new XYPlot();

        // Add the dataset to plot.
        plot->AddDataset(dataset);

        // create left and bottom number axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

        // look at this code, we setup window, so
        // only part of data will be shown, not entire dataset as
        // in XYDemo1.
        bottomAxis->SetWindowPosition(10);
        bottomAxis->SetWindowWidth(10);
        bottomAxis->SetUseWindow(true);

        // add axes to plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());

        // set axis as scrolled, so chart panel can scroll its window.
        chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
};

/**
 * Class, that updates dataset on timer.
 */
#define DYNAMIC_DATA_POINTS 200
#define DYNAMIC_UPDATE_25FPS 40
#define DYNAMIC_UPDATE_30FPS 30
 
class DynamicUpdater : public wxEvtHandler
{
public:
    DynamicUpdater(BiDataSet* dataset, NumberAxis* axis) :
    m_dataset(dataset),
    m_axis(axis)
    {
        // Create a timer and bind to OnTimer event handler.
        m_timer.SetOwner(this);
        Bind(wxEVT_TIMER, &DynamicUpdater::OnTimer, this);
        
        // Start timer with target 25fps update rate.
        m_timer.Start(DYNAMIC_UPDATE_25FPS);        
    }
    
    ~DynamicUpdater()
    {
        Unbind(wxEVT_TIMER, &DynamicUpdater::OnTimer, this);
        m_timer.Stop();
    }

private:
    BiDataSet* m_dataset;
    NumberAxis* m_axis;
    wxTimer m_timer;
    
    void OnTimer(wxTimerEvent &ev)
    {
        double first_x = m_dataset->GetFirst(0, 0);
        
        // Ripple the values down the vector.
        for (size_t i = 0; i < DYNAMIC_DATA_POINTS - 1; i++)
        {
            static_cast<BiDataPoint*>(m_dataset->GetSeries(0)->GetPoint(i).get())->
                                        SetValues(m_dataset->GetFirst(0, i + 1), m_dataset->GetSecond(0, i + 1));
        }

        // Generate a new random value for the end point.
        static_cast<BiDataPoint*>(m_dataset->GetSeries(0)->GetPoint(DYNAMIC_DATA_POINTS - 1).get())->
                                    SetValues(first_x + DYNAMIC_DATA_POINTS + 1, 100.0 * rand() / (double) RAND_MAX);
                                            
        // Shift the axis left also.
        m_axis->SetFixedBounds(first_x + 1, first_x + DYNAMIC_DATA_POINTS);
        
        // Notify the chart of new data.
        m_dataset->DatasetChanged();
    }
};

/**
 * Dynamic chart demo.
 */
class XYDemo5 : public ChartDemo
{
public:
    XYDemo5()
    : ChartDemo(wxT("XY Demo 5 - Dynamic Data"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for the series.
        DataSeries* series1 = new DataSeries("Series 1");
        
        for (size_t i = 0; i < DYNAMIC_DATA_POINTS; i++)
            series1->AddPoint(new BiDataPoint(i, 50.0));

        // Create the dataset.
        BiDataSet* dataset = new BiDataSet("Dynamic Data Set");

        // Add the series to it.
        dataset->AddSeries(series1);

        // Set the line renderer.
        dataset->SetRenderer(new XYLineRenderer());

        // Create plot.
        XYPlot *plot = new XYPlot();

        // Add the dataset to the plot.
        plot->AddDataset(dataset);

        // create left and bottom number axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        leftAxis->SetFixedBounds(0.0, 100.0);

        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetFixedBounds(0.0, DYNAMIC_DATA_POINTS - 1);
        
        m_pUpdater = new DynamicUpdater(dataset, bottomAxis);

        // Add axes to the plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // Link axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // And finally create the chart.
        return new Chart(plot, GetName());
    }
    
    virtual void CleanUp() wxOVERRIDE
    {
        delete m_pUpdater;
    }

private:
    DynamicUpdater* m_pUpdater;
};

/**
 * Sine function chart demo
 */
class XYDemo6 : public ChartDemo
{
public:
    XYDemo6()
    : ChartDemo(wxT("XY Demo 6 - Sine Wave"))
    {
    }

    virtual Chart *Create()
    {
        // Create a data series to hold the sine data.
        DataSeries* series = new DataSeries("Sine Series");
        
        // Populate the series with the data.
        for (double angle = 0.0; angle <= 360.0; angle++)
            series->AddPoint(new BiDataPoint(angle, std::sin(angle * M_PI / 180.0)));
        
        // Create a data set and add the series to it.
        BiDataSet* dataset = new BiDataSet("Sine Wave Example");
        dataset->AddSeries(series);

        // Create a line renderer and set it for this dataset.
        dataset->SetRenderer(new XYLineRenderer());

        // Create an X-Y scatter plot and add the data set to it.
        XYPlot *plot = new XYPlot();
        plot->AddDataset(dataset);

        // Add left and bottom number axes.
        plot->AddAxis(new NumberAxis(AXIS_LEFT));
        
        NumberAxis* bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetMinorIntervalCount(2);
        plot->AddAxis(bottomAxis);

        // Link axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        return new Chart(plot, GetName());
    }
};

/**
 * Multiseries line xy chart demo.
 * Also it shows how to use legend.
 */
class XYDemo7 : public ChartDemo
{
public:
    XYDemo7()
    : ChartDemo(wxT("XY Demo 7 - Multiple Series with Symbols"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(1, 1));
        series1->AddPoint(new BiDataPoint(2, 4));
        series1->AddPoint(new BiDataPoint(3, 3));
        series1->AddPoint(new BiDataPoint(4, 5));
        series1->AddPoint(new BiDataPoint(5, 5));
        series1->AddPoint(new BiDataPoint(6, 7));
        series1->AddPoint(new BiDataPoint(7, 7));
        series1->AddPoint(new BiDataPoint(8, 8));

        // XY data for second series.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new BiDataPoint(3, 4));
        series2->AddPoint(new BiDataPoint(4, 3));
        series2->AddPoint(new BiDataPoint(5, 2));
        series2->AddPoint(new BiDataPoint(6, 3));
        series2->AddPoint(new BiDataPoint(7, 6));
        series2->AddPoint(new BiDataPoint(8, 3));
        series2->AddPoint(new BiDataPoint(9, 4));
        series2->AddPoint(new BiDataPoint(10, 3));
        
        // XY data for third series.
        DataSeries* series3 = new DataSeries("Series 3");
        series3->AddPoint(new BiDataPoint(1, 5));
        series3->AddPoint(new BiDataPoint(2, 7));
        series3->AddPoint(new BiDataPoint(3, 6));
        series3->AddPoint(new BiDataPoint(4, 8));
        series3->AddPoint(new BiDataPoint(5, 4));
        series3->AddPoint(new BiDataPoint(6, 4));
        series3->AddPoint(new BiDataPoint(7, 2));
        series3->AddPoint(new BiDataPoint(8, 1));

        BiDataSet* dataset = new BiDataSet("XY Demo 10");
        
        // Add the series to the data set.
        dataset->AddSeries(series1);  
        dataset->AddSeries(series2);  
        dataset->AddSeries(series3);  
        
        // Create the plot.
        XYPlot *plot = new XYPlot();
        
        // Set line renderer with symbols enabled and lines disabled.
        XYLineRenderer* renderer = new XYLineRenderer(true, true);
        // we can change line pen for serie, for example set short-dash
        // line style and width=2 for third serie
        renderer->SetSeriePen(1, new wxPen(*wxGREEN, 2, wxPENSTYLE_SOLID));
        dataset->SetRenderer(renderer);

        // add dataset to plot
        plot->AddDataset(dataset);

        // create left and bottom number axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

        // add axes to plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // set legend
        plot->SetLegend(new Legend(wxBOTTOM, wxCENTER));

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());

        // set axis as scrolled, so chart panel can scroll its window.
        return chart;
    }
};

class XYDemo8 : public ChartDemo
{
public:
    XYDemo8()
    : ChartDemo(wxT("XY Demo 8 - Areas"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(1, 1));
        series1->AddPoint(new BiDataPoint(2, 4));
        series1->AddPoint(new BiDataPoint(3, 3));
        series1->AddPoint(new BiDataPoint(4, 5));
        series1->AddPoint(new BiDataPoint(5, 5));
        series1->AddPoint(new BiDataPoint(6, 7));
        series1->AddPoint(new BiDataPoint(7, 7));
        series1->AddPoint(new BiDataPoint(8, 8));

        // XY data for second series.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new BiDataPoint(3, 4));
        series2->AddPoint(new BiDataPoint(4, 3));
        series2->AddPoint(new BiDataPoint(5, 2));
        series2->AddPoint(new BiDataPoint(6, 3));
        series2->AddPoint(new BiDataPoint(7, 6));
        series2->AddPoint(new BiDataPoint(8, 3));
        series2->AddPoint(new BiDataPoint(9, 4));
        series2->AddPoint(new BiDataPoint(10, 3));

        BiDataSet* dataset = new BiDataSet("XY Demo 11");
        
        // Add the series to the data set.
        dataset->AddSeries(series1);  
        dataset->AddSeries(series2);  
        
        // Create the plot.
        XYPlot *plot = new XYPlot();

        // Create area renderer and set it to dataset.
        dataset->SetRenderer(new XYAreaRenderer());

        // Add our dataset to plot.
        plot->AddDataset(dataset);

        // Create left and bottom number axes.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

        // Add axes to plot.
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // Link axes and dataset.
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // Set legend.
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());
        return chart;
    }
};

class XYDemo9 : public ChartDemo
{
public:
    XYDemo9()
    : ChartDemo(wxT("XY Demo 9 - Logarithmic Y Axis"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(1, 1e3));
        series1->AddPoint(new BiDataPoint(2, 1.0));
        series1->AddPoint(new BiDataPoint(3, 1e2));
        series1->AddPoint(new BiDataPoint(4, 2e7));
        series1->AddPoint(new BiDataPoint(5, 1e3));
        
        BiDataSet* dataset = new BiDataSet("XY Demo 9");
        
        // Add the series to the data set.
        dataset->AddSeries(series1);  
        
        // Set a line renderer to the dataset.
        dataset->SetRenderer(new XYLineRenderer(true));

        // Create the plot.
        XYPlot *plot = new XYPlot();

        // Add our dataset to plot.
        plot->AddDataset(dataset);
        
        // create left and bottom number axes
        LogarithmicNumberAxis *leftAxis = new LogarithmicNumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->ZeroOrigin(false);

        // optional: set axis titles
        leftAxis->SetTitle(wxT("X Values"));
        bottomAxis->SetTitle(wxT("Y Values"));

        // add axes to plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        return new Chart(plot, GetName());
    }
};

class XYDemo10 : public ChartDemo
{
public:
    XYDemo10()
    : ChartDemo(wxT("XY Demo 10 - Logarithmic X and Y Axis"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for the series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(2, 2));
        series1->AddPoint(new BiDataPoint(4, 4));
        series1->AddPoint(new BiDataPoint(8, 8));
        series1->AddPoint(new BiDataPoint(16, 16));
        series1->AddPoint(new BiDataPoint(32, 32));
        
        BiDataSet* dataset = new BiDataSet("XY Demo 10");
        
        // Add the series to the data set.
        dataset->AddSeries(series1);  
        
        // Set a line renderer to the dataset.
        dataset->SetRenderer(new XYLineRenderer(true));

        // Create the plot.
        XYPlot *plot = new XYPlot();

        // Add our dataset to plot.
        plot->AddDataset(dataset);        
        
        // create left and bottom number axes
        LogarithmicNumberAxis *leftAxis = new LogarithmicNumberAxis(AXIS_LEFT);
        leftAxis->SetLogBase(2.0);
        leftAxis->SetMinorIntervalCount(8);
        LogarithmicNumberAxis *bottomAxis = new LogarithmicNumberAxis(AXIS_BOTTOM);
        bottomAxis->SetLogBase(2.0);
        bottomAxis->SetMinorIntervalCount(8);

        // optional: set axis titles
        leftAxis->SetTitle(wxT("X"));
        bottomAxis->SetTitle(wxT("Y"));

        // add axes to plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        return new Chart(plot, GetName());
    }
};

ChartDemo *xyDemos[] = 
{
    new XYDemo1(),
    new XYDemo2(),
    new XYDemo3(),
    new XYDemo4(),
    new XYDemo5(),
    new XYDemo6(),
    new XYDemo7(),
    new XYDemo8(),
    new XYDemo9(),
    new XYDemo10()
};
int xyDemosCount = WXSIZEOF(xyDemos);
