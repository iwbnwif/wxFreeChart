/////////////////////////////////////////////////////////////////////////////
// Name:	numberaxis.h
// Purpose: Number axis declaration.
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2010 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef NUMBERAXIS_H_
#define NUMBERAXIS_H_

#include <wx/axis/labelaxis.h>

/**
 * An axis for displaying and scaling numerical data.
 */
class WXDLLIMPEXP_FREECHART NumberAxis : public LabelAxis
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
		FireAxisChanged();
	}

	/**
	 * Sets count of labels.
	 * @param labelCount count of labels
	 */
	void SetLabelCount(size_t labelCount)
	{
		if (m_labelCount != labelCount) {
			m_labelCount = labelCount;
			FireAxisChanged();
		}
	}

	/**
	 * Set whether to use integer values instead of doubles.
	 * @param intValues if true than use integer values, false - double values
	 */
	void IntegerValues(bool intValues = true)
	{
		if (m_intValues != intValues) {
			m_intValues = intValues;
			// TODO recalc tick steps
			FireAxisChanged();
		}
	}

	/**
	 * Returns multiplier for values.
	 * @return multiplier
	 */
	double GetMultiplier() const;

	/**
	 * Sets multiplier for values.
	 * @param multiplier multiplier
	 */
	void SetMultiplier(double multiplier);

	/**
	 * Make data bounds fixed.
	 * @param minValue minimal data value
	 * @param maxValue maximal data value
	 */
	void SetFixedBounds(double minValue, double maxValue);

	/**
	 * Returns bounds, taken from data, eg. real min-max value.
	 * @param minValue output minimal data value
	 * @param maxValue output maximal data value
	 */
	virtual void GetDataBounds(double &minValue, double &maxValue) const;

	/**
	 * Returns label count, to be draw on axis.
	 * @return label count, to be draw on axis
	 */
	size_t GetLabelCount() const;

protected:
	virtual bool AcceptDataset(Dataset *dataset);
  void UpdateTickValues();

	//
	// LabelAxis
	//
	virtual double GetValue(size_t step);

	virtual void GetLabel(size_t step, wxString &label);

	virtual bool IsEnd(size_t step);

	virtual bool HasLabels();

	virtual wxSize GetLongestLabelExtent(wxDC &dc);

  bool m_fixedBounds;
	bool m_hasLabels;
  double m_minValue;
	double m_maxValue;

private:


	wxString m_tickFormat;


	double m_labelInterval;

	size_t m_labelCount;
	bool m_intValues;

	double m_multiplier;


};

#endif /*NUMBERAXIS_H_*/
