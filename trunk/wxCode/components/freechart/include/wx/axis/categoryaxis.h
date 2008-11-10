
/////////////////////////////////////////////////////////////////////////////
// Name:	categoryaxis.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CATEGORYAXIS_H_
#define CATEGORYAXIS_H_

#include <wx/axis/labelaxis.h>

/**
 * An axis for displaying category names.
 */
class CategoryAxis : public LabelAxis
{
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

	virtual wxCoord DoToGraphics(wxDC &dc, int minG, int range, double value);

private:
	int categoryCount;
	wxString longestCategory;
};

#endif /*CATEGORYAXIS_H_*/
