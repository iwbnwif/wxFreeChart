/////////////////////////////////////////////////////////////////////////////
// Name:	polynom.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef POLYNOM_H_
#define POLYNOM_H_

#include <wx/xy/xydataset.h>

/**
 * Polynom function of type: y = c0 * x^n + c1 * x^(n-1) + ... + c(n-1) * x + cn
 * where: c0 ... cn - coefficients
 */
class WXDLLIMPEXP_FREECHART Polynom : public XYDataset
{
public:
	/**
	 * Constucts new polynom function dataset.
	 * @param coefs coefficients for x values
	 * @param min minimal x value
	 * @param max maximal x value
	 * @param step x value step
	 */
	Polynom(double *coefs, int coefCount, double min, double max, double step);

	virtual ~Polynom();

	virtual double GetX(int index, int serie);

	virtual double GetY(int index, int serie);

	virtual int GetCount(int serie);

	virtual int GetSerieCount();

	virtual wxString GetSerieName(int serie);

private:
	double CalcY(double x);

	double *m_coefs;
	int m_coefCount;
	double m_min;
	double m_max;
	double m_step;
};

#endif /*POLYNOM_H_*/
