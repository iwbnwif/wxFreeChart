
/////////////////////////////////////////////////////////////////////////////
// Name:	pieplot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
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
 */
class PiePlot : public Plot, public DatasetObserver
{
public:
	PiePlot();
	virtual ~PiePlot();

	void SetDataset(CategoryDataset *_dataset);

	void SetUsedSerie(int _serie)
	{
		serie = _serie;
		FirePlotNeedRedraw();
	}

	void SetColorScheme(ColorScheme *_cs);

	void Set3DView(bool _use3DView)
	{
		if (use3DView != _use3DView) {
			use3DView = _use3DView;
			FirePlotNeedRedraw();
		}
	}

	void SetEllipticAspect(float _ellipticAspect)
	{
		if (ellipticAspect != _ellipticAspect && _ellipticAspect > 0 && _ellipticAspect <= 1) {
			ellipticAspect = _ellipticAspect;
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

	bool use3DView;
	float ellipticAspect;

	wxFont labelsFont;
	wxPen outlinePen;

	CategoryDataset *dataset;

	ColorScheme colorScheme;

	int serie;
};

#endif /*PIEPLOT_H_*/
