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

#include <wx/xy/xyplot.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/xy/xyhistorenderer.h>
#include <wx/xy/xysimpledataset.h>

#include <wx/multiplot.h>

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
        // First plot data.
        wxVector<wxRealPoint> data1;
        data1.push_back(wxRealPoint(10, 20));
        data1.push_back(wxRealPoint(13, 16));
        data1.push_back(wxRealPoint(7, 30));
        data1.push_back(wxRealPoint(15, 34));
        data1.push_back(wxRealPoint(25, 4));

        // Second plot data.
        wxVector<wxRealPoint> data2;
        data2.push_back(wxRealPoint(45, 40));
        data2.push_back(wxRealPoint(23, 16));
        data2.push_back(wxRealPoint(43, 60));
        data2.push_back(wxRealPoint(25, 7));
        data2.push_back(wxRealPoint(66, 4));

        MultiPlot *multiPlot = new MultiPlot(1, 2, 5, 5);

        // Create the left axis, that will be shared between two plots.
        NumberAxis *sharedLeftAxis = new NumberAxis(AXIS_LEFT);

        // Create first plot.
        XYPlot *plot1 = new XYPlot();

        // Create the first dataset and add the series to it.
        XYSimpleDataset *dataset1 = new XYSimpleDataset();
        dataset1->AddSerie(new XYSerie(data1));

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

        // Create the second dataset and add the second series to it.
        XYSimpleDataset *dataset2 = new XYSimpleDataset();
        dataset2->AddSerie(new XYSerie(data2));

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
        // First plot data.
        wxVector<wxRealPoint> data1;
        data1.push_back(wxRealPoint(10, 20));
        data1.push_back(wxRealPoint(43, 16));
        data1.push_back(wxRealPoint(17, 30));
        data1.push_back(wxRealPoint(65, 34));
        data1.push_back(wxRealPoint(25, 4));

        // Second plot data.
        wxVector<wxRealPoint> data2;
        data2.push_back(wxRealPoint(45, 40));
        data2.push_back(wxRealPoint(23, 16));
        data2.push_back(wxRealPoint(35, 60));
        data2.push_back(wxRealPoint(15, 7));
        data2.push_back(wxRealPoint(5, 20));
        data2.push_back(wxRealPoint(66, 4));
        
        // Create a multiplot.
        MultiPlot *multiPlot = new MultiPlot(2, 1, 5, 5);

        // create left axis, that will be shared between two plots
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);

        // Create the first plot.
        XYPlot *plot1 = new XYPlot();

        // Create first dataset and add series to it.
        XYSimpleDataset *dataset1 = new XYSimpleDataset();
        dataset1->AddSerie(new XYSerie(data1));

        // Set th eline renderer for the dataset.
        dataset1->SetRenderer(new XYLineRenderer());

        // Add our dataset to plot.
        plot1->AddDataset(dataset1);

        // Create a left number axis.
        NumberAxis *leftAxis1 = new NumberAxis(AXIS_LEFT);

        // Create an axis share for second plot to share leftAxis between plots (normally it will be invisible).
        AxisShare *bottomAxis1 = new AxisShare(bottomAxis);

        // add axes to plot
        plot1->AddAxis(leftAxis1);
        plot1->AddAxis(bottomAxis1);

        // link axes and dataset
        plot1->LinkDataVerticalAxis(0, 0);
        plot1->LinkDataHorizontalAxis(0, 0);

        // Create the second plot.
        XYPlot *plot2 = new XYPlot();

        // Create dataset and add series to it.
        XYSimpleDataset *dataset2 = new XYSimpleDataset();
        dataset2->AddSerie(new XYSerie(data2));

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
