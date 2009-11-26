/////////////////////////////////////////////////////////////////////////////
// Name:	ganttsimpledataset.h
// Purpose: gantt simple dataset declaration
// Author:	Moskvichev Andrey V.
// Created:	2009/11/25
// Copyright:	(c) 2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef GANTTSIMPLEDATASET_H_
#define GANTTSIMPLEDATASET_H_

#include <wx/gantt/ganttdataset.h>

#include <wx/dynarray.h>

class WXDLLIMPEXP_FREECHART GanttSerie
{
public:
	struct TaskTime
	{
		time_t start;
		time_t end;
	};

	GanttSerie(TaskTime *tasks, int taskCount, const wxString &name);
	virtual ~GanttSerie();

	time_t GetStart(int index);

	time_t GetEnd(int index);

	const wxString &GetName();

private:
	TaskTime *m_taskTimes;
	int m_taskTimesCount;

	wxString m_name;
};

WX_DECLARE_OBJARRAY(GanttSerie *, GanttSerieArray);

/**
 * Gantt simple dataset.
 */
class WXDLLIMPEXP_FREECHART GanttSimpleDataset : public GanttDataset
{
public:
	/**
	 * Construct new gantt demo dataset.
	 * @param dateCount
	 * @param taskNames names for tasks
	 * @param taskNamesCount count of names
	 */
	GanttSimpleDataset(int dateCount, const wxChar **taskNames, int taskNamesCount);
	virtual ~GanttSimpleDataset();

	/**
	 * Add new serie to dataset.
	 * @param serie new serie
	 */
	void AddSerie(GanttSerie *serie);

	virtual wxString GetName(int index);

	virtual double GetValue(int index, int serie);

	virtual int GetSerieCount();

	virtual wxString GetSerieName(int serie);

	virtual int GetCount();

	virtual time_t GetStart(int index, int serie);

	virtual time_t GetEnd(int index, int serie);

private:
	wxArrayString m_taskNames;
	GanttSerieArray m_series;
};

#endif /* GANTTSIMPLEDATASET_H_ */
