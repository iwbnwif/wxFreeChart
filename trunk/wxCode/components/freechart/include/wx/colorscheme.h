
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

	void operator = (ColorScheme &cs)
	{
		colours = cs.colours;
	}

	void AddColour(wxColour colour)
	{
		colours.Add(colour);
	}

	int GetCount()
	{
		return (int) colours.GetCount();
	}

	wxColour GetColor(int index)
	{
		return colours[index];
	}

private:
	wxColourArray colours;
};

#endif /*COLORSCHEME_H_*/
