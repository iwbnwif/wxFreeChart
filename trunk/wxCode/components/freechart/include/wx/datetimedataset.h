
/////////////////////////////////////////////////////////////////////////////
// Name:	datetimedataset.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATETIMEDATASET_H_
#define DATETIMEDATASET_H_

#include <time.h>

class DateTimeDataset
{
public:
	DateTimeDataset();
	virtual ~DateTimeDataset();

	virtual time_t GetDate(int index) = 0;

	virtual int GetCount() = 0;
};

#endif /*DATETIMEDATASET_H_*/
