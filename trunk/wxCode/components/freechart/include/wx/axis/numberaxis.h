
/////////////////////////////////////////////////////////////////////////////
// Name:	numberaxis.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef NUMBERAXIS_H_
#define NUMBERAXIS_H_

#include <wx/axis/labelaxis.h>

/**
 * An axis for displaying and scaling numerical data.
 */
class NumberAxis : public LabelAxis
{
public:
	NumberAxis(AXIS_LOCATION location);
	virtual ~NumberAxis();

	virtual void UpdateBounds();

	/**
	 * Sets format for tick marks.
	 * @param _tickFormat tick format
	 */
	void SetTickFormat(const wxString &_tickFormat)
	{
		tickFormat = _tickFormat;
		FireNeedRedraw();
	}

	/**
	 * Set whether to use integer values instead of doubles.
	 * @param _intValues if true than use integer values, false - double values
	 */
	void IntegerValues(bool _intValues = true)
	{
		intValues = _intValues;
		// TODO recalc tick steps
		FireNeedRedraw();
	}

	/**
	 * Make data bounds fixed.
	 * @param min minimal data value
	 * @param max maximal data value
	 */
	void FixedBounds(double _minValue, double _maxValue);

protected:
	virtual bool AcceptDataset(Dataset *dataset);

	//
	// LabelAxis
	//
	virtual double GetValue(int step);

	virtual void GetLabel(int step, wxString &label);

	virtual bool IsEnd(int step);

	virtual bool HasTicks();

	virtual wxSize GetLongestLabelExtent(wxDC &dc);

	virtual wxCoord DoToGraphics(wxDC &dc, int minG, int range, double value);

private:
	void DrawTicks(wxDC &dc, wxRect &rc);
	void DrawBorderLine(wxDC &dc, wxRect &rc);

	wxString tickFormat;

	double minValue;
	double maxValue;

	double minorTick;
	double majorTick;

	bool intValues;

	bool hasTicks;

	bool fixedBounds;
};

#endif /*NUMBERAXIS_H_*/
