/////////////////////////////////////////////////////////////////////////////
// Name:	colorscheme.cpp
// Purpose: color scheme implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/colorscheme.h>
#include <wx/arrimpl.cpp>


ColorScheme::ColorScheme(wxColour *colours, size_t count)
{
	for (size_t n = 0; n < count; n++) {
		AddColour(colours[n]);
	}
}

ColorScheme::ColorScheme()
{
}

ColorScheme::~ColorScheme()
{
}

WX_DEFINE_OBJARRAY(wxColourArray);
