/////////////////////////////////////////////////////////////////////////////
// Name:	plot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef PLOT_H_
#define PLOT_H_

#include <wx/wxfreechartdefs.h>
#include <wx/observable.h>

#include <wx/areabackground.h>

class Plot;

/**
 * Interface that receives Plot events, such as need redraw condition.
 */
class WXDLLEXPORT PlotObserver
{
public:
	PlotObserver();

	virtual ~PlotObserver();

	/**
	 * Called when plot has been changed and need to be redrawn.
	 * @param _plot plot
	 */
	virtual void PlotNeedRedraw(Plot *_plot) = 0;
};

/**
 * Base class for all plots.
 *
 */
class WXDLLEXPORT Plot : public Observable<PlotObserver>
{
public:
	Plot();
	virtual ~Plot();

	/**
	 * Draws plot
	 * @param dc device context
	 * @param rc rectangle where to draw
	 */
	virtual void Draw(wxDC &dc, wxRect rc);

	/**
	 * Draws "no data" message.
	 * Can be overriden by derivative classes.
	 * @param dc device context
	 * @param rc rectangle where to draw
	 */
	virtual void DrawNoDataMessage(wxDC &dc, wxRect rc);

	/**
	 * Sets plot background.
	 * @param _background new background for plot
	 */
	void SetBackground(AreaBackground *background)
	{
		m_background = background;
		FirePlotNeedRedraw();
	}

protected:
	/**
	 * Checks whether plot has data.
	 * Must be overriden by derivative classes.
	 * @return true if plot has data, false overwise
	 */
	virtual bool HasData() = 0;

	/**
	 * Perform data rendering.
	 * Must be overriden by derivative classes.
	 * @param dc device context
	 * @param rc rectangle where to draw
	 */
	virtual void DrawData(wxDC &dc, wxRect rc) = 0;

	FIRE_WITH_THIS(PlotNeedRedraw);

private:
	wxFont m_textNoDataFont;
	wxString m_textNoData;

	AreaBackground *m_background;
};

#endif /*PLOT_H_*/
