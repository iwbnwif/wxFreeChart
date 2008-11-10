
/////////////////////////////////////////////////////////////////////////////
// Name:	sinefunction.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/xy/functions/sinefunction.h>

#include <math.h>

static wxString sineFunctionName(wxT("Sine function"));

SineFunction::SineFunction(double _a, double _min, double _max, double _step)
{
	a = _a;
	min = _min;
	max = _max;
	step = _step;
}

SineFunction::~SineFunction()
{
}

double SineFunction::GetX(int index, int serie)
{
	return min + index * step;
}

double SineFunction::GetY(int index, int serie)
{
	double x = min + index * step;
	return a * sin(x);
}

int SineFunction::GetCount(int serie)
{
	return RoundHigh((max - min) / step) + 1;
}

int SineFunction::GetSerieCount()
{
	return 1;
}

wxString SineFunction::GetSerieName(int serie)
{
	return sineFunctionName;
}
