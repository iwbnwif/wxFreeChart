/////////////////////////////////////////////////////////////////////////////
// Name:	sinefunction.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/functions/sinefunction.h>

#include <math.h>

static wxString sineFunctionName(wxT("Sine function"));

SineFunction::SineFunction(double a, double minX, double maxX, double step)
{
	m_a = a;
	m_minX = minX;
	m_maxX = maxX;
	m_step = step;
}

SineFunction::~SineFunction()
{
}

double SineFunction::GetX(int index, int WXUNUSED(serie))
{
	return m_minX + index * m_step;
}

double SineFunction::GetY(int index, int WXUNUSED(serie))
{
	double x = m_minX + index * m_step;
	return m_a * sin(x);
}

int SineFunction::GetCount(int WXUNUSED(serie))
{
	return RoundHigh((m_maxX - m_minX) / m_step) + 1;
}

int SineFunction::GetSerieCount()
{
	return 1;
}

wxString SineFunction::GetSerieName(int WXUNUSED(serie))
{
	return sineFunctionName;
}
