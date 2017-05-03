/////////////////////////////////////////////////////////////////////////////
// Name:    multipleaxisdemos.cpp
// Purpose: This file contains source code, that demonstrates how to
//          multiple axis charts.
// Author:    Moskvichev Andrey V.
// Created:    2009/04/03
// Copyright:    (c) 2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////


#include "democollection.h"

#include <wx/xy/xyplot.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/xy/xylinerenderer.h>

#include <wx/axis/numberaxis.h>

/**
 * Multiple axis demo.
 */
class MultipleAxisDemo1 : public ChartDemo
{
public:
    MultipleAxisDemo1()
    : ChartDemo(wxT("Multiple axis Demo 1"))
    {
    }

    virtual Chart *Create()
    {
        // First dataset values.
        wxVector<wxRealPoint> values1;
        values1.push_back(wxRealPoint(1, 1));
        values1.push_back(wxRealPoint(2, 3));
        values1.push_back(wxRealPoint(5, 4));
        values1.push_back(wxRealPoint(6, 3));
        values1.push_back(wxRealPoint(7, 6));
        values1.push_back(wxRealPoint(8, 6));
        values1.push_back(wxRealPoint(9, 4));

        // Second dataset values.
        wxVector<wxRealPoint> values2;
        values2.push_back(wxRealPoint(0, 0));
        values2.push_back(wxRealPoint(2, -1));
        values2.push_back(wxRealPoint(4, 6));
        values2.push_back(wxRealPoint(5, 2));
        values2.push_back(wxRealPoint(7, 8));
        values2.push_back(wxRealPoint(8, 4));
        values2.push_back(wxRealPoint(9, -2));

        // Create xy plot.
        XYPlot *plot = new XYPlot();
        
        // Create first dataset and add series 1 to it.
        XYSimpleDataset *dataset1 = new XYSimpleDataset();
        dataset1->AddSerie(new XYSerie(values1));

        // Create second dataset and add series 2 to it.
        XYSimpleDataset *dataset2 = new XYSimpleDataset();
        dataset2->AddSerie(new XYSerie(values2));

        // Create colours for the series.
        wxColour colour1 = DEFAULT_LINE_COLOUR_0;
        wxColour colour2 = DEFAULT_LINE_COLOUR_1;

        // Create renderer for first dataset.
        XYLineRenderer *renderer1 = new XYLineRenderer();
        renderer1->SetSerieColour(0, &colour1);
        dataset1->SetRenderer(renderer1);

        // Create renderer for second dataset.
        XYLineRenderer *renderer2 = new XYLineRenderer();
        renderer2->SetSerieColour(0, &colour2);
        dataset2->SetRenderer(renderer2);

        // Add both datasets to the plot.
        plot->AddDataset(dataset1);
        plot->AddDataset(dataset2);

        // Create left axis for first dataset with the same colours as the line.
        NumberAxis *leftAxis1 = new NumberAxis(AXIS_LEFT);
        leftAxis1->SetLabelTextColour(colour1);
        leftAxis1->SetLabelPen(wxPen(colour1));
        plot->AddAxis(leftAxis1);

        // Create left axis for second dataset also with the same colours as the line.
        NumberAxis *leftAxis2 = new NumberAxis(AXIS_LEFT);
        leftAxis2->SetLabelTextColour(colour2);
        leftAxis2->SetLabelPen(wxPen(colour2));
        plot->AddAxis(leftAxis2);

        // Create bottom axis.
        plot->AddAxis(new NumberAxis(AXIS_BOTTOM));

        // Link the first dataset with the first left axis.
        plot->LinkDataVerticalAxis(0, 0);
        // Link the second dataset with the second left axis.
        plot->LinkDataVerticalAxis(1, 1);

        // Link both datasets with the bottom axis.
        plot->LinkDataHorizontalAxis(0, 0);
        plot->LinkDataHorizontalAxis(1, 0);

        return new Chart(plot, GetName());
    }
};

