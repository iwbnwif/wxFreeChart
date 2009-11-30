/////////////////////////////////////////////////////////////////////////////
// Name:	combinedaxisdemos.cpp
// Purpose: This file contains source code, that demonstrates how to
//          combined axis charts.
// Author:	Moskvichev Andrey V.
// Created:	2009/04/03
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/04/03 16:42:58 moskvichev Exp $
// Copyright:	(c) 2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"


/**
 * Combined axis demo.
 */
class CombinedAxisDemo1 : public ChartDemo
{
public:
	CombinedAxisDemo1()
	: ChartDemo(wxT("Combined axis Demo 1 - simple"))
	{
	}

	virtual Chart *Create()
	{
		// TODO not implemented
		return NULL;
	}
};

ChartDemo *combinedAxisDemos[] = {
		new CombinedAxisDemo1(),
};
int combinedAxisDemosCount = WXSIZEOF(combinedAxisDemos);
