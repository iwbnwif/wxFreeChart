/////////////////////////////////////////////////////////////////////////////
// Name:    bardemos.cpp
// Purpose: Code for bar chart demos
// Author:    Moskvichev Andrey V.
// Created:    2008/11/12
// Copyright:    (c) 2008-2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

/*
 * This file contains demos for Category type charts.
 */

#include "democollection.h"

#include <wx/bars/barplot.h>

#include <wx/axis/numberaxis.h>
#include <wx/axis/categoryaxis.h>

#include <wx/xy/xyhistorenderer.h>

#include <wx/category/categorysimpledataset.h>

/**
 * Simple demo with one dataset, and left and bottom axes.
 */
class BarDemo1 : public ChartDemo
{
public:
    BarDemo1()
    : ChartDemo(wxT("Bar demo 1 - Single Series"))
    {
    }

    virtual Chart *Create()
    {
        wxString names[] = { // category names
                wxT("Cat 1"),
                wxT("Cat 2"),
                wxT("Cat 3"),
                wxT("Cat 4"),
                wxT("Cat 5"),
        };
        // serie 1 values - we have only one serie
        double values[] = {
                10.0,
                20.0,
                5.0,
                50.0,
                25.0,
        };

        // Create dataset
        CategorySimpleDataset *dataset = new CategorySimpleDataset(names, WXSIZEOF(names));

        // add serie to it
        dataset->AddSerie(wxT("Serie 0"), values, WXSIZEOF(values));

        // create normal bar type with bar width = 10
        BarType *barType = new NormalBarType(30);

        // Set bar renderer for it
        dataset->SetRenderer(new BarRenderer(barType));

        // Create bar plot
        BarPlot *plot = new BarPlot();

        // Create left number axis, set it's margins, and add it to plot
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        leftAxis->SetMargins(5, 0);
        leftAxis->SetLabelTextColour(wxColour("#DADADA"));
        leftAxis->SetLabelPen(wxPen(wxColour("#DADADA")));
        leftAxis->SetMajorGridlinePen(wxPen(wxColour("#DADADA")));
        plot->AddAxis(leftAxis);

        // Create bottom axis, set it's margins, and add it to plot
        CategoryAxis *bottomAxis = new CategoryAxis(AXIS_BOTTOM);
        bottomAxis->SetMargins(20, 20);
        bottomAxis->SetLabelTextColour(wxColour("#DADADA"));
        bottomAxis->SetLabelPen(wxPen(wxColour("#DADADA")));
        plot->AddAxis(bottomAxis);

        // Add dataset to plot
        plot->AddDataset(dataset);
        
        plot->SetBackground(new FillAreaDraw(*wxTRANSPARENT_PEN, *wxTRANSPARENT_BRUSH));

        // Link first dataset with horizontal axis
        plot->LinkDataHorizontalAxis(0, 0);

        // Link first dataset with vertical axis
        plot->LinkDataVerticalAxis(0, 0);

        // Show a legend at the centre-right position.
        Legend* legend = new Legend(wxCENTER, wxRIGHT, new FillAreaDraw(*wxTRANSPARENT_PEN, *wxTRANSPARENT_BRUSH));
        plot->SetLegend(legend);

        // Create a custom title.
        TextElement title(GetName());
        title.SetColour(wxColour("#DADADA"));

        // and finally construct and return chart
        Chart* chart = new Chart(plot, new Header(title));
        
        // Create a radial gradient background.
        // Warning: Radial gradients are slow to draw in wxWidgets!
        chart->SetBackground(new GradientAreaDraw(*wxTRANSPARENT_PEN, 
                                                    wxColour("#8A8A8A"), wxColour("#707070"), wxALL));
        
        return chart;
    }
};

/**
 * Simple demo with one dataset, and left and bottom axes.
 */
class BarDemo2 : public ChartDemo
{
public:
    BarDemo2()
    : ChartDemo(wxT("Bar Demo 2 - One Category"))
    {
    }

