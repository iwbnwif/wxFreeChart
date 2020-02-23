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

// for histogram demo
#include <wx/xy/xyhistorenderer.h>

// for area demo
#include <wx/xy/xyarearenderer.h>

// for dynamic dataset
#include <wx/xy/vectordataset.h>

#include <wx/xy/functions/sinefunction.h>

#include <math.h>


class XYDemo1 : public ChartDemo
{
public:
    XYDemo1()
    : ChartDemo(wxT("XY Demo 1 - Simple Line Graph"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for series
        wxVector<wxRealPoint> data;
        data.push_back(wxRealPoint(10, 20));
        data.push_back(wxRealPoint(13, 16));
        data.push_back(wxRealPoint(7, 30));
        data.push_back(wxRealPoint(15, 34));
        data.push_back(wxRealPoint(25, 4));
        
        // First step: create plot.
        XYPlot *plot = new XYPlot();

        // Second step: create dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add a series to it.
        dataset->AddSerie(new XYSerie(data));
        
        // set line renderer to dataset
        dataset->SetRenderer(new XYLineRenderer());

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
    : ChartDemo(wxT("XY Demo 2 - Multiple Series (with legend)"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series
        wxVector<wxRealPoint> data1;
        data1.push_back(wxRealPoint(10, 20));
        data1.push_back(wxRealPoint(13, 16));
        data1.push_back(wxRealPoint(7, 30));
        data1.push_back(wxRealPoint(15, 34));
        data1.push_back(wxRealPoint(25, 4));

        // XY data for second series
        wxVector<wxRealPoint> data2;
        data2.push_back(wxRealPoint(45, 40));
        data2.push_back(wxRealPoint(23, 16));
        data2.push_back(wxRealPoint(43, 60));
        data2.push_back(wxRealPoint(25, 7));
        data2.push_back(wxRealPoint(66, 4));

        // First step: create the plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add the two series to it.
        dataset->AddSerie(new XYSerie(data1));
        dataset->AddSerie(new XYSerie(data2));

        // set line renderer to dataset
        dataset->SetRenderer(new XYLineRenderer());

        // add our dataset to plot
        plot->AddDataset(dataset);

        // create left and bottom number axes
        plot->AddAxis(new NumberAxis(AXIS_LEFT));
        plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // set serie names to be displayed on legend
        dataset->GetSerie(0)->SetName(wxT("Serie 0"));
        dataset->GetSerie(1)->SetName(wxT("Serie 1"));

        // set legend
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // and finally create chart
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
        // XY data for first series
        wxVector<wxRealPoint> data1;
        data1.push_back(wxRealPoint(10, 20));
        data1.push_back(wxRealPoint(13, 16));
        data1.push_back(wxRealPoint(7, 30));
        data1.push_back(wxRealPoint(15, 34));
        data1.push_back(wxRealPoint(25, 4));

        // XY data for second series
        wxVector<wxRealPoint> data2;
        data2.push_back(wxRealPoint(45, 40));
        data2.push_back(wxRealPoint(23, 16));
        data2.push_back(wxRealPoint(43, 60));
        data2.push_back(wxRealPoint(25, 7));
        data2.push_back(wxRealPoint(66, 4));

        // First step: create the plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add the two series to it.
        dataset->AddSerie(new XYSerie(data1));
        dataset->AddSerie(new XYSerie(data2));

        // set line renderer with symbols enabled and lines disabled
        dataset->SetRenderer(new XYLineRenderer(true, false));

        // add our dataset to plot
        plot->AddDataset(dataset);

        // create left and bottom number axes
        plot->AddAxis(new NumberAxis(AXIS_LEFT));
        plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // set serie names to be displayed on legend
        dataset->GetSerie(0)->SetName(wxT("First"));
        dataset->GetSerie(1)->SetName(wxT("Second"));

        // set legend to plot
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // and finally create chart
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
        // XY data for series
        wxVector<wxRealPoint> data;
        data.push_back(wxRealPoint(10, 20));
        data.push_back(wxRealPoint(13, 16));
        data.push_back(wxRealPoint(7, 30));
        data.push_back(wxRealPoint(15, 34));
        data.push_back(wxRealPoint(25, 4));

        // first step: create plot
        XYPlot *plot = new XYPlot();

        // create dataset
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // and add serie to it
        dataset->AddSerie(new XYSerie(data));

        // set line renderer to dataset
        dataset->SetRenderer(new XYLineRenderer());

        // add our dataset to plot
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
    DynamicUpdater(XYSimpleDataset* dataset, NumberAxis* axis) :
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
    XYSimpleDataset *m_dataset;
    NumberAxis* m_axis;
    wxTimer m_timer;
    
    void OnTimer(wxTimerEvent &WXUNUSED(ev))
    {
        double first_x = m_dataset->GetSerie(0)->GetX(0);
        
        // Ripple the values down the vector.
        for (size_t i = 0; i < DYNAMIC_DATA_POINTS - 1; i++)
            m_dataset->GetSerie(0)->UpdatePoint(i, wxRealPoint(first_x + i + 1, m_dataset->GetSerie(0)->GetY(i + 1)));

        // Generate a new random value for the end point.
        m_dataset->GetSerie(0)->UpdatePoint(DYNAMIC_DATA_POINTS - 1, 
                                            wxPoint(first_x + DYNAMIC_DATA_POINTS + 1, (100.0 * rand() / (double) RAND_MAX)));
                                            
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
        // XY data for series.
        wxVector<wxRealPoint> data;
        
        for (size_t i = 0; i < DYNAMIC_DATA_POINTS; i++)
            data.push_back(wxRealPoint(i, 50));

        // First step: create plot.
        XYPlot *plot = new XYPlot();

        // Second step: create dataset
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // and add serie to it
        dataset->AddSerie(new XYSerie(data));

        
        // set line renderer to it
        dataset->SetRenderer(new XYLineRenderer());

        // add our dataset to plot
        plot->AddDataset(dataset);

        // create left and bottom number axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        leftAxis->SetFixedBounds(0.0, 100.0);

        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetFixedBounds(0.0, DYNAMIC_DATA_POINTS - 1);
        
        m_pUpdater = new DynamicUpdater(dataset, bottomAxis);

        // leftAxis->SetLabelCount(101);
        // leftAxis->SetLabelSkip(9);
        // bottomAxis->SetFixedBounds(0.0, 300.0);
        // bottomAxis->SetLabelCount(101);
        // bottomAxis->SetLabelSkip(9);

        // we setup window
        //bottomAxis->SetWindow(0, 10);
        //bottomAxis->SetUseWindow(true);

        // add axes to plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());

        // set axis as scrolled, so chart panel can scroll its window.
        //chart->SetScrolledAxis(bottomAxis);
        return chart;
    }
    
    virtual void CleanUp() wxOVERRIDE
    {
        delete m_pUpdater;
    }

private:
    DynamicUpdater* m_pUpdater;

};

/**
 * Histogram XY chart demo
 */
class XYDemo6 : public ChartDemo
{
public:
    XYDemo6()
    : ChartDemo(wxT("XY Demo 6 - Single Histogram"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series
        wxVector<wxRealPoint> data;
        
        data.push_back(wxRealPoint(-2.75, 0.01));
        data.push_back(wxRealPoint(-2.5, 0.02));
        data.push_back(wxRealPoint(-2.25, 0.03));
        data.push_back(wxRealPoint(-2, 0.05));
        data.push_back(wxRealPoint(-1.75, 0.09));
        data.push_back(wxRealPoint(-1.5, 0.13));
        data.push_back(wxRealPoint(-1.25, 0.18));
        data.push_back(wxRealPoint(-1, 0.24));
        data.push_back(wxRealPoint(-0.75, 0.3));
        data.push_back(wxRealPoint(-0.5, 0.35));
        data.push_back(wxRealPoint(-0.25, 0.39));
        data.push_back(wxRealPoint(0, 0.4));
        data.push_back(wxRealPoint(0.25, 0.39));
        data.push_back(wxRealPoint(0.5, 0.35));
        data.push_back(wxRealPoint(0.75, 0.3));
        data.push_back(wxRealPoint(1, 0.24));
        data.push_back(wxRealPoint(1.25, 0.18));
        data.push_back(wxRealPoint(1.5, 0.13));
        data.push_back(wxRealPoint(1.75, 0.09));
        data.push_back(wxRealPoint(2, 0.05));
        data.push_back(wxRealPoint(2.25, 0.03));
        data.push_back(wxRealPoint(2.5, 0.02));
        data.push_back(wxRealPoint(2.75, 0.01));

        // First step: create the plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add the series to it.
        dataset->AddSerie(new XYSerie(data));

        // create histogram renderer with bar width = 10 and vertical bars
        XYHistoRenderer *histoRenderer = new XYHistoRenderer(10, true);

        // set bar areas to renderer
        // in this case, we set green bar with black outline for serie 0
        histoRenderer->SetBarArea(0, new FillAreaDraw(*wxBLACK_PEN, *wxGREEN_BRUSH));

        // set renderer to dataset
        dataset->SetRenderer(histoRenderer);

        // add our dataset to plot
        plot->AddDataset(dataset);

        // add left and bottom number axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

        // set bottom axis margins
        bottomAxis->SetMargins(15, 15);

        // add axes to plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());
        return chart;
    }
};

/**
 * Histogram XY chart demo
 */
class XYDemo7 : public ChartDemo
{
public:
    XYDemo7()
    : ChartDemo(wxT("XY Demo 7 - Two Histograms"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series
        wxVector<wxRealPoint> data1;
        
        data1.push_back(wxRealPoint(-2.75, 0.01));
        data1.push_back(wxRealPoint(-2.5, 0.02));
        data1.push_back(wxRealPoint(-2.25, 0.03));
        data1.push_back(wxRealPoint(-2, 0.05));
        data1.push_back(wxRealPoint(-1.75, 0.09));
        data1.push_back(wxRealPoint(-1.5, 0.13));
        data1.push_back(wxRealPoint(-1.25, 0.18));
        data1.push_back(wxRealPoint(-1, 0.24));
        data1.push_back(wxRealPoint(-0.75, 0.3));
        data1.push_back(wxRealPoint(-0.5, 0.35));
        data1.push_back(wxRealPoint(-0.25, 0.39));
        data1.push_back(wxRealPoint(0, 0.4));
        data1.push_back(wxRealPoint(0.25, 0.39));
        data1.push_back(wxRealPoint(0.5, 0.35));
        data1.push_back(wxRealPoint(0.75, 0.3));
        data1.push_back(wxRealPoint(1, 0.24));
        data1.push_back(wxRealPoint(1.25, 0.18));
        data1.push_back(wxRealPoint(1.5, 0.13));
        data1.push_back(wxRealPoint(1.75, 0.09));
        data1.push_back(wxRealPoint(2, 0.05));
        data1.push_back(wxRealPoint(2.25, 0.03));
        data1.push_back(wxRealPoint(2.5, 0.02));
        data1.push_back(wxRealPoint(2.75, 0.01));

        // XY data for second series
        wxVector<wxRealPoint> data2;
        
        data2.push_back(wxRealPoint(-3.75, 0.01));
        data2.push_back(wxRealPoint(-3.5, 0.02));
        data2.push_back(wxRealPoint(-3.25, 0.03));
        data2.push_back(wxRealPoint(-3, 0.05));
        data2.push_back(wxRealPoint(-2.75, 0.09));
        data2.push_back(wxRealPoint(-2.5, 0.13));
        data2.push_back(wxRealPoint(-2.25, 0.18));
        data2.push_back(wxRealPoint(-2, 0.24));
        data2.push_back(wxRealPoint(-1.75, 0.3));
        data2.push_back(wxRealPoint(-1.5, 0.35));
        data2.push_back(wxRealPoint(-1.25, 0.39));
        data2.push_back(wxRealPoint(-1, 0.4));
        data2.push_back(wxRealPoint(-0.75, 0.39));
        data2.push_back(wxRealPoint(-0.5, 0.35));
        data2.push_back(wxRealPoint(-0.25, 0.3));
        data2.push_back(wxRealPoint(0, 0.24));
        data2.push_back(wxRealPoint(0.25, 0.18));
        data2.push_back(wxRealPoint(0.5, 0.13));
        data2.push_back(wxRealPoint(0.75, 0.09));
        data2.push_back(wxRealPoint(1, 0.05));
        data2.push_back(wxRealPoint(1.25, 0.03));
        data2.push_back(wxRealPoint(1.5, 0.02));
        data2.push_back(wxRealPoint(1.75, 0.01));

        // First step: create the plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add the two series to it.
        dataset->AddSerie(new XYSerie(data1));
        dataset->AddSerie(new XYSerie(data2));

        // create histogram renderer with bar width = 10 and vertical bars
        XYHistoRenderer *histoRenderer = new XYHistoRenderer(10, true);

        // set bar area draw for two series
        histoRenderer->SetBarArea(0, new FillAreaDraw(*wxBLACK_PEN, *wxBLUE_BRUSH));
        histoRenderer->SetBarArea(1, new FillAreaDraw(*wxBLACK_PEN, *wxGREEN_BRUSH));

        // set renderer to dataset
        dataset->SetRenderer(histoRenderer);

        // add our dataset to plot
        plot->AddDataset(dataset);

        // add left and bottom number axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

        // set bottom axis margins
        bottomAxis->SetMargins(15, 15);

        // add axes to plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());
        return chart;
    }
};


/**
 * Sine function chart demo
 */
class XYDemo9 : public ChartDemo
{
public:
    XYDemo9()
    : ChartDemo(wxT("XY Demo 9 - sine"))
    {
    }

    virtual Chart *Create()
    {
        // first step: create plot
        XYPlot *plot = new XYPlot();

        SineFunction *dataset = new SineFunction(1, -10, 10, 0.1);

        // create line renderer
        XYLineRenderer *renderer = new XYLineRenderer();
        dataset->SetRenderer(renderer);

        plot->AddDataset(dataset);

        // add left and bottom number axes
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

        // add axes to plot
        plot->AddAxis(leftAxis);
        plot->AddAxis(bottomAxis);

        // link axes and dataset
        plot->LinkDataVerticalAxis(0, 0);
        plot->LinkDataHorizontalAxis(0, 0);

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());

        // set axis as scrolled, so chart panel can scroll its window.
        return chart;
    }
};

/**
 * Multiseries line xy chart demo.
 * Also it shows how to use legend.
 */
class XYDemo10 : public ChartDemo
{
public:
    XYDemo10()
    : ChartDemo(wxT("XY Demo 10 - lines"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series
        wxVector<wxRealPoint> data1;
        
        data1.push_back(wxRealPoint(1, 1));
        data1.push_back(wxRealPoint(2, 4));
        data1.push_back(wxRealPoint(3, 3));
        data1.push_back(wxRealPoint(4, 5));
        data1.push_back(wxRealPoint(5, 5));
        data1.push_back(wxRealPoint(6, 7));
        data1.push_back(wxRealPoint(7, 7));
        data1.push_back(wxRealPoint(8, 8));

        // XY data for second series
        wxVector<wxRealPoint> data2;
        
        data2.push_back(wxRealPoint(3, 4));
        data2.push_back(wxRealPoint(4, 3));
        data2.push_back(wxRealPoint(5, 2));
        data2.push_back(wxRealPoint(6, 3));
        data2.push_back(wxRealPoint(7, 6));
        data2.push_back(wxRealPoint(8, 3));
        data2.push_back(wxRealPoint(9, 4));
        data2.push_back(wxRealPoint(10, 3));

        // XY data for third series
        wxVector<wxRealPoint> data3;
        
        data3.push_back(wxRealPoint(1, 5));
        data3.push_back(wxRealPoint(2, 7));
        data3.push_back(wxRealPoint(3, 6));
        data3.push_back(wxRealPoint(4, 8));
        data3.push_back(wxRealPoint(5, 4));
        data3.push_back(wxRealPoint(6, 4));
        data3.push_back(wxRealPoint(7, 2));
        data3.push_back(wxRealPoint(8, 1));

        // First step: create the plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add the two series to it.
        dataset->AddSerie(new XYSerie(data1));
        dataset->AddSerie(new XYSerie(data2));
        dataset->AddSerie(new XYSerie(data3));

        // create line renderer
        // set it to draw lines and symbols.
        XYLineRenderer *renderer = new XYLineRenderer(true, true);

        // we can change line pen for serie, for example set short-dash
        // line style and width=2 for third serie
        renderer->SetSeriePen(1, wxThePenList->FindOrCreatePen(*wxGREEN, 2, wxPENSTYLE_SOLID));
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

        // set serie names to be displayed on legend
        dataset->GetSerie(0)->SetName(wxT("First"));
        dataset->GetSerie(1)->SetName(wxT("Second"));
        dataset->GetSerie(2)->SetName(wxT("Third"));

        // set legend
        plot->SetLegend(new Legend(wxBOTTOM, wxCENTER));

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());

        // set axis as scrolled, so chart panel can scroll its window.
        return chart;
    }
};

class XYDemo11 : public ChartDemo
{
public:
    XYDemo11()
    : ChartDemo(wxT("XY Demo 11 - areas"))
    {
    }

    virtual Chart *Create()
    {

        // XY data for first series
        wxVector<wxRealPoint> data1;
        
        data1.push_back(wxRealPoint(1, 1));
        data1.push_back(wxRealPoint(2, 4));
        data1.push_back(wxRealPoint(3, 3));
        data1.push_back(wxRealPoint(4, 5));
        data1.push_back(wxRealPoint(5, 5));
        data1.push_back(wxRealPoint(6, 7));
        data1.push_back(wxRealPoint(7, 7));
        data1.push_back(wxRealPoint(8, 8));

        // XY data for second series
        wxVector<wxRealPoint> data2;
        
        data2.push_back(wxRealPoint(3, 4));
        data2.push_back(wxRealPoint(4, 3));
        data2.push_back(wxRealPoint(5, 2));
        data2.push_back(wxRealPoint(6, 3));
        data2.push_back(wxRealPoint(7, 6));
        data2.push_back(wxRealPoint(8, 3));
        data2.push_back(wxRealPoint(9, 4));
        data2.push_back(wxRealPoint(10, 3));

        // First step: create the plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add the two series to it.
        dataset->AddSerie(new XYSerie(data1));
        dataset->AddSerie(new XYSerie(data2));

        // create area renderer and set it to dataset
        XYAreaRenderer *renderer = new XYAreaRenderer();
        dataset->SetRenderer(renderer);

        // add our dataset to plot
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

        // set serie names to be displayed on legend
        dataset->GetSerie(0)->SetName(wxT("Serie 0"));
        dataset->GetSerie(1)->SetName(wxT("Serie 1"));

        // set legend
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // and finally create chart
        Chart *chart = new Chart(plot, GetName());
        return chart;
    }
};

class XYDemo12 : public ChartDemo
{
public:
    XYDemo12()
    : ChartDemo(wxT("XY Demo 12 - Logarithmic Y Axis"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for series
        wxVector<wxRealPoint> data;
        
        data.push_back(wxRealPoint(1, 1e3));
        data.push_back(wxRealPoint(2, 1.0));
        data.push_back(wxRealPoint(3, 1e2));
        data.push_back(wxRealPoint(4, 2e7));
        data.push_back(wxRealPoint(5, 1e3));

        // First step: create the plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add the two series to it.
        dataset->AddSerie(new XYSerie(data));
        
        // set line renderer to dataset
        // renderer should draw symbols of algorithmic axis to show single points
        // (ie, when drawing five values where the second is zero, the first point won't
        // be visible because no line segment will be drawn from the first to the second point)
        dataset->SetRenderer(new XYLineRenderer(true));

        // add our dataset to plot
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

class XYDemo13 : public ChartDemo
{
public:
    XYDemo13()
    : ChartDemo(wxT("XY Demo 13 - Logarithmic X and Y Axis"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for series
        wxVector<wxRealPoint> data;
        
        data.push_back(wxRealPoint(2, 2));
        data.push_back(wxRealPoint(4, 4));
        data.push_back(wxRealPoint(8, 8));
        data.push_back(wxRealPoint(16, 16));
        data.push_back(wxRealPoint(32, 32));

        // First step: create the plot.
        XYPlot *plot = new XYPlot();

        // Second step: create the dataset.
        XYSimpleDataset *dataset = new XYSimpleDataset();

        // Third step: add the two series to it.
        dataset->AddSerie(new XYSerie(data));        
        
        // set line renderer to dataset
        dataset->SetRenderer(new XYLineRenderer(true, true));

        // add our dataset to plot
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


ChartDemo *xyDemos[] = {
    new XYDemo1(),
    new XYDemo2(),
    new XYDemo3(),
    new XYDemo4(),
    new XYDemo5(),
    new XYDemo6(),
    new XYDemo7(),
//    new XYDemo8(), deleted because it was a duplicate.
    new XYDemo9(),
    new XYDemo10(),
    new XYDemo11(),
    new XYDemo12(),
    new XYDemo13(),
};
int xyDemosCount = WXSIZEOF(xyDemos);
