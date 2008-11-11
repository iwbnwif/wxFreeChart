/////////////////////////////////////////////////////////////////////////////
// Name:	marker.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef MARKER_H_
#define MARKER_H_

#include <wx/wxfreechartdefs.h>

class Marker
{
public:
	Marker();
	virtual ~Marker();

	virtual void Draw(wxDC &dc, wxRect rcData) = 0;
};

class LineMarker
{
public:
	LineMarker(wxPen _linePen);
	virtual ~LineMarker();

	virtual void Draw(wxDC &dc, wxRect rcData);
};

class RangeMarker
{
public:
	RangeMarker(wxBrush _brush, wxPen _pen);
	virtual ~RangeMarker();

	virtual void Draw(wxDC &dc, wxRect rcData);
};

#endif /*MARKER_H_*/
