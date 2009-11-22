/////////////////////////////////////////////////////////////////////////////
// Name:	ganttdataset.h
// Purpose: gantt dataset declaration
// Author:	Moskvichev Andrey V.
// Created:	2009/03/23
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2009/03/23 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef GANTTDATASET_H_
#define GANTTDATASET_H_

//#include <wx/dataset.h>
#include <wx/category/categorydataset.h>

class GanttRenderer;
class GanttDataset;

/**
 * Helper used to access gantt dataset as datetime dataset.
 */
class WXDLLIMPEXP_FREECHART GanttDatasetDateHelper : public DateTimeDataset
{
public:
	GanttDatasetDateHelper(GanttDataset *ganttDataset);
	virtual ~GanttDatasetDateHelper();

	virtual time_t GetDate(int index);

	virtual int GetCount();

private:
	GanttDataset *m_ganttDataset;
};

/**
 * Gantt chart dataset base class.
 */
class WXDLLIMPEXP_FREECHART GanttDataset : public CategoryDataset
{
	DECLARE_CLASS(GanttDataset)
public:
	GanttDataset(int dateCount);
	virtual ~GanttDataset();

	virtual DateTimeDataset *AsDateTimeDataset();

	/**
	 * Returns task count.
	 * @return task count
	 */
	virtual int GetCount() = 0;

	virtual time_t GetStart(int index, int serie) = 0;

	virtual time_t GetEnd(int index, int serie) = 0;

	virtual int GetCount(int serie);

	virtual time_t GetMinStart();

	virtual time_t GetMaxEnd();

	time_t GetDateInterval();

	int GetDateCount();

	GanttRenderer *GetRenderer()
	{
		return (GanttRenderer *) m_renderer;
	}

private:
	GanttDatasetDateHelper m_dateHelper;

	int m_dateCount;
};

#endif /* GANTTDATASET_H_ */
