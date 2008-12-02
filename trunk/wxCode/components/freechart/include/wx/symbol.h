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

class WXDLLEXPORT Symbol
{
public:
	Symbol();
	virtual ~Symbol();

	virtual void SetColor(wxColour color);

	virtual void Draw(wxDC &dc, wxCoord x, wxCoord y) = 0;

	virtual wxSize GetExtent() = 0;
};

class WXDLLEXPORT MaskedSymbol : public Symbol
{
public:
	MaskedSymbol(const char **maskData, wxCoord size = 9);

	virtual ~MaskedSymbol();

	virtual void SetColor(wxColour color);

	virtual void Draw(wxDC &dc, wxCoord x, wxCoord y);

	virtual wxSize GetExtent();

private:
	wxBitmap m_maskBmp;
	wxBitmap m_symbolBitmap;

	bool m_initialized;

	wxCoord m_size;
};

class WXDLLEXPORT ShapeSymbol : public Symbol
{
public:
	ShapeSymbol(wxCoord size);
	virtual ~ShapeSymbol();

	virtual void SetColor(wxColour color);

	virtual wxSize GetExtent();

protected:
	wxColour m_color;
	wxCoord m_size;
};


class WXDLLEXPORT CircleSymbol : public ShapeSymbol
{
public:
	CircleSymbol(wxCoord size = 5);
	virtual ~CircleSymbol();

	virtual void Draw(wxDC &dc, wxCoord x, wxCoord y);
};

class WXDLLEXPORT SquareSymbol : public ShapeSymbol
{
public:
	SquareSymbol(wxCoord size = 5);
	virtual ~SquareSymbol();

	virtual void Draw(wxDC &dc, wxCoord x, wxCoord y);
};

class WXDLLEXPORT CrossSymbol : public ShapeSymbol
{
public:
	CrossSymbol(wxCoord size = 5);
	virtual ~CrossSymbol();

	virtual void Draw(wxDC &dc, wxCoord x, wxCoord y);
};

class WXDLLEXPORT TriangleSymbol : public ShapeSymbol
{
public:
	TriangleSymbol(wxCoord size = 5);
	virtual ~TriangleSymbol();

	virtual void Draw(wxDC &dc, wxCoord x, wxCoord y);
};

#endif /*SYMBOL_H_*/
