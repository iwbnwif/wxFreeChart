/////////////////////////////////////////////////////////////////////////////
// Name:	polynom.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef POLYNOM_H_
#define POLYNOM_H_

#include <wx/xy/xydataset.h>

/**
 * Polynom function of type: y = c0 * x^n + c1 * x^(n-1) + ... + c(n-1) * x + cn
 * where: c0 ... cn - coefficients
 */
class WXDLLEXPORT Polynom : public XYDataset
{
public:
	/**
	 * Constucts new polynom function dataset.
	 * @param _coefs coefficients for x values
	 * @param _min minimal x value
	 * @param _max maximal x value
	 * @param _step x value step
	 */
	Polynom(double *_coefs, int _coefCount, double _min, double _max, double _step);

	virtual ~Polynom();

	virtual double GetX(int index, int serie);

	virtual double GetY(int index, int serie);

	virtual int GetCount(int serie);

	virtual int GetSerieCount();

	virtual wxString GetSerieName(int serie);

private:
	double CalcY(double x);

	double *coefs;
	int coefCount;
	double min;
	double max;
	double step;
};

#endif /*POLYNOM_H_*/
