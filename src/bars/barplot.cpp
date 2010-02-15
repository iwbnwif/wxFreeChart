/////////////////////////////////////////////////////////////////////////////
// Name:	barplot.cpp
// Purpose: bar plot implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2010 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/bars/barplot.h>

#include <wx/axis/categoryaxis.h>
#include <wx/axis/numberaxis.h>
#include <wx/axis/dateaxis.h>

BarPlot::BarPlot()
{
}

BarPlot::~BarPlot()
{
}

bool BarPlot::AcceptAxis(Axis *axis)
{
	return (wxDynamicCast(axis, NumberAxis) != NULL) ||
			(wxDynamicCast(axis, CategoryAxis) != NULL);
}

bool BarPlot::AcceptDataset(Dataset *dataset)
{
	return (wxDynamicCast(dataset, CategoryDataset) != NULL);
}

void BarPlot::DrawDatasets(wxDC &dc, wxRect rc)
{
	for (size_t nData = 0; nData < GetDatasetCount(); nData++) {
		CategoryDataset *dataset = (CategoryDataset *) GetDataset(nData);
		BarRenderer *renderer = dataset->GetRenderer();
		wxCHECK_RET(renderer != NULL, wxT("no renderer for data"));

		Axis *vertAxis = GetDatasetVerticalAxis(dataset);
		Axis *horizAxis = GetDatasetHorizontalAxis(dataset);

		wxCHECK_RET(vertAxis != NULL, wxT("no axis for data"));
		wxCHECK_RET(horizAxis != NULL, wxT("no axis for data"));

		bool verticalBars;
		if (wxDynamicCast(horizAxis, CategoryAxis) != NULL ||
				wxDynamicCast(horizAxis, DateAxis) != NULL) {
			verticalBars = true;
		}
		else if (wxDynamicCast(vertAxis, CategoryAxis) != NULL ||
				wxDynamicCast(vertAxis, DateAxis) != NULL) {
			verticalBars = false;
		}
		else {
			// wrong plot configuration, TODO be handled not here
			return ;
		}

		renderer->Draw(dc, rc, horizAxis, vertAxis, verticalBars, dataset);
	}
}
