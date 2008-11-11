
/////////////////////////////////////////////////////////////////////////////
// Name:	multiplot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef MULTIPLOT_H_
#define MULTIPLOT_H_

#include <wx/array.h>
#include <wx/plot.h>

class MultiPlot : public Plot, public PlotObserver
{
public:
	MultiPlot(int rows, int cols, wxCoord horizGap, wxCoord vertGap);
	virtual ~MultiPlot();

	void AddPlot(Plot *subPlot)
	{
		m_subPlots.Add(subPlot);

		subPlot->AddObserver(this);
		FirePlotNeedRedraw();
	}

	//
	// PlotObserver
	//
	virtual void PlotNeedRedraw(Plot *_plot);

protected:
	virtual bool HasData();

	virtual void DrawData(wxDC &dc, wxRect rc);

private:
	Array<Plot, 1> m_subPlots;

	int m_rows;
	int m_cols;
	wxCoord m_horizGap;
	wxCoord m_vertGap;
};

#endif /*MULTIPLOT_H_*/
