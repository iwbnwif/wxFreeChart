/////////////////////////////////////////////////////////////////////////////
// Name:    bubbledemos.cpp
// Purpose: This file contains source code, that demonstrates how to
//          create bubble charts.
// Author:    Moskvichev Andrey V.
// Created:    2009/04/03
// Copyright:    (c) 2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/axis/numberaxis.h>
#include <wx/plot/bubbleplot.h>
#include <wx/render/xyzrenderer.h>

#define SERIES_ADD_TRIPLE_POINT(S, X, Y, Z) \
{ \
    wxVector<double> pt; \
    pt.push_back(X); \
    pt.push_back(Y); \
    pt.push_back(Z); \
    S->AddPoint(new NaryDataPoint(pt)); \
}

/**
 * Bubble demo with one xyz serie.
 */
class BubbleDemo1 : public ChartDemo
{
public:
    BubbleDemo1()
    : ChartDemo(wxT("Bubble Demo 1 - Simple"))
    {
    }

    virtual Chart *Create()
    {
        // XYZ data for first series.
        DataSeries* series1 = new DataSeries("Series 1");
     
        SERIES_ADD_TRIPLE_POINT(series1, 10, 20, 10);
        SERIES_ADD_TRIPLE_POINT(series1, 13, 16, 40);
        SERIES_ADD_TRIPLE_POINT(series1, 15, 26, 30);
        SERIES_ADD_TRIPLE_POINT(series1, 7, 30, 11);
        SERIES_ADD_TRIPLE_POINT(series1, 25, 14, 15);
        SERIES_ADD_TRIPLE_POINT(series1, 15, 34, 35);
        SERIES_ADD_TRIPLE_POINT(series1, 25, 4, 20);
   
        // XYZ data for first series.
        DataSeries* series2 = new DataSeries("Series 2");

        SERIES_ADD_TRIPLE_POINT(series2, 13, 18, 40);
        SERIES_ADD_TRIPLE_POINT(series2, 53, 36, 20);
        SERIES_ADD_TRIPLE_POINT(series2, 25, 23, 10);
        SERIES_ADD_TRIPLE_POINT(series2, 76, 40, 41);
        SERIES_ADD_TRIPLE_POINT(series2, 30, 15, 25);
        SERIES_ADD_TRIPLE_POINT(series2, 45, 24, 45);
        SERIES_ADD_TRIPLE_POINT(series2, 15, 4, 10);
   
        // Create an n-ary dataset.
        NaryDataSet* dataset = new NaryDataSet("Bubble Demo 1");

        // Add the two series to the dataset.
        dataset->AddSeries(series1);
        dataset->AddSeries(series2);

        // Create a xyz renderer with minimal and maximal radius values.
        dataset->SetRenderer(new XYZRenderer(5, 15));

        // Create a plot.
        BubblePlot *plot = new BubblePlot();

        // Add the dataset to the plot.
        plot->AddDataset(dataset);

        // create left number axis
        NumberAxis *leftAxis = new NumberAxis(AXIS_LEFT);
        leftAxis->SetMargins(15, 15);

        // create bottom number axis
        NumberAxis *bottomAxis = new NumberAxis(AXIS_BOTTOM);
        bottomAxis->SetMargins(15, 15);

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

ChartDemo *bubbleDemos[] = {
        new BubbleDemo1(),
};
int bubbleDemosCount = WXSIZEOF(bubbleDemos);
