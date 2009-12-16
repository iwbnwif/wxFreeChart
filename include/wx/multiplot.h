/////////////////////////////////////////////////////////////////////////////
// Name:	multiplot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef MULTIPLOT_H_
#define MULTIPLOT_H_

#include <wx/dynarray.h>
#include <wx/plot.h>

WX_DECLARE_EXPORTED_OBJARRAY(Plot *, PlotArray);

class WXDLLIMPEXP_FREECHART MultiPlot : public Plot, public PlotObserver
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
	virtual void PlotNeedRedraw(Plot *plot);

protected:
	virtual bool HasData();

	virtual void DrawData(wxDC &dc, wxRect rc);

private:
	PlotArray m_subPlots;

	int m_rows;
	int m_cols;
	wxCoord m_horizGap;
	wxCoord m_vertGap;
};

#endif /*MULTIPLOT_H_*/
