/////////////////////////////////////////////////////////////////////////////
// Name:	colorscheme.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef COLORSCHEME_H_
#define COLORSCHEME_H_

#include <wx/wxfreechartdefs.h>
#include <wx/dynarray.h>

WX_DECLARE_OBJARRAY(wxColour, wxColourArray);

/**
 * Defines set of colors for use by PiePlots, etc...
 */
class WXDLLIMPEXP_FREECHART ColorScheme
{
public:
	ColorScheme(wxColour *colours, int count);

	ColorScheme();
	virtual ~ColorScheme();

	void operator = (const ColorScheme &cs)
	{
		m_colours = cs.m_colours;
	}

	/**
	 * Add colour to color scheme.
	 * @param colour colour to be added
	 */
	void AddColour(wxColour colour)
	{
		m_colours.Add(colour);
	}

	/**
	 * Returns color count in this color scheme.
	 * @return color count
	 */
	size_t GetCount()
	{
		return m_colours.GetCount();
	}

	/**
	 * Returns color at specified index.
	 * @param index index of color
	 * @return color at specified index
	 */
	wxColour GetColor(size_t index)
	{
		return m_colours[index];
	}

private:
	wxColourArray m_colours;
};

#endif /*COLORSCHEME_H_*/
