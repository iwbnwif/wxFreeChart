/////////////////////////////////////////////////////////////////////////////
// Name:	legend.h
// Purpose: Legend declaration.
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef LEGEND_H_
#define LEGEND_H_

#include <wx/wxfreechartdefs.h>
#include <wx/array.h>
#include <wx/dataset.h>
#include <wx/areadraw.h>

const wxCoord labelsSpacing = 2;

/**
 * Legend.
 */
class WXDLLIMPEXP_FREECHART Legend
{
public:
	/**
	 * Constructs new legend.
	 * @param vertPosition vertical position, can be wxTOP, wxCENTER, wxBOTTOM
	 * @param horizPosition horizontal position, can be wxLEFT, wxCENTER, wxRIGHT
	 * @param background background for legend area
	 * @param symbolTextGap distance between symbol and text
	 * @param margin legend margin
	 */
	Legend(int vertPosition, int horizPosition, AreaDraw *background = new FillAreaDraw(), int symbolTextGap = 2, int margin = 2);

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

	/**
	 * Sets font to draw legend labels.
	 * @param font new font to draw legend labels
	 */
	void SetTextFont(wxFont font)
	{
		m_font = font;
	}

	/**
	 * Returns font to draw legend labels.
	 * @return font to draw legend labels
	 */
	wxFont GetTextFont()
	{
		return m_font;
	}

	/**
	 * Returns size of area to draw legend.
	 * @param dc device context
	 * @param datasetes dataset array
	 * @return size needed for legend area
	 */
	wxSize GetExtent(wxDC &dc, Array<Dataset, 1> &datasets);

private:
	int m_vertPosition;
	int m_horizPosition;

	wxFont m_font;

	AreaDraw *m_background;

	int m_symbolTextGap;
	int m_margin;
};

#endif /*LEGEND_H_*/
