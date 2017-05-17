/////////////////////////////////////////////////////////////////////////////
// Name:    pieplotdemos.cpp
// Purpose:     Pie plot demos
// Author:    Grgory Soutad
// Created:    2010/05/24
// Copyright:    (c) 2010 Grgory Soutad
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/pie/pieplot.h>

class PieplotDemo1 : public ChartDemo
{
public:
    PieplotDemo1()
    : ChartDemo(wxT("Pie Demo 1"))
    {
    }

    virtual Chart *Create()
    {
        // Create the category dataset and add the categories.
        // Each category represents a segment in the pie plot.
        UniDataSet* dataset = new UniDataSet("Pie Demo 1");
        dataset->AddCategory("Cat 1");
        dataset->AddCategory("Cat 2");
        dataset->AddCategory("Cat 3");

        // Create the series data.
        DataSeries* series = new DataSeries("Series 1");
        series->AddPoint(new UniDataPoint(1.0));
        series->AddPoint(new UniDataPoint(2.0));
        series->AddPoint(new UniDataPoint(3.0));
        
        // Add the series to the data set.
        dataset->AddSeries(series);
        
        // Create a colour scheme.
        // TODO: This should be changed to a vector.
        wxColour colours[] = {wxColour(0x99, 0xCC, 0xFF), wxColour(0xFF, 0xFF, 0x99), wxColour(0x3D, 0xEB, 0x3D)} ;
        ColorScheme* colorScheme = new ColorScheme(colours, WXSIZEOF(colours));

        // Create a category renderer for legend drawing.
        dataset->SetRenderer(new CategoryRenderer(*colorScheme));

        // Create the plot and add the dataset.
        // Note: Currently pie plots can only have a single dataset.
        PiePlot *plot = new PiePlot();
        plot->SetDataset(dataset);

        // Set the color scheme.
        plot->SetColorScheme(colorScheme);

        // Set the plot's legend.
        plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

        // Create the chart.
        return new Chart(plot, GetName());
    }
};

ChartDemo *pieplotDemos[] = {
    new PieplotDemo1()
};
int pieplotDemosCount = WXSIZEOF(pieplotDemos);
