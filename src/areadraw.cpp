/////////////////////////////////////////////////////////////////////////////
// Name:	areadraw.cpp
// Purpose: area draw classes implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/areadraw.h>

AreaDraw::AreaDraw()
{
}

AreaDraw::~AreaDraw()
{
}

NoAreaDraw::NoAreaDraw()
{
}

NoAreaDraw::~NoAreaDraw()
{
}

void NoAreaDraw::Draw(wxDC &WXUNUSED(dc), wxRect WXUNUSED(rc))
{
	// do nothing
}


FillAreaDraw::FillAreaDraw(wxPen borderPen, wxBrush fillBrush)
{
	m_fillBrush = fillBrush;
	m_borderPen = borderPen;
}

FillAreaDraw::~FillAreaDraw()
{
}

void FillAreaDraw::Draw(wxDC &dc, wxRect rc)
{
	dc.SetPen(m_borderPen);
	dc.SetBrush(m_fillBrush);
	dc.DrawRectangle(rc);
}

GradientAreaDraw::GradientAreaDraw(wxPen borderPen, wxColour colour1, wxColour colour2, wxDirection dir)
{
	m_borderPen = borderPen;
	m_colour1 = colour1;
	m_colour2 = colour2;
	m_dir = dir;
}

GradientAreaDraw::~GradientAreaDraw()
{
}

void GradientAreaDraw::Draw(wxDC &dc, wxRect rc)
{
	dc.GradientFillLinear(rc, m_colour1, m_colour2, m_dir);

	dc.SetPen(m_borderPen);
	dc.SetBrush(wxNoBrush);
	dc.DrawRectangle(rc);
}

AreaDrawCollection::AreaDrawCollection()
{
}

AreaDrawCollection::~AreaDrawCollection()
{
	AreaDrawMap::iterator it;
	for (it = m_areas.begin(); it != m_areas.end(); it++) {
		delete it->second;
	}
}

void AreaDrawCollection::SetAreaDraw(int serie, AreaDraw *barArea)
{
	if (m_areas.find(serie) != m_areas.end()) {
		AreaDraw *oldBarArea = m_areas[serie];
		//oldBarArea->RemoveObserver(this);
		delete oldBarArea;
	}

	m_areas[serie] = barArea;
	//FireNeedRedraw();
}

AreaDraw *AreaDrawCollection::GetAreaDraw(int serie)
{
	if (m_areas.find(serie) != m_areas.end()) {
		return m_areas[serie];
	}
	return NULL;
}
