/////////////////////////////////////////////////////////////////////////////
// Name:	chartpanel.h
// Purpose: wxChartPanel declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CHARTPANEL_H_
#define CHARTPANEL_H_

#include <wx/wxfreechartdefs.h>
#include <wx/chart.h>

/**
 * ChartPanel is wxWidgets panel for displaying chart.
 *
 */
class WXDLLIMPEXP_FREECHART wxChartPanel : public wxScrolledWindow, public ChartObserver
{
public:
	wxChartPanel(wxWindow *parent, wxWindowID = wxID_ANY, Chart *chart = NULL,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
	virtual ~wxChartPanel();

	/**
	 * Sets chart.
	 * @param chart new chart
	 */
	void SetChart(Chart *chart);

	Chart *GetChart()
	{
		return m_chart;
	}

	//
	// ChartObserver
	//
	virtual void ChartChanged(Chart *chart);

	virtual void ChartScrollsChanged(Chart *chart);

private:
	void ResizeBackBitmap(wxSize size);
	void RedrawBackBitmap();
	void RecalcScrollbars();

	//
	// Event handlers
	//
	void OnPaint(wxPaintEvent &ev);
	void OnSize(wxSizeEvent &ev);
	void OnScrollWin(wxScrollWinEvent &ev);

	void ScrollAxis(Axis *axis, int d);

	Chart *m_chart;

	wxBitmap m_backBitmap;

	DECLARE_EVENT_TABLE()
};

#endif /*CHARTPANEL_H_*/
