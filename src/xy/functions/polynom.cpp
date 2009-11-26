/////////////////////////////////////////////////////////////////////////////
// Name:	polynom.cpp
// Purpose: polynom function implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/functions/polynom.h>

static wxString polynomFunctionName(wxT("Polynom function"));

Polynom::Polynom(double *coefs, int coefCount, double min, double max, double step)
{
	m_coefs = new double[coefCount];
	for (int n = 0; n < coefCount; n++)
		m_coefs[n] = coefs[n];
	m_coefCount = coefCount;
	m_min = min;
	m_max = max;
	m_step = step;
}

Polynom::~Polynom()
{
	wxDELETEA(m_coefs);
}

double Polynom::GetX(int index, int serie)
{
	return m_min + index * m_step;
}

double Polynom::GetY(int index, int serie)
{
	return CalcY(GetX(index, 0));
}

int Polynom::GetCount(int serie)
{
	return RoundHigh((m_max - m_min) / m_step);
}

int Polynom::GetSerieCount()
{
	return 1;
}

double Polynom::CalcY(double x)
{
	double xn = 1;
	double y = 0;

	for (int n = m_coefCount - 1; n >= 0; n--) {
		y += xn * m_coefs[n];
		xn *= x;
	}
	return y;
}

wxString Polynom::GetSerieName(int serie)
{
	return polynomFunctionName;
}
