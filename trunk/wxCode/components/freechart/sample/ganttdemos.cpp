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
#include <wx/gantt/ganttdataset.h>

struct Task
{
	time_t start;
	time_t end;
};

/**
 * Gantt demo dataset.
 */
class GanttDemoDataset : public GanttDataset
{
public:
	GanttDemoDataset(int dateCount, const wxChar **names, int nameCount, Task *tasks, int taskCount)
	: GanttDataset(dateCount)
	{
		m_names.Alloc(nameCount);
		for (int n = 0; n < nameCount; n++) {
			m_names.Add(wxString(names[n]));
		}

		m_tasks = new Task[taskCount];
		for (int n = 0; n < taskCount; n++) {
			m_tasks[n].start = tasks[n].start;
			m_tasks[n].end = tasks[n].end;
		}
	}

	virtual ~GanttDemoDataset()
	{
		wxDELETEA(m_tasks);
	}

	virtual wxString GetName(int index)
	{
		return m_names[index];
	}

	virtual double GetValue(int WXUNUSED(index), int WXUNUSED(serie))
	{
		return 0; // dummy
	}

	virtual int GetSerieCount()
	{
		return 1;
	}

	virtual wxString GetSerieName(int serie)
	{
		return wxEmptyString;
	}

	virtual int GetCount()
	{
		return m_names.Count();
	}

	virtual time_t GetStart(int index, int WXUNUSED(serie))
	{
		return m_tasks[index].start;
	}

	virtual time_t GetEnd(int index, int WXUNUSED(serie))
	{
		return m_tasks[index].end;
	}

private:
	wxArrayString m_names;
	Task *m_tasks;
	int m_taskCount;
};


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

		Task tasks[] = {
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		};

		// task names, in this case - option names
		const wxChar *names[] = {
			wxT("March"),
			wxT("April"),
			wxT("May"),
			wxT("June"),
		};

		// parse dates from string and set to tasks start/end
		wxDateTime dt;
		for (size_t n = 0; n < WXSIZEOF(tasks); n++) {
			dt.ParseFormat(dates[n][0], wxT("%Y-%m-%d"));
			tasks[n].start = dt.GetTicks();

			dt.ParseFormat(dates[n][1], wxT("%Y-%m-%d"));
			tasks[n].end = dt.GetTicks();
		}

		// first step: create plot
		GanttPlot *plot = new GanttPlot();

		GanttDemoDataset *dataset = new GanttDemoDataset(4/*date count*/, names, WXSIZEOF(names), tasks, WXSIZEOF(tasks));

		GanttRenderer *renderer = new GanttRenderer(10);
		renderer->SetSerieDraw(0, new GradientAreaDraw(*wxBLACK_PEN, wxColour(50, 0, 0), wxColour(255, 0, 0)));

		dataset->SetRenderer(renderer);

		plot->AddDataset(dataset);

		// add left number (for names) and top date axes
		CategoryAxis *leftAxis = new CategoryAxis(AXIS_LEFT);
		leftAxis->SetMargins(10, 10);

		DateAxis *bottomAxis = new DateAxis(AXIS_TOP);
		bottomAxis->SetDateFormat(wxT("%d-%m-%y"));
		bottomAxis->SetMargins(25, 25);

		plot->AddAxis(leftAxis);
		plot->AddAxis(bottomAxis);

		CategoryAxis *rightAxis = new CategoryAxis(AXIS_RIGHT);
		rightAxis->SetMargins(10, 10);
		plot->AddAxis(rightAxis);

		// link axes and dataset
		plot->LinkDataVerticalAxis(0, 0);
		plot->LinkDataHorizontalAxis(0, 0);

		plot->LinkDataVerticalAxis(0, 1);

		// and finally create chart
		Chart *chart = new Chart(plot, GetName());
		return chart;
	}
};

ChartDemo *ganttDemos[] = {
		new GanttDemo1(),
};
int ganttDemosCount = WXSIZEOF(ganttDemos);
