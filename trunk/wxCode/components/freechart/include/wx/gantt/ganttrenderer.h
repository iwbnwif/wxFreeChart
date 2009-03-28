/////////////////////////////////////////////////////////////////////////////
// Name:	ganttrenderer.h
// Purpose: gantt renderer declaration
// Author:	Moskvichev Andrey V.
// Created:	2009/03/23
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2009/03/23 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef GANTTRENDERER_H_
#define GANTTRENDERER_H_

#include <wx/axis/axis.h>
#include <wx/gantt/ganttdataset.h>

class WXDLLEXPORT GanttRenderer : public Renderer
{
	DECLARE_CLASS(GanttRenderer)
public:
	/**
	 * Constructs new gantt renderer.
	 * @param barWidth bar width
	 * @param serieGap distance between series
	 */
	GanttRenderer(int barWidth = 5, int serieGap = 2);
	virtual ~GanttRenderer();

	void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, GanttDataset *dataset);

private:
	int m_barWidth;
	int m_serieGap;
};

#endif /* GANTTRENDERER_H_ */
