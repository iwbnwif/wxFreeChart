/////////////////////////////////////////////////////////////////////////////
// Name:	chartpanel.h
// Purpose: wxChartPanel declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
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

	/**
	 * Turn antialiasing on/off.
	 * Has effect only when wx wxUSE_GRAPHICS_CONTEXT is set in wxWidgets build.
	 *
	 * @param antialias true to turn on antialiasing.
	 */
	void SetAntialias(bool antialias);

	bool GetAntialias()
	{
		return m_antialias;
	}

	/**
	 * Returns back buffer copy as wxBitmap.
	 * Can be used to save chart image to file.
	 * @return back buffer copy as wxBitmap
	 */
	wxBitmap CopyBackbuffer();

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

	bool m_antialias;

	DECLARE_EVENT_TABLE()
};

#endif /*CHARTPANEL_H_*/
