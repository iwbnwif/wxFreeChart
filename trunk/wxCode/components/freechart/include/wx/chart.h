
/////////////////////////////////////////////////////////////////////////////
// Name:	chart.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CHART_H_
#define CHART_H_

#include <wx/wxfreechartdefs.h>

#include <wx/refobject.h>
#include <wx/observable.h>
#include <wx/plot.h>

#include <wx/areabackground.h>

class Chart;

/**
 * Interface for receiving chart events.
 */
class ChartObserver
{
public:
	ChartObserver();

	virtual ~ChartObserver();

	/**
	 * Called when some of chart or chart component properties
	 * has been changed.
	 * @param chart chart that has been changed
	 */
	virtual void ChartChanged(Chart *chart) = 0;
};

/**
 * Chart. Contains plot, title and chart attributes.
 */
class Chart : public RefObject, public Observable<ChartObserver>, public PlotObserver
{
public:
	/**
	 * Constructs new chart.
	 * @param _plot plot
	 * @param _title chart title (empty string - no title)
	 */
	Chart(Plot *plot, const wxString &title = wxEmptyString);
	virtual ~Chart();

	/**
	 * Draws chart.
	 * @param dc device context
	 * @param rc rectangle where to draw chart
	 */
	void Draw(wxDC &dc, wxRect &rc);

	/**
	 * Sets chart background.
	 * @param _background chart background
	 */
	void SetBackground(AreaBackground *background)
	{
		SAFE_REPLACE(m_background, background);
		FireChartChanged();
	}

	/**
	 * Sets chart title.
	 * @param _title chart title
	 */
	void SetTitle(wxString title)
	{
		m_title = title;
		FireChartChanged();
	}

	/**
	 * Sets font for chart title.
	 * @param _font font for chart title
	 */
	void SetTitleFont(wxFont font)
	{
		m_titleFont = font;
		FireChartChanged();
	}

	//
	// PlotObserver
	//
	virtual void PlotNeedRedraw(Plot *_plot);

private:
	Plot *m_plot;
	AreaBackground *m_background;
	wxString m_title;
	wxFont m_titleFont;

	FIRE_WITH_THIS(ChartChanged);
};

#endif /*CHART_H_*/
