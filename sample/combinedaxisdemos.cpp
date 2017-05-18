/////////////////////////////////////////////////////////////////////////////
// Name:    combinedaxisdemos.cpp
// Purpose: This file contains source code, that demonstrates how to
//          combined axis charts.
// Author:    Moskvichev Andrey V.
// Created:    2009/04/03
// Copyright:    (c) 2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/multiplot.h>
#include <wx/xy/xyhistorenderer.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xyplot.h>

/**
 * Combined axis demo.
 */
class CombinedAxisDemo1 : public ChartDemo
{
public:
    CombinedAxisDemo1()
    : ChartDemo(wxT("Combined Axis Demo 1 - Left Axis"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(10, 20));
        series1->AddPoint(new BiDataPoint(13, 16));
        series1->AddPoint(new BiDataPoint(7, 30));
        series1->AddPoint(new BiDataPoint(15, 34));
        series1->AddPoint(new BiDataPoint(25, 4));

        // XY data for second series.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new BiDataPoint(45, 40));
        series2->AddPoint(new BiDataPoint(23, 16));
        series2->AddPoint(new BiDataPoint(43, 60));
        series2->AddPoint(new BiDataPoint(25, 7));
        series2->AddPoint(new BiDataPoint(66, 4));

        MultiPlot *multiPlot = new MultiPlot(1, 2, 5, 5);

        // Create the left axis, that will be shared between two plots.
        NumberAxis *sharedLeftAxis = new NumberAxis(AXIS_LEFT);

        // Create first plot.
        XYPlot *plot1 = new XYPlot();

        // Create first dataset and add series 1 to it.
        BiDataSet* dataset1 = new BiDataSet("Dataset 1");
        dataset1->AddSeries(series1);  

        // Create a line renderer for the dataset.
        dataset1->SetRenderer(new XYLineRenderer());

        // Add our dataset to the plot.
        plot1->AddDataset(dataset1);

        // Create an axis share for first plot to share leftAxis between plots.
        AxisShare *leftAxis1 = new AxisShare(sharedLeftAxis);
        
        // And make it visible for first plot.
        leftAxis1->SetShareVisible(true);

        // Create bottom number axes.
        NumberAxis *bottomAxis1 = new NumberAxis(AXIS_BOTTOM);
        bottomAxis1->SetVerticalLabelText(true);
        bottomAxis1->SetMargins(10, 15);

        // Add axes to plot.
        plot1->AddAxis(leftAxis1);
        plot1->AddAxis(bottomAxis1);

        // Link axes and dataset.
        plot1->LinkDataVerticalAxis(0, 0);
        plot1->LinkDataHorizontalAxis(0, 0);

        //
        // create second plot
        //
        XYPlot *plot2 = new XYPlot();

        // Create second dataset and add series 2 to it.
        BiDataSet* dataset2 = new BiDataSet("Dataset 2");
        dataset2->AddSeries(series2);

        // Set the line renderer for the dataset.
        dataset2->SetRenderer(new XYLineRenderer());

        // Add our dataset to the plot.
        plot2->AddDataset(dataset2);

        // Create an axis share for second plot to share leftAxis between plots (it will normally be invisible).
        AxisShare *leftAxis2 = new AxisShare(sharedLeftAxis);

        // Create th ebottom number axis.
        NumberAxis *bottomAxis2 = new NumberAxis(AXIS_BOTTOM);
        bottomAxis2->SetMargins(15, 10);
        bottomAxis2->SetVerticalLabelText(true);

        // Add axes to plot.
        plot2->AddAxis(leftAxis2);
        plot2->AddAxis(bottomAxis2);

        // Link axes and dataset.
        plot2->LinkDataVerticalAxis(0, 0);
        plot2->LinkDataHorizontalAxis(0, 0);

        // Add the plots to the multiplot.
        multiPlot->AddPlot(plot1);
        multiPlot->AddPlot(plot2);

        // And finally create the chart.
        return new Chart(multiPlot, GetName());
    }
};

