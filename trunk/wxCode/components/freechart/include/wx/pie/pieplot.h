/////////////////////////////////////////////////////////////////////////////
// Name:	pieplot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef PIEPLOT_H_
#define PIEPLOT_H_

#include <wx/plot.h>
#include <wx/category/categorydataset.h>

#include <wx/colorscheme.h>

const int shift3D = 20;

/**
 * Pie plot.
 * TODO: initial quick and dirty, must be cleaned up or rewritten.
 */
class WXDLLIMPEXP_FREECHART PiePlot : public Plot, public DatasetObserver
{
public:
	PiePlot();
	virtual ~PiePlot();

	void SetDataset(CategoryDataset *dataset);

	void SetUsedSerie(int serie)
	{
		m_serie = serie;
		FirePlotNeedRedraw();
	}

	void SetColorScheme(ColorScheme *cs);

	void Set3DView(bool use3DView)
	{
		if (m_use3DView != use3DView) {
			m_use3DView = use3DView;
			FirePlotNeedRedraw();
		}
	}

	void SetEllipticAspect(float ellipticAspect)
	{
		if (m_ellipticAspect != ellipticAspect && ellipticAspect > 0 && ellipticAspect <= 1) {
			m_ellipticAspect = ellipticAspect;
			FirePlotNeedRedraw();
		}
	}

	//
	// DatasetObserver
	//
	virtual void DatasetChanged(Dataset *dataset);

protected:
	virtual bool HasData();

	virtual void DrawData(wxDC &dc, wxRect rc);

private:

	bool m_use3DView;
	float m_ellipticAspect;

	wxFont m_labelsFont;
	wxPen m_outlinePen;

	CategoryDataset *m_dataset;

	ColorScheme m_colorScheme;

	int m_serie;
};

#endif /*PIEPLOT_H_*/
