/////////////////////////////////////////////////////////////////////////////
// Name:	marker.cpp
// Purpose: markers implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/marker.h>

#include "wx/arrimpl.cpp"

//
// TODO: write more!
//
WX_DEFINE_EXPORTED_OBJARRAY(MarkerArray);

Marker::Marker()
{
}

Marker::~Marker()
{
}

PointMarker::PointMarker()
{
}

PointMarker::~PointMarker()
{
}

void PointMarker::Draw(wxDC &dc, wxRect rcData, Axis *horizAxis, Axis *vertAxis)
{
	// TODO not implemented!
	//wxCoord x = horizAxis->ToGraphics()
}
