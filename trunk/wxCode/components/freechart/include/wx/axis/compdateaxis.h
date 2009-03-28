/////////////////////////////////////////////////////////////////////////////
// Name:	categoryaxis.cpp
// Purpose: category axis implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef COMPDATEAXIS_H_
#define COMPDATEAXIS_H_

#include "wx/axis/labelaxis.h"

class CompDateAxis : public LabelAxis
{
	DECLARE_CLASS(CompDateAxis)
public:
	CompDateAxis(AXIS_LOCATION location);
	virtual ~CompDateAxis();

	void AddInterval(const wxDateSpan &interval);

	void AddInterval(const wxTimeSpan &interval);

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

};

#endif /* COMPDATEAXIS_H_ */
