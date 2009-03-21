/////////////////////////////////////////////////////////////////////////////
// Name:	legend.h
// Purpose: Legend declaration.
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
 */
class WXDLLEXPORT Legend
{
public:
	/**
	 * Constructs new legend.
	 * @param vertPosition vertical position, can be wxTOP, wxCENTER, wxBOTTOM
	 * @param horizPosition horizontal position, can be wxLEFT, wxCENTER, wxRIGHT
	 * @param background background for legend area
	 */
	Legend(int vertPosition, int horizPosition, AreaBackground *background = NULL);
	virtual ~Legend();

	void Draw(wxDC &dc, wxRect rc, Array<Dataset, 1> &datasets);

	int GetVertPosition()
	{
		return m_vertPosition;
	}

	int GetHorizPosition()
	{
		return m_horizPosition;
	}

	void SetTextFont(wxFont font)
	{
		m_font = font;
	}

	wxFont GetTextFont()
	{
		return m_font;
	}

	/**
	 * Returns size of area to draw legend.
	 */
	wxSize GetExtent(wxDC &dc, Array<Dataset, 1> &datasets);

private:
	int m_vertPosition;
	int m_horizPosition;

	wxFont m_font;

	AreaBackground *m_background;
};

#endif /*LEGEND_H_*/
