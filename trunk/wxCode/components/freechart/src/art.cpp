
/////////////////////////////////////////////////////////////////////////////
// Name:	art.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>

#include <wx/art.h>

WX_DECLARE_OBJARRAY(Symbol *, SymbolArray);
WX_DEFINE_OBJARRAY(SymbolArray);

#include "symbols/cross.xpm"
#include "symbols/cyrcle.xpm"
#include "symbols/emptysquare.xpm"
#include "symbols/triangle.xpm"

SymbolArray defaultSymbols;

wxColour defaultColours[] = {
	wxColour(255, 0, 0),
	wxColour(0, 255, 0),
	wxColour(0, 0, 255),
	wxColour(200, 100, 100),
	wxColour(200, 200, 100),
	// TODO add more colors
};

void InitDefaultSymbols()
{
	defaultSymbols.Add(new MaskedSymbol((const char **) cyrcle));
	defaultSymbols.Add(new MaskedSymbol((const char **) triangle));
	defaultSymbols.Add(new MaskedSymbol((const char **) cross));
	defaultSymbols.Add(new MaskedSymbol((const char **) emptysquare));
}

wxColour GetDefaultColour(size_t index)
{
	if (index >= N(defaultColours)) {
		index = index % N(defaultColours);
	}
	return defaultColours[index];
}

Symbol *GetDefaultSymbol(size_t index)
{
	size_t count = defaultSymbols.Count();

	if (count == 0) {
		InitDefaultSymbols();
		count = defaultSymbols.Count();
	}

	if (index >= count) {
		index = index % count;
	}
	return defaultSymbols[index];
}
