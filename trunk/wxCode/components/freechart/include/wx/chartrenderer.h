/////////////////////////////////////////////////////////////////////////////
// Name:	chartrenderer.h
// Purpose: Dataset renderer base class declaration.
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef RENDERER_H_
#define RENDERER_H_

#include <wx/wxfreechartdefs.h>
#include <wx/drawobject.h>
#include <wx/refobject.h>
#include <wx/art.h>

/**
 * Base class for all renderers.
 */
class WXDLLEXPORT Renderer : public DrawObject, public RefObject
{
public:
	Renderer();
	virtual ~Renderer();

	virtual void SetSerieColor(int serie, wxColour *color);

	virtual wxColour GetSerieColor(int serie);

	virtual void SetSerieSymbol(int serie, Symbol *symbol);

	virtual Symbol *GetSerieSymbol(int serie);

private:
	ColorMap m_serieColors;
	SymbolMap m_serieSymbols;
};

#endif /*RENDERER_H_*/
