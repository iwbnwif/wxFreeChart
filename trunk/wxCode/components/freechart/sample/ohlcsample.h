/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcsample.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCSAMPLE_H_
#define OHLCSAMPLE_H_

#include "ohlc/ohlcdataset.h"

class OHLCSample : public OHLCDataset
{
public:
	OHLCSample();
	virtual ~OHLCSample();
	
	virtual OHLCItem *GetItem(int index);

	virtual int GetCount();
};

#endif /*OHLCSAMPLE_H_*/
