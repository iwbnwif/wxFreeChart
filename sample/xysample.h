/////////////////////////////////////////////////////////////////////////////
// Name:	xysample.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYSAMPLE_H_
#define XYSAMPLE_H_

#include "xy/xydataset.h"

class XYSample : public XYDataset
{
public:
	XYSample();
	virtual ~XYSample();
	
	virtual double GetX(int index, int serie);
	
	virtual double GetY(int index, int serie);
	
	virtual int GetCount(int serie);

	virtual int GetSerieCount();
	
	virtual wxString GetSerieName(int serie);
};

#endif /*XYSAMPLE_H_*/
