/////////////////////////////////////////////////////////////////////////////
// Name:	axis.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/axis.h>

IMPLEMENT_CLASS(Axis, wxObject)

AxisObserver::AxisObserver()
{
}

AxisObserver::~AxisObserver()
{
}

Axis::Axis(AXIS_LOCATION location)
{
	m_location = location;

	m_gridLinesPen = wxPen(*wxLIGHT_GREY, 1, wxSHORT_DASH);


	m_winPos = 0;
	m_winWidth = 0;
	m_useWin = false;
}

Axis::~Axis()
{
}

bool Axis::IsVisible(double value)
{
	if (m_useWin) {
		return (value >= m_winPos && value <= (m_winPos + m_winWidth));
	}
	else {
		return true;
	}
}

bool Axis::IntersectsWindow(double v0, double v1)
{
	if (m_useWin) {
		return ((v0 >= v1 && v0 >= m_winPos && v1 <= m_winPos)
				|| (v0 < v1 && v1 >= m_winPos && v0 <= m_winPos));
	}
	else {
		return true; // window not used, so it always intersect
	}
}

double Axis::BoundValue(double value)
{
	if (m_useWin) {
		if (value <= m_winPos) {
			return m_winPos;
		}
		else if (value >= (m_winPos + m_winWidth)) {
			return m_winPos + m_winWidth;
		}
		else {
			return value;
		}
	}
	else {
		return value;
	}
}
