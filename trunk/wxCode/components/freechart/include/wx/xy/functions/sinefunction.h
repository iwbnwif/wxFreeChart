/////////////////////////////////////////////////////////////////////////////
// Name:	sinefunction.h
// Purpose:
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
	 * @param _a y scaling coefficient
	 * @param _min minimal x
	 * @param _max maximal x
	 * @param _step x step
	 */
	SineFunction(double _a, double _min, double _max, double _step);
	virtual ~SineFunction();

	virtual double GetX(int index, int serie);

	virtual double GetY(int index, int serie);

	virtual int GetCount(int serie);

	virtual int GetSerieCount();

	virtual wxString GetSerieName(int serie);

private:
	double a;

	double min;
	double max;
	double step;
};

#endif /*SINEFUNCTION_H_*/
