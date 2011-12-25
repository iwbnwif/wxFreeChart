/////////////////////////////////////////////////////////////////////////////
// Name:	crosshair.cpp
// Purpose: Crosshair implementation
// Author:	Moskvichev Andrey V.
// Created:	14.04.2010
// Copyright:	(c) 2010 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/crosshair.h"

Crosshair::Crosshair(int style, wxPen *pen)
{

}

Crosshair::~Crosshair()
{

}

void Crosshair::Draw(wxDC &dc, wxRect rcData)//, wxCoord x, wxCoord y)
{
	// TODO
	/*
	dc.SetPen(*m_pen);

	dc.DrawLine(rcData.x, y,
			rcData.x + rcData.width, y);
	*/
}

void Crosshair::ChartMouseDown(wxPoint &pt, int key)
{
}

void Crosshair::ChartMouseUp(wxPoint &pt, int key)
{
}

void Crosshair::ChartMouseMove(wxPoint &pt)
{
}
