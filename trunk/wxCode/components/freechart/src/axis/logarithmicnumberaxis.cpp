/////////////////////////////////////////////////////////////////////////////
// Name:	logarithmicnumberaxis.cpp
// Purpose: label axis implementation
// Author:	Andreas Kuchler
// Created:	2008/11/07
// Copyright:	(c) 2010 Andreas Kuchler
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/logarithmicnumberaxis.h>
#include <math.h>

IMPLEMENT_CLASS(LogarithmicNumberAxis, NumberAxis);

LogarithmicNumberAxis::LogarithmicNumberAxis(AXIS_LOCATION location)
: NumberAxis(location)
, m_longExponent(false)
, m_logBase(10.0)
{
	m_logBase == 10.0 ? SetTickFormat(wxT("%2.2e")) : SetTickFormat(wxT("%2.2f"));
}

LogarithmicNumberAxis::~LogarithmicNumberAxis()
{
}

void LogarithmicNumberAxis::SetLogBase(double logBase)
{
	m_logBase = logBase;
	m_logBase == 10.0 ? SetTickFormat(wxT("%2.2e")) : SetTickFormat(wxT("%2.2f"));
}

void LogarithmicNumberAxis::EnableLongLabelExponent(bool enable)
{
	m_longExponent = enable;
}

double LogarithmicNumberAxis::GetValue(size_t step)
{
	double min, max;
	GetDataBounds(min, max);

	double logMin = log(min) / log(m_logBase);
	double logMax = log(max) / log(m_logBase);

	double logInterval = (logMax - logMin) / (GetLabelCount() - 1);
	return min * pow(m_logBase, step * logInterval);
}

void LogarithmicNumberAxis::GetLabel(size_t step, wxString& label)
{
	NumberAxis::GetLabel(step, label);

	if (m_logBase == 10.0 && !m_longExponent) {
		label.erase(label.length() - 3, 1);
	}
}

wxCoord LogarithmicNumberAxis::ToGraphics(wxDC &dc, int minCoord, int gRange, double value)
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

	double logValue = log(value) / log(m_logBase);
	double logMax = log(maxValue) / log(m_logBase);
	double logMin = log(minValue) / log(m_logBase);

	return ::ToGraphics(minCoord, gRange, logMin, logMax, 0/*textMargin*/, IsVertical(), logValue);
}

double LogarithmicNumberAxis::ToData(wxDC &dc, int minCoord, int gRange, wxCoord g)
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

	double logMin = log(minValue) / log(m_logBase);
	double logMax = log(minValue) / log(m_logBase);
	return ::ToData(minCoord, gRange, logMin, logMax, 0/*textMargin*/, IsVertical(), g);
}