    virtual Chart *Create()
    {
        wxString names[] = { // category names
                wxT("Cat 1"),
        };
        // serie 1 values - we have only one serie
        double values[] = {
                10.0,
        };

        // Create dataset
        CategorySimpleDataset *dataset = new CategorySimpleDataset(names, WXSIZEOF(names));

        // add serie to it
        dataset->AddSerie(wxT("Serie 0"), values, WXSIZEOF(values));

        // Create bar type
        BarType *barType = new NormalBarType(10);

        // Set histogram renderer for it
        dataset->SetRenderer(new BarRenderer(barType));

        // Create bar plot
        BarPlot *plot = new BarPlot();

        // Add left number axis
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        leftAxis->SetMargins(10, 10);
        plot->AddAxis(leftAxis);

        // Add bottom axis
        CategoryAxis *bottomAxis = new CategoryAxis(AXIS_BOTTOM);
        bottomAxis->SetMargins(0, 5);
        plot->AddAxis(bottomAxis);

        // Add dataset to plot
        plot->AddDataset(dataset);

        // Link first dataset with first horizontal axis
        plot->LinkDataHorizontalAxis(0, 0);

        // Link first dataset with first vertical axis
        plot->LinkDataVerticalAxis(0, 0);

        // and finally construct and return chart
        return new Chart(plot, GetName());
    }
};

/**
 * Simple demo with one dataset having 2 series, and left and bottom axes.
 * Bars are horizontal.
 */
class BarDemo3 : public ChartDemo
{
public:
    BarDemo3()
    : ChartDemo(wxT("Bar Demo 3 - Normal Bars"))
    {
    }

    virtual Chart *Create()
    {
        wxString names[] = { // category names
                wxT("Cat 1"),
                wxT("Cat 2"),
                wxT("Cat 3"),
                wxT("Cat 4"),
                wxT("Cat 5"),
        };

        // serie 1 values
        double values1[] = {
                7.5,
                19,
                19,
                22,
                25,
        };

        // serie 2 values
        double values2[] = {
                16,
                10,
                15,
                30,
                45,
        };

        // Create dataset
        CategorySimpleDataset *dataset = new CategorySimpleDataset(names, WXSIZEOF(names));

        // add two series to it
        dataset->AddSerie(wxT("Serie 1"), values1, WXSIZEOF(values1));
        dataset->AddSerie(wxT("Serie 2"), values2, WXSIZEOF(values2));

        // Create bat type
        BarType *barType = new NormalBarType(20);

        // Set bar renderer for it, with normal bars
        BarRenderer *renderer = new BarRenderer(barType);
        
        // Why doesn't SetSerieColour work for bars?
        renderer->SetBarDraw(0, new FillAreaDraw(*wxTRANSPARENT_PEN, wxBrush(wxColour("#007F7F"))));
        renderer->SetBarDraw(1, new FillAreaDraw(*wxTRANSPARENT_PEN, wxBrush(wxColour("#EA4B32"))));
        
        // assign renderer to dataset - necessary step
        dataset->SetRenderer(renderer);

        // Create bar plot
        BarPlot *plot = new BarPlot();

        // Add left category axis
        CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
        leftAxis->SetMargins(40, 40); // setup margins, so bars will fit to plot.
        
        plot->AddAxis(leftAxis);

        // Add bottom number axis
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetMargins(0, 5);
        bottomAxis->IntegerValues(true);
        plot->AddAxis(bottomAxis);

        // Add dataset to plot
        plot->AddDataset(dataset);

        // Link first dataset with first horizontal axis
        plot->LinkDataHorizontalAxis(0, 0);

        // Link first dataset with first vertical axis
        plot->LinkDataVerticalAxis(0, 0);

        // and finally construct and return chart
        return new Chart(plot, GetName());
    }
};

/**
 * Stacked bars demo.
 */
class BarDemo4 : public ChartDemo
{
public:
    BarDemo4()
    : ChartDemo(wxT("Bar Demo 4 - Stacked Bars"))
    {
    }

