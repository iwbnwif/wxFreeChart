/////////////////////////////////////////////////////////////////////////////
// Name:	chartrenderer.h
// Purpose: Dataset renderer base class declaration.
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
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
class WXDLLIMPEXP_FREECHART Renderer : public wxObject, public DrawObject, public RefObject
{
	DECLARE_CLASS(Renderer)
public:
	Renderer();

	virtual ~Renderer();

	/**
	 * Sets color for serie.
	 * @param serie serie index
	 * @param symbol new color for specified serie
	 */
	virtual void SetSerieColor(int serie, wxColour *color);

	/**
	 * Returns serie color.
	 * @return serie color
	 */
	virtual wxColour GetSerieColor(int serie);

	/**
	 * Sets symbol for serie.
	 * @param serie serie index
	 * @param symbol new symbol for specified serie
	 */
	virtual void SetSerieSymbol(int serie, Symbol *symbol);

	/**
	 * returns symbol for serie.
	 * @return symbol for specified serie
	 */
	virtual Symbol *GetSerieSymbol(int serie);

private:
	ColorMap m_serieColors;
	SymbolMap m_serieSymbols;
};

#endif /*RENDERER_H_*/