/**
 * Multiple axis demo.
 */
class MultipleAxisDemo2 : public ChartDemo
{
public:
    MultipleAxisDemo2()
    : ChartDemo(wxT("Multiple axis Demo 2"))
    {
    }

    virtual Chart *Create()
    {
        // First dataset values.
        wxVector<wxRealPoint> values1;
        values1.push_back(wxRealPoint(1, 1));
        values1.push_back(wxRealPoint(2, 3));
        values1.push_back(wxRealPoint(5, 4));
        values1.push_back(wxRealPoint(6, 3));
        values1.push_back(wxRealPoint(7, 6));
        values1.push_back(wxRealPoint(8, 6));
        values1.push_back(wxRealPoint(9, 4));

        // Second dataset values.
        wxVector<wxRealPoint> values2;
        values2.push_back(wxRealPoint(0, 0));
        values2.push_back(wxRealPoint(2, -1));
        values2.push_back(wxRealPoint(4, 6));
        values2.push_back(wxRealPoint(5, 2));
        values2.push_back(wxRealPoint(7, 8));
        values2.push_back(wxRealPoint(8, 4));
        values2.push_back(wxRealPoint(90, -2));

        // Create xy plot.
        XYPlot *plot = new XYPlot();
        
        // Create first dataset and add series 1 to it.
        XYSimpleDataset *dataset1 = new XYSimpleDataset();
        dataset1->AddSerie(new XYSerie(values1));

        // Create second dataset and add series 2 to it.
        XYSimpleDataset *dataset2 = new XYSimpleDataset();
        dataset2->AddSerie(new XYSerie(values2));

        // Create colours for the series.
        wxColour colour1 = DEFAULT_LINE_COLOUR_0;
        wxColour colour2 = DEFAULT_LINE_COLOUR_1;

        // Create renderer for first dataset.
        XYLineRenderer *renderer1 = new XYLineRenderer();
        renderer1->SetSerieColour(0, &colour1);
        dataset1->SetRenderer(renderer1);

        // Create renderer for second dataset.
        XYLineRenderer *renderer2 = new XYLineRenderer();
        renderer2->SetSerieColour(0, &colour2);
        dataset2->SetRenderer(renderer2);

        // Add both datasets to the plot.
        plot->AddDataset(dataset1);
        plot->AddDataset(dataset2);

        // Create left axis for first dataset with the same colours as the line.
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        leftAxis->SetLabelTextColour(colour1);
        leftAxis->SetTitle("Left Axis");
        plot->AddAxis(leftAxis);

        // Create right axis for second dataset also with the same colours as the line.
        NumberAxis *rightAxis = new NumberAxis(AXIS_RIGHT);
        rightAxis->SetLabelTextColour(colour2);
        rightAxis->SetTitle("Right Axis");
        plot->AddAxis(rightAxis);

        // Create a top axis for first dataset.
        NumberAxis *topAxis = new NumberAxis(AXIS_TOP);
        topAxis->SetLabelTextColour(colour1);
        topAxis->SetTitle("Top Axis");
        plot->AddAxis(topAxis);

        // Create a bottom axis for second dataset.
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetLabelTextColour(colour2);
        bottomAxis->SetTitle("Bottom Axis");
        plot->AddAxis(bottomAxis);

        // Link the first dataset with left axis.
        plot->LinkDataVerticalAxis(0, 0);
        
        // Link the second dataset with right axis.
        plot->LinkDataVerticalAxis(1, 1);

        // Link first dataset with top axis.
        plot->LinkDataHorizontalAxis(0, 0);

        // Link second dataset with bottom axis.
        plot->LinkDataHorizontalAxis(1, 1);

        return new Chart(plot, GetName());
    }
};

ChartDemo *multipleAxisDemos[] = {
        new MultipleAxisDemo1(),
        new MultipleAxisDemo2(),
};
int multipleAxisDemosCount = WXSIZEOF(multipleAxisDemos);