    virtual Chart *Create()
    {
        wxString names[] = { // category names
                wxT("Cat 1"),
                wxT("Cat 2"),
                wxT("Cat 3"),
                wxT("Cat 4"),
                wxT("Cat 5"),
        };

        // serie 1 values
        double values1[] = {
                10,
                20,
                5,
                50,
                25,
        };

        // serie 2 values
        double values2[] = {
                16,
                10,
                15,
                30,
                45,
        };

        // serie 3 values
        double values3[] = {
                14,
                20,
                10,
                20,
                10,
        };
        // Create dataset
        CategorySimpleDataset *dataset = new CategorySimpleDataset(names, WXSIZEOF(names));

        // add two series to it
        dataset->AddSerie(wxT("Serie 1"), values1, WXSIZEOF(values1));
        dataset->AddSerie(wxT("Serie 2"), values2, WXSIZEOF(values2));
        dataset->AddSerie(wxT("Serie 3"), values3, WXSIZEOF(values3));

        // Create stacked bar type
        BarType *barType = new StackedBarType(40, 0);

        // Set bar renderer for it, with stacked bar type
        BarRenderer *renderer = new BarRenderer(barType);

        // assign renderer to dataset - necessary step
        dataset->SetRenderer(renderer);

        // Create bar plot
        BarPlot *plot = new BarPlot();

        // Add left category axis
        CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
        leftAxis->SetMargins(20, 20);
        plot->AddAxis(leftAxis);

        // Add bottom number axis
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetMargins(0, 5);
        plot->AddAxis(bottomAxis);

        // Add dataset to plot
        plot->AddDataset(dataset);

        // Link first dataset with first horizontal axis
        plot->LinkDataHorizontalAxis(0, 0);

        // Link first dataset with first vertical axis
        plot->LinkDataVerticalAxis(0, 0);

        // and finally construct and return chart
        return new Chart(plot, GetName());
    }
};

/**
 * Layered bars demo.
 */
class BarDemo5 : public ChartDemo
{
public:
    BarDemo5()
    : ChartDemo(wxT("Bar Demo 5 - Layered Bars"))
    {
    }

    virtual Chart *Create()
    {
        wxString names[] = { // category names
                wxT("Cat 1"),
                wxT("Cat 2"),
                wxT("Cat 3"),
                wxT("Cat 4"),
                wxT("Cat 5"),
        };

        // serie 1 values
        double values1[] = {
                10,
                20,
                5,
                50,
                25,
        };

        // serie 2 values
        double values2[] = {
                16,
                10,
                15,
                30,
                45,
        };

        // Create dataset
        CategorySimpleDataset *dataset = new CategorySimpleDataset(names, WXSIZEOF(names));

        // add two series to it
        dataset->AddSerie(wxT("Serie 1"), values1, WXSIZEOF(values1));
        dataset->AddSerie(wxT("Serie 2"), values2, WXSIZEOF(values2));

        // create layered bar type with width=40 and base=0
        BarType *barType = new LayeredBarType(40, 0);

        // Set bar renderer for it, with layered bar type
        BarRenderer *renderer = new BarRenderer(barType);

        // Some eye-candy: gradient bars
        renderer->SetBarDraw(0, new GradientAreaDraw(DEFAULT_BAR_FILL_COLOUR_0, DEFAULT_BAR_FILL_COLOUR_0, 
                                                        DEFAULT_BAR_FILL_COLOUR_0.ChangeLightness(150), wxEAST));
        renderer->SetBarDraw(1, new GradientAreaDraw(DEFAULT_BAR_FILL_COLOUR_1, DEFAULT_BAR_FILL_COLOUR_1, 
                                                        DEFAULT_BAR_FILL_COLOUR_1.ChangeLightness(150), wxEAST));

        // assign renderer to dataset
        dataset->SetRenderer(renderer);

        // Create bar plot
        BarPlot *plot = new BarPlot();

        // Add left category axis
        CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
        leftAxis->SetMargins(20, 20);
        plot->AddAxis(leftAxis);

        // Add bottom number axis
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetMargins(0, 5);
        plot->AddAxis(bottomAxis);

        // Add dataset to plot
        plot->AddDataset(dataset);

        // Link first dataset with first horizontal axis
        plot->LinkDataHorizontalAxis(0, 0);

        // Link first dataset with first vertical axis
        plot->LinkDataVerticalAxis(0, 0);

        // and finally construct and return chart
        return new Chart(plot, GetName());
    }
};