class CombinedAxisDemo2 : public ChartDemo
{
public:
    CombinedAxisDemo2()
    : ChartDemo(wxT("Combined Axis Demo 2 - Bottom Axis"))
    {
    }

    virtual Chart *Create()
    {
        // XY data for first series.
        DataSeries* series1 = new DataSeries("Series 1");
        series1->AddPoint(new BiDataPoint(10, 20));
        series1->AddPoint(new BiDataPoint(13, 16));
        series1->AddPoint(new BiDataPoint(7, 30));
        series1->AddPoint(new BiDataPoint(15, 34));
        series1->AddPoint(new BiDataPoint(25, 4));

        // XY data for first series.
        DataSeries* series2 = new DataSeries("Series 2");
        series2->AddPoint(new BiDataPoint(45, 20));
        series2->AddPoint(new BiDataPoint(23, 16));
        series2->AddPoint(new BiDataPoint(35, 30));
        series2->AddPoint(new BiDataPoint(15, 34));
        series2->AddPoint(new BiDataPoint(5, 4));
        series2->AddPoint(new BiDataPoint(66, 4));
        
        // Create a multiplot.
        MultiPlot *multiPlot = new MultiPlot(2, 1, 5, 5);

        // Create bottom axis, that will be shared between two plots
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

        // Create the first plot.
        XYPlot *plot1 = new XYPlot();

        // Create first dataset and add series to it.
        BiDataSet* dataset1 = new BiDataSet("Dataset 1");
        dataset1->AddSeries(series1);

        // Set the line renderer for the dataset.
        dataset1->SetRenderer(new XYLineRenderer());

        // Add our dataset to plot.
        plot1->AddDataset(dataset1);

        // Create a left number axis.
        NumberAxis *leftAxis1 = new NumberAxis(AXIS_LEFT);

        // Create an axis share for second plot to share leftAxis between plots (normally it will be invisible).
        AxisShare *bottomAxis1 = new AxisShare(bottomAxis);

        // Add axes to plot
        plot1->AddAxis(leftAxis1);
        plot1->AddAxis(bottomAxis1);

        // Link axes and dataset
        plot1->LinkDataVerticalAxis(0, 0);
        plot1->LinkDataHorizontalAxis(0, 0);

        // Create the second plot.
        XYPlot *plot2 = new XYPlot();

        // Create dataset and add series to it.
        BiDataSet* dataset2 = new BiDataSet("Dataset 2");
        dataset2->AddSeries(series2);

        // Create a histogram renderer to render the dataset.
        XYHistoRenderer *renderer2 = new XYHistoRenderer();
        renderer2->SetBarArea(0, new FillAreaDraw(*wxBLACK, *wxGREEN));
        dataset2->SetRenderer(renderer2);

        // add our dataset to plot
        plot2->AddDataset(dataset2);

        // create left number axes
        NumberAxis *leftAxis2 = new NumberAxis(AXIS_LEFT);

        // create axis share for second plot to share leftAxis between plots
        AxisShare *bottomAxis2 = new AxisShare(bottomAxis);
        // and make it visible for second plot
        bottomAxis2->SetShareVisible(true);

        // add axes to plot
        plot2->AddAxis(leftAxis2);
        plot2->AddAxis(bottomAxis2);

        // link axes and dataset
        plot2->LinkDataVerticalAxis(0, 0);
        plot2->LinkDataHorizontalAxis(0, 0);

        // add first plot to multiplot
        multiPlot->AddPlot(plot1);

        // add second plot to multiplot
        multiPlot->AddPlot(plot2);

        // and finally create chart
        return new Chart(multiPlot, GetName());
    }
};

ChartDemo *combinedAxisDemos[] = {
        new CombinedAxisDemo1(),
        new CombinedAxisDemo2(),
};
int combinedAxisDemosCount = WXSIZEOF(combinedAxisDemos);
