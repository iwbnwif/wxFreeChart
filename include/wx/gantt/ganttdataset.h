/////////////////////////////////////////////////////////////////////////////
// Name:	ganttdataset.h
// Purpose: gantt dataset declaration
// Author:	Moskvichev Andrey V.
// Created:	2009/03/23
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2009/03/23 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef GANTTDATASET_H_
#define GANTTDATASET_H_

//#include <wx/dataset.h>
#include <wx/category/categorydataset.h>

class GanttRenderer;

class WXDLLEXPORT GanttDataset : public CategoryDataset
{
	DECLARE_CLASS(GanttDataset)
public:
	GanttDataset();
	virtual ~GanttDataset();

	virtual int GetCount() = 0;

	//virtual double GetValue(int index, int serie);

	virtual time_t GetStart(int serie, int index) = 0;

	virtual time_t GetEnd(int serie, int index) = 0;

	virtual int GetCount(int serie);

	GanttRenderer *GetRenderer()
	{
		return (GanttRenderer *) m_renderer;
	}
};

#endif /* GANTTDATASET_H_ */
