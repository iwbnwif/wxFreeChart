/////////////////////////////////////////////////////////////////////////////
// Name:	art.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>

#include <wx/art.h>

WX_DECLARE_OBJARRAY(Symbol *, SymbolArray);
WX_DEFINE_OBJARRAY(SymbolArray);

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
	defaultSymbols.Add(new SquareSymbol());
	defaultSymbols.Add(new TriangleSymbol());
	defaultSymbols.Add(new CircleSymbol());
	defaultSymbols.Add(new CrossSymbol());
}

wxColour GetDefaultColour(size_t index)
{
	if (index >= WXSIZEOF(defaultColours)) {
		index = index % WXSIZEOF(defaultColours);
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
