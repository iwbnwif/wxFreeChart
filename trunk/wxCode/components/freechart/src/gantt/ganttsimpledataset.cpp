/////////////////////////////////////////////////////////////////////////////
// Name:	ganttsimpledataset.cpp
// Purpose: gantt simple dataset implementation
// Author:	Moskvichev Andrey V.
// Created:	2009/11/25
// Copyright:	(c) 2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/gantt/ganttsimpledataset.h>

#include "wx/arrimpl.cpp"

WX_DEFINE_OBJARRAY(GanttSerieArray);

GanttSerie::GanttSerie(TaskTime *taskTimes, int taskTimesCount, const wxString &name)
{
	m_taskTimes = new TaskTime[taskTimesCount];
	for (int n = 0; n < taskTimesCount; n++) {
		m_taskTimes[n].start = taskTimes[n].start;
		m_taskTimes[n].end = taskTimes[n].end;
	}

	m_taskTimesCount = taskTimesCount;

	m_name = name;
}

GanttSerie::~GanttSerie()
{
	wxDELETEA(m_taskTimes);
}

time_t GanttSerie::GetStart(int index)
{
	wxCHECK(index < m_taskTimesCount, 0);
	return m_taskTimes[index].start;
}

time_t GanttSerie::GetEnd(int index)
{
	wxCHECK(index < m_taskTimesCount, 0);
	return m_taskTimes[index].end;
}

const wxString &GanttSerie::GetName()
{
	return m_name;
}

//
// GanttSimpleDataset
//

GanttSimpleDataset::GanttSimpleDataset(int dateCount, const wxChar **taskNames, int taskNamesCount)
: GanttDataset(dateCount)
{
	m_taskNames.Alloc(taskNamesCount);
	for (int n = 0; n < taskNamesCount; n++) {
		m_taskNames.Add(wxString(taskNames[n]));
	}
}

GanttSimpleDataset::~GanttSimpleDataset()
{
	for (size_t n = 0; n < m_series.Count(); n++) {
		wxDELETE(m_series[n]);
	}
}

void GanttSimpleDataset::AddSerie(GanttSerie *serie)
{
	m_series.Add(serie);
	DatasetChanged();
}

wxString GanttSimpleDataset::GetName(int index)
{
	return m_taskNames[index];
}

double GanttSimpleDataset::GetValue(int WXUNUSED(index), int WXUNUSED(serie))
{
	return 0; // dummy
}

int GanttSimpleDataset::GetSerieCount()
{
	return m_series.Count();
}

wxString GanttSimpleDataset::GetSerieName(int serie)
{
	wxCHECK(serie < (int) m_series.Count(), wxEmptyString);
	return m_series[serie]->GetName();
}

int GanttSimpleDataset::GetCount()
{
	return m_taskNames.Count();
}

time_t GanttSimpleDataset::GetStart(int index, int serie)
{
	wxCHECK(serie < (int) m_series.Count(), 0);
	return m_series[serie]->GetStart(index);
}

time_t GanttSimpleDataset::GetEnd(int index, int serie)
{
	wxCHECK(serie < (int) m_series.Count(), 0);
	return m_series[serie]->GetEnd(index);
}
