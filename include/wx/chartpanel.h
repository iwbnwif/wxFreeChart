
/////////////////////////////////////////////////////////////////////////////
// Name:	chartpanel.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
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
class wxChartPanel : public wxScrolledWindow, public ChartObserver
{
public:
	wxChartPanel(wxWindow *parent, Chart *_chart = NULL,
		const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);
	virtual ~wxChartPanel();

	/**
	 * Sets chart.
	 * @param chart new chart
	 */
	void SetChart(Chart *_chart);

	Chart *GetChart()
	{
		return chart;
	}

	//
	// ChartObserver
	//
	virtual void ChartChanged(Chart *_chart);

private:
	void ResizeBackBitmap(wxSize size);
	void RedrawBackBitmap();

	void OnPaint(wxPaintEvent &ev);
	void OnSize(wxSizeEvent &ev);

	Chart *chart;

	wxBitmap backBitmap;

	DECLARE_EVENT_TABLE()
};

#endif /*CHARTPANEL_H_*/
