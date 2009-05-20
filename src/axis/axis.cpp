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

	m_gridLinesPen = *wxThePenList->FindOrCreatePen(*wxLIGHT_GREY, 1, wxSHORT_DASH);

	m_winPos = 0;
	m_winWidth = 0;
	m_useWin = false;

	m_marginMin = 5;
	m_marginMax = 5;
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

wxCoord Axis::ToGraphics(wxDC &dc, int minCoord, int gRange, double value)
{
	double minValue, maxValue;
	GetDataBounds(minValue, maxValue);

	minCoord += m_marginMin;
	gRange -= (m_marginMin + m_marginMax);
	if (gRange < 0) {
		gRange = 0;
	}

	if (m_useWin) {
		minValue = m_winPos;
		maxValue = m_winPos + m_winWidth;
	}

	return ::ToGraphics(minCoord, gRange, minValue, maxValue, 0/*textMargin*/, IsVertical(), value);
}

double Axis::ToData(wxDC &dc, int minCoord, int gRange, wxCoord g)
{
	double minValue, maxValue;
	GetDataBounds(minValue, maxValue);

	minCoord += m_marginMin;
	gRange -= (m_marginMin + m_marginMax);
	if (gRange < 0) {
		gRange = 0;
	}

	if (m_useWin) {
		minValue = m_winPos;
		maxValue = m_winPos + m_winWidth;
	}

	double value = ::ToData(minCoord, gRange, minValue, maxValue, 0/*textMargin*/, IsVertical(), g);
	return value;
}

wxCoord ToGraphics(int minCoord, int gRange, double minValue, double maxValue, wxCoord margin, bool vertical, double value)
{
	double k;
	double valueRange = maxValue - minValue;

	minCoord += margin / 2;
	gRange -= margin;

	if (gRange <= 0) {
		return minCoord;
	}

	if (vertical) {
		k = (maxValue - value) / valueRange;
	}
	else {
		k = (value - minValue) / valueRange;
	}

	return (wxCoord) (k * gRange + minCoord);
}

double ToData(int minCoord, int gRange, double minValue, double maxValue, wxCoord margin, bool vertical, wxCoord g)
{
	double valueRange = maxValue - minValue;

	minCoord += margin / 2;
	gRange -= margin;

	if (gRange <= 0) {
		return 0;
	}

	if (vertical) {
		return maxValue - ((g - minCoord) * valueRange / gRange);
	}
	else {
		return minValue + ((g - minCoord) * valueRange / gRange);
	}
}
