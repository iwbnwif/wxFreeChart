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

#include <wx/plot/barplot.h>
#include <wx/render/barrenderer.h>

#include <wx/axis/numberaxis.h>
#include <wx/axis/categoryaxis.h>

#include <wx/dataset.h>

/**
 * Simple demo with one dataset, and left and bottom axes.
 */
class BarDemo1 : public ChartDemo
{
public:
    BarDemo1()
    : ChartDemo(wxT("Bar Demo 1 - Single Series"))
    {
    }

    virtual Chart *Create()
    {
        // Create the category dataset and add the categories.
        UniDataSet* dataset = new UniDataSet("Bar Demo 1");
        dataset->AddCategory("Cat 1");
        dataset->AddCategory("Cat 2");
        dataset->AddCategory("Cat 3");
        dataset->AddCategory("Cat 4");
        dataset->AddCategory("Cat 5");

        // Create the series data.
        DataSeries* series = new DataSeries("Series 1");
        series->AddPoint(new UniDataPoint(10.0));
        series->AddPoint(new UniDataPoint(20.0));
        series->AddPoint(new UniDataPoint(5.0));
        series->AddPoint(new UniDataPoint(50.0));
        series->AddPoint(new UniDataPoint(25.0));
        
        // Add the series to the data set.
        dataset->AddSeries(series);

        // Assign a renderer to the series.
        BarType* barType = new NormalBarType(30);
        
        // dataset1->SetSeriesRenderer(0, new BarRenderer(barType1));
        dataset->SetRenderer(new BarRenderer(barType));
       
        // Create bar plot
        BarPlot *plot = new BarPlot(BARPLOT_VERTICAL);

        // Add dataset to plot
        plot->AddDataset(dataset);

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
        
        // Link the data sets to the axis.
        plot->LinkDataHorizontalAxis(0, 0);
        plot->LinkDataVerticalAxis(0, 0);

        plot->SetBackground(new FillAreaDraw(*wxTRANSPARENT_PEN, *wxTRANSPARENT_BRUSH));

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

#if 0
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
        BarPlot *plot = new BarPlot(BARPLOT_VERTICAL);

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
#endif 


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
        // Create the category dataset and add the categories.
        UniDataSet* dataset = new UniDataSet("Bar Demo 1");
        dataset->AddCategory("Cat 1");
        dataset->AddCategory("Cat 2");
        dataset->AddCategory("Cat 3");
        dataset->AddCategory("Cat 4");
        dataset->AddCategory("Cat 5");

        // Create the first series data.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new UniDataPoint(7.5));
        series1->AddPoint(new UniDataPoint(19.0));
        series1->AddPoint(new UniDataPoint(19.0));
        series1->AddPoint(new UniDataPoint(22.0));
        series1->AddPoint(new UniDataPoint(25.0));        
        
        // Create the second series data.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new UniDataPoint(16.0));
        series2->AddPoint(new UniDataPoint(10.0));
        series2->AddPoint(new UniDataPoint(15.0));
        series2->AddPoint(new UniDataPoint(30.0));
        series2->AddPoint(new UniDataPoint(45.0));        

        dataset->AddSeries(series1);
        dataset->AddSeries(series2);

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
        BarPlot *plot = new BarPlot(BARPLOT_HORIZONTAL);

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
        // Create the category dataset and add the categories.
        UniDataSet* dataset = new UniDataSet("Bar Demo 4");
        dataset->AddCategory("Cat 1");
        dataset->AddCategory("Cat 2");
        dataset->AddCategory("Cat 3");
        dataset->AddCategory("Cat 4");
        dataset->AddCategory("Cat 5");

        // Create the first series data.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new UniDataPoint(10));
        series1->AddPoint(new UniDataPoint(20.0));
        series1->AddPoint(new UniDataPoint(5.0));
        series1->AddPoint(new UniDataPoint(50.0));
        series1->AddPoint(new UniDataPoint(25.0));        
        
        // Create the second series data.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new UniDataPoint(16.0));
        series2->AddPoint(new UniDataPoint(10.0));
        series2->AddPoint(new UniDataPoint(15.0));
        series2->AddPoint(new UniDataPoint(30.0));
        series2->AddPoint(new UniDataPoint(45.0));        

        dataset->AddSeries(series1);
        dataset->AddSeries(series2);

        // Create stacked bar type
        BarType *barType = new StackedBarType(40, 0);

        // Set bar renderer for it, with stacked bar type
        BarRenderer *renderer = new BarRenderer(barType);

        // assign renderer to dataset - necessary step
        dataset->SetRenderer(renderer);

        // Create bar plot
        BarPlot *plot = new BarPlot(BARPLOT_HORIZONTAL);

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
        // Create the category dataset and add the categories.
        UniDataSet* dataset = new UniDataSet("Bar Demo 1");
        dataset->AddCategory("Cat 1");
        dataset->AddCategory("Cat 2");
        dataset->AddCategory("Cat 3");
        dataset->AddCategory("Cat 4");
        dataset->AddCategory("Cat 5");

        // Create the first series data.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new UniDataPoint(10.0));
        series1->AddPoint(new UniDataPoint(20.0));
        series1->AddPoint(new UniDataPoint(5.0));
        series1->AddPoint(new UniDataPoint(50.0));
        series1->AddPoint(new UniDataPoint(25.0));        
        
        // Create the second series data.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new UniDataPoint(16.0));
        series2->AddPoint(new UniDataPoint(10.0));
        series2->AddPoint(new UniDataPoint(15.0));
        series2->AddPoint(new UniDataPoint(30.0));
        series2->AddPoint(new UniDataPoint(45.0));        

        dataset->AddSeries(series1);
        dataset->AddSeries(series2);

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
        BarPlot *plot = new BarPlot(BARPLOT_HORIZONTAL);

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
        // Create the category dataset and add the categories.
        UniDataSet* dataset = new UniDataSet("Bar Demo 6");
        dataset->AddCategory(wxDateTime(1, wxDateTime::Jan, 2010).Format("%Y"));
        dataset->AddCategory(wxDateTime(1, wxDateTime::Jan, 2011).Format("%Y"));
        dataset->AddCategory(wxDateTime(1, wxDateTime::Jan, 2012).Format("%Y"));
        dataset->AddCategory(wxDateTime(1, wxDateTime::Jan, 2013).Format("%Y"));
        dataset->AddCategory(wxDateTime(1, wxDateTime::Jan, 2014).Format("%Y"));
        dataset->AddCategory(wxDateTime(1, wxDateTime::Jan, 2015).Format("%Y"));
        dataset->AddCategory(wxDateTime(1, wxDateTime::Jan, 2016).Format("%Y"));
        dataset->AddCategory(wxDateTime(1, wxDateTime::Jan, 2017).Format("%Y"));

        // Create the first series data.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new UniDataPoint(771994.0));
        series1->AddPoint(new UniDataPoint(718712.0));
        series1->AddPoint(new UniDataPoint(682422.0));
        series1->AddPoint(new UniDataPoint(713415.0));
        series1->AddPoint(new UniDataPoint(807516.0));        
        series1->AddPoint(new UniDataPoint(894631.0));        
        series1->AddPoint(new UniDataPoint(1023109.0));        
        series1->AddPoint(new UniDataPoint(1148481.0));        
        
        // Create the second series data.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new UniDataPoint(298603.0));
        series2->AddPoint(new UniDataPoint(286184.0));
        series2->AddPoint(new UniDataPoint(292299.0));
        series2->AddPoint(new UniDataPoint(304342.0));
        series2->AddPoint(new UniDataPoint(353072.0));        
        series2->AddPoint(new UniDataPoint(389122.0));        
        series2->AddPoint(new UniDataPoint(433905.0));        
        series2->AddPoint(new UniDataPoint(497245.0));        

        dataset->AddSeries(series1);
        dataset->AddSeries(series2);

        /*
                
        // Create dataset
        CategorySimpleDataset *dataset = new CategorySimpleDataset(names, WXSIZEOF(names));

        // add two series to it
        dataset->AddSerie(wxT("Goods"), values1, WXSIZEOF(values1));
        dataset->AddSerie(wxT("Services"), values2, WXSIZEOF(values2));
        */
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
        BarPlot *plot = new BarPlot(BARPLOT_VERTICAL);

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
        
        plot->SetBackground(new FillAreaDraw(*wxTRANSPARENT_PEN, *wxTRANSPARENT_BRUSH));

        // And finally construct and return chart
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
