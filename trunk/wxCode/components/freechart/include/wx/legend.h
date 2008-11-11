
/////////////////////////////////////////////////////////////////////////////
// Name:	legend.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef LEGEND_H_
#define LEGEND_H_

#include <wx/wxfreechartdefs.h>
#include <wx/array.h>
#include <wx/dataset.h>
#include <wx/areabackground.h>

const wxCoord labelsSpacing = 2;

/**
 * Legend.
 * TODO: initial quick and dirty.
 */
class Legend
{
public:
	/**
	 * Constructs new legend.
	 * @param _vertPosition vertical position, can be wxTOP, wxCENTER, wxBOTTOM
	 * @param _horizPosition horizontal position, can be wxLEFT, wxCENTER, wxRIGHT
	 */
	Legend(int _vertPosition, int _horizPosition, AreaBackground *_background = NULL);
	virtual ~Legend();

	void Draw(wxDC &dc, wxRect rc, Array<Dataset, 1> &datasets);

	int GetVertPosition()
	{
		return vertPosition;
	}

	int GetHorizPosition()
	{
		return horizPosition;
	}

	/**
	 * Returns size of area to draw legend.
	 */
	wxSize GetExtent(wxDC &dc, Array<Dataset, 1> &datasets);

private:
	int vertPosition;
	int horizPosition;

	wxFont font;

	AreaBackground *background;
};

#endif /*LEGEND_H_*/