/**
 * Layered date bars demo.
 */
class BarDemo6 : public ChartDemo
{
public:
    BarDemo6()
    : ChartDemo(wxT("Bar Demo 6 - Date Bars"))
    {
    }

    virtual Chart *Create()
    {
        // TODO: !!! remake this demo to use dates, not string representation of years!
        wxString names[] = { // category names
                wxT("2010"),
                wxT("2011"),
                wxT("2012"),
                wxT("2013"),
                wxT("2014"),
                wxT("2015"),
                wxT("2016"),
                wxT("2017"),
        };

        // serie 1 values
        double values1[] = {
                771994,    718712,    682422,    713415,    807516,    894631,    1023109, 1148481,
        };

        // serie 2 values
        double values2[] = {
                298603,    286184,    292299,    304342,    353072,    389122,    433905,    497245,
        };
        
                
        // Create dataset
        CategorySimpleDataset *dataset = new CategorySimpleDataset(names, WXSIZEOF(names));

        // add two series to it
        dataset->AddSerie(wxT("Goods"), values1, WXSIZEOF(values1));
        dataset->AddSerie(wxT("Services"), values2, WXSIZEOF(values2));

        // create layered bar type with width=20 and base=0
        BarType *barType = new LayeredBarType(30, 0);

        // Set bar renderer for it, with layered bar type
        BarRenderer *renderer = new BarRenderer(barType);

        // Some eye-candy: gradient bars.
        renderer->SetBarDraw(0, new GradientAreaDraw(*wxTRANSPARENT_PEN, DEFAULT_BAR_FILL_COLOUR_0, 
                                                        DEFAULT_BAR_FILL_COLOUR_0.ChangeLightness(50), wxSOUTH));
        renderer->SetBarDraw(1, new GradientAreaDraw(*wxTRANSPARENT_PEN, DEFAULT_BAR_FILL_COLOUR_1, 
                                                        DEFAULT_BAR_FILL_COLOUR_1.ChangeLightness(50), wxSOUTH));

        // assign renderer to dataset
        dataset->SetRenderer(renderer);

        // Create bar plot
        BarPlot *plot = new BarPlot();

        // Add left number axis
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);

        ///// leftAxis Experiments.
        leftAxis->SetMargins(20, 0);
        // leftAxis->SetMajorLabelSteps(5);
        leftAxis->SetMinorIntervalCount(0);
        // leftAxis->SetLabelSkip(5);
        
        plot->AddAxis(leftAxis);

        // Add bottom category axis
        CategoryAxis *bottomAxis = new CategoryAxis(AXIS_BOTTOM);
        bottomAxis->SetMargins(20, 20);
        bottomAxis->SetVerticalLabelText(true);
        plot->AddAxis(bottomAxis);

        // Add dataset to plot
        plot->AddDataset(dataset);

        // Link first dataset with first horizontal axis
        plot->LinkDataHorizontalAxis(0, 0);

        // Link first dataset with first vertical axis
        plot->LinkDataVerticalAxis(0, 0);

        // Set legend
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));
        
        // Experiments.
        plot->SetDrawGrid(true, false);
        
        plot->SetBackground(new FillAreaDraw(*wxGREEN_PEN, *wxBLUE_BRUSH));
        plot->SetBackground(new FillAreaDraw(*wxTRANSPARENT_PEN, *wxTRANSPARENT_BRUSH));

        // and finally construct and return chart
        return new Chart(plot, wxT("USA Export Goods / Services"));;
    }
};

ChartDemo *barDemos[] = {
        new BarDemo1(),
        // new BarDemo2(), // demo 2 is buggy!
        new BarDemo3(),
        new BarDemo4(),
        new BarDemo5(),
        new BarDemo6(),
};
int barDemosCount = WXSIZEOF(barDemos);
