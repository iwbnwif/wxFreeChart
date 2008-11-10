
/////////////////////////////////////////////////////////////////////////////
// Name:	symbol.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <wx/wxfreechartdefs.h>

class Symbol
{
public:
	Symbol();
	virtual ~Symbol();

	virtual void SetColor(wxColour _color);

	virtual void Draw(wxDC &dc, wxCoord x, wxCoord y) = 0;

	virtual wxSize GetExtent() = 0;
};

class MaskedSymbol : public Symbol
{
public:
	MaskedSymbol(const char **maskData, wxCoord _size = 9);

	virtual ~MaskedSymbol();

	virtual void SetColor(wxColour _color);

	virtual void Draw(wxDC &dc, wxCoord x, wxCoord y);

	virtual wxSize GetExtent();

private:
	wxBitmap maskBmp;
	wxBitmap symbolBitmap;

	bool initialized;

	wxCoord size;
};

#endif /*SYMBOL_H_*/
