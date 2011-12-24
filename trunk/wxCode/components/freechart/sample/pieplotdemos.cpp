/////////////////////////////////////////////////////////////////////////////
// Name:	pieplotdemos.cpp
// Purpose:     Pie plot demos
// Author:	Grgory Soutad
// Created:	2010/05/24
// Copyright:	(c) 2010 Grgory Soutad
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/pie/pieplot.h>
#include <wx/category/categorysimpledataset.h>

class PieplotDemo1 : public ChartDemo
{
public:
	PieplotDemo1()
	: ChartDemo(wxT("Pieplot Demo 1"))
	{
	}

	virtual Chart *Create()
	{
	  // serie pieplot data
	  double data[] = {1.0, 2.0, 3.0} ;
	  wxString categories[] = {_("cat 1"), _("cat 2"), _("cat 3")};
	  wxColour colours[] = {wxColour(0x99, 0xCC, 0xFF), wxColour(0xFF, 0xFF, 0x99), wxColour(0x3D, 0xEB, 0x3D)} ;

	  ColorScheme* colorScheme = new ColorScheme(colours, WXSIZEOF(colours));

	  // first step: create plot
	  PiePlot *plot = new PiePlot();

	  // create dataset
	  CategorySimpleDataset* dataset = new CategorySimpleDataset(categories, WXSIZEOF(categories));

	  // and add serie to it
	  dataset->AddSerie(_("Serie 1"), data, WXSIZEOF(data));

	  // create category renderer for legend drawing
	  dataset->SetRenderer(new CategoryRenderer(*colorScheme));

	  // set color scheme
	  plot->SetColorScheme(colorScheme);

	  plot->SetDataset(dataset);

	  // set legend to plot
	  plot->SetLegend(new Legend(wxCENTER, wxRIGHT));

	  // and finally create chart
	  return new Chart(plot, GetName());
	}
};

ChartDemo *pieplotDemos[] = {
	new PieplotDemo1()
};
int pieplotDemosCount = WXSIZEOF(pieplotDemos);
