
/////////////////////////////////////////////////////////////////////////////
// Name:	pieplot.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/pie/pieplot.h>
#include <wx/drawutils.h>
#include <wx/drawobject.h>

#include <math.h>

/*
 * TODO Initial quick and dirty. Must be rewritten.
 */

void Rotate(wxCoord &x, wxCoord &y, wxCoord xc, wxCoord yc, double rad, double angle)
{
	x = (wxCoord) (rad * cos(angle) + xc);
	y = (wxCoord) (-rad * sin(angle) + yc);
}

void EllipticEgde(wxCoord x, wxCoord y, wxCoord width, wxCoord height, double angle, wxCoord &outX, wxCoord &outY)
{
	double degs = angle * M_PI / 180;

	double w = width;
	double h = height;

	outX = (wxCoord) (w * cos(degs) / 2 + x + w / 2);
	outY = (wxCoord) (-h * sin(degs) / 2 + y + h / 2);
}

PiePlot::PiePlot()
{
	dataset = NULL;

	use3DView = false;
	ellipticAspect = 1.0f;
	//colorScheme = defaultColorScheme;
	outlinePen = *wxBLACK_PEN;
	labelsFont = *wxSMALL_FONT;

	serie = 0; // default behaviour - use first serie
}

PiePlot::~PiePlot()
{
	SAFE_REMOVE_OBSERVER(this, dataset);
	SAFE_UNREF(dataset);
}

void PiePlot::SetDataset(CategoryDataset *_dataset)
{
	SAFE_REPLACE_OBSERVER(this, dataset, _dataset);
	SAFE_REPLACE_UNREF(dataset, _dataset);

	FirePlotNeedRedraw();
}

void PiePlot::SetColorScheme(ColorScheme *_colorScheme)
{
	colorScheme = *_colorScheme;
}

bool PiePlot::HasData()
{
	return dataset != NULL && dataset->GetSerieCount() >= serie;
}

void PiePlot::DatasetChanged(Dataset *dataset)
{
	FirePlotNeedRedraw();
}

void PiePlot::DrawData(wxDC &dc, wxRect rc)
{
	// TODO initial quick and dirty, need cleanup.
	//
	double sum = 0;

	for (int n = 0; n < dataset->GetCount(); n++) {
		sum += dataset->GetValue(n, serie);
	}


	int radHoriz = (int) (0.8 * MIN(rc.width, rc.height));
	int radVert  = (int) (radHoriz * ellipticAspect);

	wxCoord x0 = rc.x + (rc.width - radHoriz) / 2;
	wxCoord y0 = rc.y + (rc.height - radVert) / 2;

	if (use3DView) {
		dc.SetPen(outlinePen);
		dc.SetBrush(noBrush);
		dc.DrawEllipticArc(x0, y0 + shift3D, radHoriz, radVert, -180, 0);
		dc.DrawLine(x0, y0 + radVert / 2, x0, y0 + radVert / 2 + shift3D + 1);
		dc.DrawLine(x0 + radHoriz, y0 + radVert / 2, x0 + radHoriz, y0 + radVert / 2 + shift3D + 1);

		double part = 0;
		for (int n = 0; ; n++) {
			double angle = 360 * part;

			wxCoord x1, y1, x2, y2;

			if (angle > 180) {
				EllipticEgde(x0, y0, radHoriz, radVert, angle, x1, y1);

				x2 = x1;
				y2 = y1 + shift3D + 1/*XXX*/;

				dc.DrawLine(x1, y1, x2, y2);
			}

			if (n >= dataset->GetCount())
				break;

			double v = dataset->GetValue(n, serie);
			part += v / sum;
		}
	}

	dc.SetPen(outlinePen);
	//dc.SetFont(labelsFont);
	double part = 0;
	for (int n = 0; n < dataset->GetCount(); n++) {
		double v = dataset->GetValue(n, serie);

		double angle1 = 360 * part;

		part += v / sum;

		double angle2 = 360 * part;

		dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(colorScheme.GetColor(n)));

		dc.DrawEllipticArc(x0, y0, radHoriz, radVert, angle1, angle2);
	}

	// draw edges
	dc.SetPen(outlinePen);
	dc.SetBrush(noBrush);
	part = 0;
	for (int n = 0; n < dataset->GetCount(); n++) {
		double v = dataset->GetValue(n, serie);

		double angle = 360 * part;

		wxCoord x1, y1;
		EllipticEgde(x0, y0, radHoriz, radVert, angle, x1, y1);
		dc.DrawLine(x0 + radHoriz / 2, y0 + radVert / 2, x1, y1);

		part += v / sum;
	}

	// fill areas
	if (use3DView) {
		double part = 0;
		for (int n = 0; n < dataset->GetCount(); n++) {
			double angle = 360 * part;
			double v = dataset->GetValue(n, serie);
			part += v / sum;

			double angle2 = 360 * part;

			if (angle > 180 || angle2 > 180) {
				wxCoord x1, y1;

				double a;
				if (angle <= 180) {
					a = (180 + angle2) / 2;
				}
				else {
					a = (angle + angle2) / 2;
				}

				EllipticEgde(x0, y0, radHoriz, radVert, a, x1, y1);

				dc.SetBrush(*wxTheBrushList->FindOrCreateBrush(colorScheme.GetColor(n)));
				dc.FloodFill(x1, y1 + shift3D / 2, outlinePen.GetColour(), wxFLOOD_BORDER);
			}
		}
	}
}

