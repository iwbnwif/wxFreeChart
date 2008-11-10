
/////////////////////////////////////////////////////////////////////////////
// Name:	multiplot.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/multiplot.h>

MultiPlot::MultiPlot(int _rows, int _cols, wxCoord _horizGap, wxCoord _vertGap)
{
	rows = _rows;
	cols = _cols;
	horizGap = _horizGap;
	vertGap = _vertGap;
}

MultiPlot::~MultiPlot()
{
}

void MultiPlot::PlotNeedRedraw(Plot *_plot)
{
	FirePlotNeedRedraw();
}

bool MultiPlot::HasData()
{
	return (subPlots.GetSize() != 0);
}

void MultiPlot::DrawData(wxDC &dc, wxRect rc)
{
	wxCHECK_RET(rows != 0 || cols != 0, wxT("row and column count = 0"));

	int row = 0;
	int col = 0;

	int _rows = rows;
	int _cols = cols;
	bool vertical = false;

	if (_cols == 0) {
		_cols = 1;

		int row = 0;
		for (int n = 0; n < subPlots.GetSize(); n++) {
			if (row >= _rows) {
				row = 0;
				_cols++;
			}
			row++;
		}

		vertical = true;
	}
	if (rows == 0) {
		_rows = 1;

		int col = 0;
		for (int n = 0; n < subPlots.GetSize(); n++) {
			if (col >= _cols) {
				col = 0;

				_rows++;
			}
			col++;
		}
	}

	wxCoord subWidth = (rc.width - (_cols - 1) * horizGap) / _cols;
	wxCoord subHeight = (rc.height - (_rows - 1) * vertGap) / _rows;

	wxCoord x = rc.x;
	wxCoord y = rc.y;

	for (int n = 0; n < subPlots.GetSize(); n++) {
		// TODO untested!
		if (vertical) {
			if (row >= _rows) {
				row = 0;
				y = rc.y;
				x += subWidth + horizGap;

				col++;
				if (col >= _cols)
					break;
			}
		}
		else {
			if (col >= _cols) {
				col = 0;
				x = rc.x;
				y += subHeight + vertGap;

				row++;
				if (row >= _rows)
					break;
			}
		}

		wxRect subRc(x, y, subWidth, subHeight);

		subPlots[n]->Draw(dc, subRc);

		if (vertical) {
			row++;
			y += subHeight + vertGap;
		}
		else {
			col++;
			x += subWidth + horizGap;
		}
	}
}
