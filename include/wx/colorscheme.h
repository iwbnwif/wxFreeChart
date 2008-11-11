
/////////////////////////////////////////////////////////////////////////////
// Name:	colorscheme.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
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
class ColorScheme
{
public:
	ColorScheme(wxColour *colours, int count);

	ColorScheme();
	virtual ~ColorScheme();

	void operator = (const ColorScheme &cs)
	{
		m_colours = cs.m_colours;
	}

	void AddColour(wxColour colour)
	{
		m_colours.Add(colour);
	}

	size_t GetCount()
	{
		return m_colours.GetCount();
	}

	wxColour GetColor(size_t index)
	{
		return m_colours[index];
	}

private:
	wxColourArray m_colours;
};

#endif /*COLORSCHEME_H_*/
