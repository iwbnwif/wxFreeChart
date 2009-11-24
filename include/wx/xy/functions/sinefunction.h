/////////////////////////////////////////////////////////////////////////////
// Name:	sinefunction.h
// Purpose: sine function dataset declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef SINEFUNCTION_H_
#define SINEFUNCTION_H_

#include <wx/xy/xydataset.h>

/**
 * Sine function of type: y = a * sin(x)
 */
class WXDLLIMPEXP_FREECHART SineFunction : public XYDataset
{
public:
	/**
	 * Construct new sine function.
	 * @param a y scaling coefficient
	 * @param min minimal x
	 * @param max maximal x
	 * @param step x step
	 */
	SineFunction(double a, double minX, double maxX, double step);
	virtual ~SineFunction();

	virtual double GetX(int index, int serie);

	virtual double GetY(int index, int serie);

	virtual int GetCount(int serie);

	virtual int GetSerieCount();

	virtual wxString GetSerieName(int serie);

private:
	double m_a;

	double m_minX;
	double m_maxX;
	double m_step;
};

#endif /*SINEFUNCTION_H_*/
