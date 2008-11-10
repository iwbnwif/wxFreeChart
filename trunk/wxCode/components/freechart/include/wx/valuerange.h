
/////////////////////////////////////////////////////////////////////////////
// Name:	valuerange.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef VALUERANGE_H_
#define VALUERANGE_H_

/**
 * Single value range.
 */
class ValueRange
{
public:
	ValueRange();
	virtual ~ValueRange();

	virtual double GetMinValue(bool vertical) = 0;

	virtual double GetMaxValue(bool vertical) = 0;

};

#endif /*VALUERANGE_H_*/
