/////////////////////////////////////////////////////////////////////////////
// Name:	renderer.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/chartrenderer.h>

IMPLEMENT_CLASS(Renderer, wxObject)

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetSerieColor(int serie, wxColour *color)
{
	m_serieColors[serie] = *color;
	FireNeedRedraw();
}

wxColour Renderer::GetSerieColor(int serie)
{
	if (m_serieColors.find(serie) == m_serieColors.end()) {
		return GetDefaultColour(serie);
	}
	return m_serieColors[serie];
}

void Renderer::SetSerieSymbol(int serie, Symbol *symbol)
{
	m_serieSymbols[serie] = symbol;
	FireNeedRedraw();
}

Symbol *Renderer::GetSerieSymbol(int serie)
{
	if (m_serieSymbols.find(serie) == m_serieSymbols.end()) {
		return GetDefaultSymbol(serie);
	}
	return m_serieSymbols[serie];
}
