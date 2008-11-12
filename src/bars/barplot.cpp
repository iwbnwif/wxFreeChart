
/////////////////////////////////////////////////////////////////////////////
// Name:	barplot.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
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
	return (dynamic_cast<NumberAxis *>(axis) != NULL) ||
			(dynamic_cast<CategoryAxis *>(axis) != NULL) ||
			(dynamic_cast<DateAxis *>(axis) != NULL);
}

bool BarPlot::AcceptDataset(Dataset *dataset)
{
	return (dynamic_cast<CategoryDataset *>(dataset) != NULL ||
			dynamic_cast<DateTimeDataset *>(dataset));
}

void BarPlot::DrawDatasets(wxDC &dc, wxRect rc)
{
	for (int nData = 0; nData < GetDatasetCount(); nData++) {
		CategoryDataset *dataset = (CategoryDataset *) GetDataset(nData);
		XYRenderer *renderer = dataset->GetRenderer();
		wxCHECK_RET(renderer != NULL, wxT("no renderer for data"));

		Axis *vertAxis = GetDatasetVerticalAxis(dataset);
		Axis *horizAxis = GetDatasetHorizontalAxis(dataset);

		wxCHECK_RET(vertAxis != NULL, wxT("no axis for data"));
		wxCHECK_RET(horizAxis != NULL, wxT("no axis for data"));

		bool verticalBars;
		if (dynamic_cast<CategoryAxis *>(horizAxis) != NULL ||
				dynamic_cast<DateAxis *>(horizAxis) != NULL) {
			verticalBars = true;
		}
		else if (dynamic_cast<CategoryAxis *>(vertAxis) != NULL ||
				dynamic_cast<DateAxis *>(vertAxis) != NULL) {
			verticalBars = false;
		}
		else {
			// wrong plot configuration, TODO be handled not here
			return ;
		}

		renderer->Draw(dc, rc, horizAxis, vertAxis, dataset);
	}
}

