/////////////////////////////////////////////////////////////////////////////
// Name:	categoryaxis.h
// Purpose: category axis declarations
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CATEGORYAXIS_H_
#define CATEGORYAXIS_H_

#include <wx/axis/labelaxis.h>

/**
 * An axis for displaying category names.
 */
class WXDLLIMPEXP_FREECHART CategoryAxis : public LabelAxis
{
	DECLARE_CLASS(CategoryAxis)
public:
	CategoryAxis(AXIS_LOCATION location);
	virtual ~CategoryAxis();

	virtual void UpdateBounds();

protected:
	virtual bool AcceptDataset(Dataset *dataset);

	//
	// LabelAxis
	//
	virtual double GetValue(int step);

	virtual void GetLabel(int step, wxString &label);

	virtual bool IsEnd(int step);

	virtual wxSize GetLongestLabelExtent(wxDC &dc);

	virtual void GetDataBounds(double &minValue, double &maxValue);

private:
	int m_categoryCount;
	wxString m_longestCategory;
};

#endif /*CATEGORYAXIS_H_*/
