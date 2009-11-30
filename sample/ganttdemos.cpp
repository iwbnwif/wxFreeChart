/////////////////////////////////////////////////////////////////////////////
// Name:	ganttdemos.cpp
// Purpose: This file contains source code, that demonstrates how to
//          create gantt charts.
// Author:	Moskvichev Andrey V.
// Created:	2009/04/03
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/04/03 16:42:58 moskvichev Exp $
// Copyright:	(c) 2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

#include <wx/gantt/ganttplot.h>
#include <wx/gantt/ganttrenderer.h>

#include <wx/gantt/ganttsimpledataset.h>

/**
 * Simple gannt demo, showing options lifetime.
 */
class GanttDemo1 : public ChartDemo
{
public:
	GanttDemo1()
	: ChartDemo(wxT("Gannt Demo 1 - options lifetime"))
	{
	}

	virtual Chart *Create()
	{
		// start/end dates for tasks in string form.
		const wxChar *dates[][2] = {
			{ wxT("2009-01-01"), wxT("2009-03-14") },
			{ wxT("2009-03-01"), wxT("2009-04-14") },
			{ wxT("2009-04-01"), wxT("2009-05-14") },
			{ wxT("2009-02-01"), wxT("2009-06-14") },
		};

		GanttSerie::TaskTime taskTimes[] = {
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		};

		// task names, in this case - option names
		const wxChar *taskNames[] = {
			wxT("March"),
			wxT("April"),
			wxT("May"),
			wxT("June"),
		};

		// parse dates from string and set to tasks start/end
		wxDateTime dt;
		for (size_t n = 0; n < WXSIZEOF(taskTimes); n++) {
			dt.ParseFormat(dates[n][0], wxT("%Y-%m-%d"));
			taskTimes[n].start = dt.GetTicks();

			dt.ParseFormat(dates[n][1], wxT("%Y-%m-%d"));
			taskTimes[n].end = dt.GetTicks();
		}

		// first step: create plot
		GanttPlot *plot = new GanttPlot();

		// create gantt dataset
		GanttSimpleDataset *dataset = new GanttSimpleDataset(4/*date count*/, taskNames, WXSIZEOF(taskNames));

		// add serie to it
		dataset->AddSerie(new GanttSerie(taskTimes, WXSIZEOF(taskTimes), wxT("")));

		// create gantt renderer
		GanttRenderer *renderer = new GanttRenderer(10);

		// set renderer to dataset
		dataset->SetRenderer(renderer);

		// add dataset to plot
		plot->AddDataset(dataset);

		// create left axis
		CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
		leftAxis->SetMargins(10, 10);

		// create bottom date axis
		DateAxis *bottomAxis = new DateAxis(AXIS_TOP);
		bottomAxis->SetDateFormat(wxT("%d-%m-%y"));
		bottomAxis->SetMargins(25, 25);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());
		return chart;
	}
};

/**
 * gannt demo, showing tasks scheduled and actual time.
 */
class GanttDemo2 : public ChartDemo
{
public:
	GanttDemo2()
	: ChartDemo(wxT("Gannt Demo 2 - scheduled vs actual"))
	{
	}

	virtual Chart *Create()
	{
		// start/end dates for scheduled task times in string form
		const wxChar *datesScheduled[][2] = {
			{ wxT("2009-01-01"), wxT("2009-03-14") },
			{ wxT("2009-03-01"), wxT("2009-04-14") },
			{ wxT("2009-04-01"), wxT("2009-06-14") },
			{ wxT("2009-06-16"), wxT("2009-07-20") },
		};

		// start/end dates for actual task times in string form
		const wxChar *datesActual[][2] = {
			{ wxT("2009-01-08"), wxT("2009-03-25") },
			{ wxT("2009-04-01"), wxT("2009-05-02") },
			{ wxT("2009-05-04"), wxT("2009-07-14") },
			{ wxT("2009-07-20"), wxT("2009-09-01") },
		};

		GanttSerie::TaskTime taskTimesScheduled[] = {
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		};

		GanttSerie::TaskTime taskTimesActual[] = {
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		};

		// task names
		const wxChar *taskNames[] = {
			wxT("Requirements analysis"),
			wxT("Design phase"),
			wxT("Implementation"),
			wxT("Testing"),
		};

		// parse dates from string and set to tasks start/end
		wxDateTime dt;
		for (size_t n = 0; n < WXSIZEOF(taskTimesScheduled); n++) {
			dt.ParseFormat(datesScheduled[n][0], wxT("%Y-%m-%d"));
			taskTimesScheduled[n].start = dt.GetTicks();

			dt.ParseFormat(datesScheduled[n][1], wxT("%Y-%m-%d"));
			taskTimesScheduled[n].end = dt.GetTicks();
		}

		// the same for actual task times
		for (size_t n = 0; n < WXSIZEOF(taskTimesActual); n++) {
			dt.ParseFormat(datesActual[n][0], wxT("%Y-%m-%d"));
			taskTimesActual[n].start = dt.GetTicks();

			dt.ParseFormat(datesActual[n][1], wxT("%Y-%m-%d"));
			taskTimesActual[n].end = dt.GetTicks();
		}

		// first step: create plot
		GanttPlot *plot = new GanttPlot();

		// create gantt dataset
		GanttSimpleDataset *dataset = new GanttSimpleDataset(4/*date count*/, taskNames, WXSIZEOF(taskNames));

		// add scheduled serie to it
		dataset->AddSerie(new GanttSerie(taskTimesScheduled, WXSIZEOF(taskTimesScheduled), wxT("Scheduled")));

		// add actual serie to it
		dataset->AddSerie(new GanttSerie(taskTimesActual, WXSIZEOF(taskTimesActual), wxT("Actual")));

		// create gantt renderer
		GanttRenderer *renderer = new GanttRenderer(10);

		// set renderer to dataset
		dataset->SetRenderer(renderer);

		// add dataset to plot
		plot->AddDataset(dataset);

		// create left axis
		CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
		leftAxis->SetMargins(20, 20);

		// create bottom date axis
		DateAxis *bottomAxis = new DateAxis(AXIS_TOP);
		bottomAxis->SetDateFormat(wxT("%d-%m-%y"));
		bottomAxis->SetMargins(25, 25);

		// add axes to plot
		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		// set legend to plot
		plot->SetLegend(new Legend(wxBOTTOM, wxCENTER));

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());
		return chart;
	}
};

ChartDemo *ganttDemos[] = {
		new GanttDemo1(),
		new GanttDemo2(),
};
int ganttDemosCount = WXSIZEOF(ganttDemos);
