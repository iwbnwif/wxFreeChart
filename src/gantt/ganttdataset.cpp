/////////////////////////////////////////////////////////////////////////////
// Name:	ganttdataset.cpp
// Purpose: gantt dataset implementation
// Author:	Moskvichev Andrey V.
// Created:	2009/03/23
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2009/03/23 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/gantt/ganttdataset.h>

IMPLEMENT_CLASS(GanttDataset, CategoryDataset)

GanttDataset::GanttDataset()
{
}

GanttDataset::~GanttDataset()
{
}

int GanttDataset::GetCount(int WXUNUSED(serie))
{
	// Gannt Dataset has equal number of elements in all series.
	return GetCount();
}
