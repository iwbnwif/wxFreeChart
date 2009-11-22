/////////////////////////////////////////////////////////////////////////////
// Name:	chart.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CHART_H_
#define CHART_H_

#include <wx/wxfreechartdefs.h>

#include <wx/refobject.h>
#include <wx/observable.h>
#include <wx/plot.h>

#include <wx/areadraw.h>

#include <wx/axis/axis.h>

class Chart;

/**
 * Interface for receiving chart events.
 */
class WXDLLIMPEXP_FREECHART ChartObserver
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

	/**
	 * Called when some of chart scrolled axes changed its bounds.
	 * @param chart chart
	 */
	virtual void ChartScrollsChanged(Chart *chart) = 0;
};

/**
 * Chart. Contains plot, title and chart attributes.
 */
class WXDLLIMPEXP_FREECHART Chart : public RefObject, public Observable<ChartObserver>, public PlotObserver, public AxisObserver
{
public:
	/**
	 * Constructs new chart.
	 * @param plot plot
	 * @param title chart title (empty string - no title)
	 */
	Chart(Plot *plot, const wxString &title = wxEmptyString);

	virtual ~Chart();

	Plot *GetPlot()
	{
		return m_plot;
	}

	/**
	 * Draws chart.
	 * @param dc device context
	 * @param rc rectangle where to draw chart
	 */
	void Draw(wxDC &dc, wxRect &rc);

	/**
	 * Sets chart background.
	 * @param background chart background
	 */
	void SetBackground(AreaDraw *background)
	{
		wxREPLACE(m_background, background);
		FireChartChanged();
	}

	/**
	 * Calcalate plot area rectangle.
	 * @param dc device context
	 * @param rc entire chart rectangle
	 * @return plot area rectangle
	 */
	wxRect CalcPlotRect(wxDC &dc, wxRect rc);

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
	 * Returns chart title.
	 * @return chart title string
	 */
	const wxString &GetTitle()
	{
		return m_title;
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

	void SetScrolledAxis(Axis *axis);

	Axis *GetHorizScrolledAxis();

	Axis *GetVertScrolledAxis();


	//
	// PlotObserver
	//
	virtual void PlotNeedRedraw(Plot *_plot);

	//
	// AxisObserver
	//
	virtual void AxisChanged(Axis *axis);

	virtual void BoundsChanged(Axis *axis);

private:
	Plot *m_plot;
	AreaDraw *m_background;
	wxString m_title;
	wxFont m_titleFont;

	Axis *m_horizScrolledAxis;
	Axis *m_vertScrolledAxis;

	FIRE_WITH_THIS(ChartChanged);
	FIRE_WITH_THIS(ChartScrollsChanged);
};

#endif /*CHART_H_*/
