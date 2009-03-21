/////////////////////////////////////////////////////////////////////////////
// Name:	numberaxis.h
// Purpose: Number axis declaration.
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
class WXDLLEXPORT NumberAxis : public LabelAxis
{
	DECLARE_CLASS(NumberAxis)
public:
	NumberAxis(AXIS_LOCATION location);
	virtual ~NumberAxis();

	virtual void UpdateBounds();

	/**
	 * Sets format for tick marks.
	 * @param tickFormat tick format
	 */
	void SetTickFormat(const wxString &tickFormat)
	{
		m_tickFormat = tickFormat;
		FireNeedRedraw();
	}

	/**
	 * Set whether to use integer values instead of doubles.
	 * @param _intValues if true than use integer values, false - double values
	 */
	void IntegerValues(bool intValues = true)
	{
		m_intValues = intValues;
		// TODO recalc tick steps
		FireNeedRedraw();
	}

	/**
	 * Make data bounds fixed.
	 * @param minValue minimal data value
	 * @param maxValue maximal data value
	 */
	void SetFixedBounds(double minValue, double maxValue);

protected:
	virtual bool AcceptDataset(Dataset *dataset);

	//
	// LabelAxis
	//
	virtual double GetValue(int step);

	virtual void GetLabel(int step, wxString &label);

	virtual bool IsEnd(int step);

	virtual bool HasLabels();

	virtual wxSize GetLongestLabelExtent(wxDC &dc);

	virtual wxCoord DoToGraphics(wxDC &dc, int minG, int range, double value);

	virtual double DoToData(wxDC &dc, int minG, int range, wxCoord g);

private:
	void UpdateTickValues();

	wxString m_tickFormat;

	double m_minValue;
	double m_maxValue;

	double m_minorTick;
	double m_majorTick;

	int m_stepCount;
	bool m_intValues;

	bool m_hasTicks;

	bool m_fixedBounds;
};

#endif /*NUMBERAXIS_H_*/
