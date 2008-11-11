/////////////////////////////////////////////////////////////////////////////
// Name:	dateaxis.h
// Purpose: Date/time axis declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATEAXIS_H_
#define DATEAXIS_H_

#include <wx/axis/labelaxis.h>

/**
 * An axis for displaying date/time values.
 */
class DateAxis : public LabelAxis
{
public:
	DateAxis(AXIS_LOCATION location);
	virtual ~DateAxis();

	virtual void UpdateBounds();

	/**
	 * Sets date format for date labels.
	 * @param dateFormat date format in strftime style
	 */
	void SetDateFormat(const wxString &dateFormat)
	{
		m_dateFormat = dateFormat;
		FireNeedRedraw();
	}

protected:
	virtual bool AcceptDataset(Dataset *dataset);

	//
	// LabelAxis
	//
	virtual double GetValue(int step);

	virtual void GetLabel(int step, wxString &label);

	virtual bool IsEnd(int step);

	virtual wxSize GetLongestLabelExtent(wxDC &dc);

	virtual wxCoord DoToGraphics(wxDC &dc, int minG, int range, double value);

private:
	int m_dateCount;

	wxString m_dateFormat;
};

#endif /*DATEAXIS_H_*/
