
/////////////////////////////////////////////////////////////////////////////
// Name:	polynom.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/functions/polynom.h>

static wxString polynomFunctionName(wxT("Polynom function"));

Polynom::Polynom(double *_coefs, int _coefCount, double _min, double _max, double _step)
{
	coefs = new double[_coefCount];
	for (int n = 0; n < _coefCount; n++)
		coefs[n] = _coefs[n];
	coefCount = _coefCount;
	min = _min;
	max = _max;
	step = _step;
}

Polynom::~Polynom()
{
	SAFE_DELETE(coefs);
}

double Polynom::GetX(int index, int serie)
{
	return min + index * step;
}

double Polynom::GetY(int index, int serie)
{
	return CalcY(GetX(index, 0));
}

int Polynom::GetCount(int serie)
{
	return RoundHigh((max - min) / step);
}

int Polynom::GetSerieCount()
{
	return 1;
}

double Polynom::CalcY(double x)
{
	double xn = 1;
	double y = 0;

	for (int n = coefCount - 1; n >= 0; n--) {
		y += xn * coefs[n];
		xn *= x;
	}
	return y;
}

wxString Polynom::GetSerieName(int serie)
{
	return polynomFunctionName;
}
