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

IMPLEMENT_CLASS(Axis, wxObject)

Axis::Axis(AXIS_LOCATION location)
{
	m_location = location;

	m_gridLinesPen = wxPen(*wxLIGHT_GREY, 1, wxSHORT_DASH);
}

Axis::~Axis()
{
}
