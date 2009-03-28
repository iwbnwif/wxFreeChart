/////////////////////////////////////////////////////////////////////////////
// Name:	ganttplot.cpp
// Purpose: gantt plot implementation
// Author:	Moskvichev Andrey V.
// Created:	2009/03/23
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2009/03/23 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/gantt/ganttplot.h>
#include <wx/gantt/ganttdataset.h>
#include <wx/gantt/ganttrenderer.h>

#include <wx/axis/numberaxis.h>
#include <wx/axis/categoryaxis.h>

GanttPlot::GanttPlot()
{
	// TODO Auto-generated constructor stub

}

GanttPlot::~GanttPlot()
{
	// TODO Auto-generated destructor stub
}

bool GanttPlot::AcceptAxis(Axis *axis)
{
	return (wxDynamicCast(axis, NumberAxis) != NULL && !axis->IsVertical()) ||
			(wxDynamicCast(axis, CategoryAxis) != NULL && axis->IsVertical());
}

bool GanttPlot::AcceptDataset(Dataset *dataset)
{
	return (wxDynamicCast(dataset, GanttDataset) != NULL);
}

void GanttPlot::DrawDatasets(wxDC &dc, wxRect rc)
{
	for (int nData = 0; nData < GetDatasetCount(); nData++) {
		GanttDataset *dataset = (GanttDataset *) GetDataset(nData);
		GanttRenderer *renderer = dataset->GetRenderer();
		wxCHECK_RET(renderer != NULL, wxT("no renderer for data"));

		Axis *vertAxis = GetDatasetVerticalAxis(dataset);
		Axis *horizAxis = GetDatasetHorizontalAxis(dataset);

		wxCHECK_RET(vertAxis != NULL, wxT("no axis for data"));
		wxCHECK_RET(horizAxis != NULL, wxT("no axis for data"));

		renderer->Draw(dc, rc, horizAxis, vertAxis, dataset);
	}
}
