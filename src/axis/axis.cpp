
/////////////////////////////////////////////////////////////////////////////
// Name:	axis.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/axis.h>

Axis::Axis(AXIS_LOCATION _location)
: gridLinesPen(*wxLIGHT_GREY, 1, wxSHORT_DASH)
{
	location = _location;
}

Axis::~Axis()
{
}
