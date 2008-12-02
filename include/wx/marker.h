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

class WXDLLEXPORT Marker
{
public:
	Marker();
	virtual ~Marker();

	virtual void Draw(wxDC &dc, wxRect rcData) = 0;
};

class WXDLLEXPORT LineMarker
{
public:
	LineMarker(wxPen linePen);
	virtual ~LineMarker();

	virtual void Draw(wxDC &dc, wxRect rcData);
};

class WXDLLEXPORT RangeMarker
{
public:
	RangeMarker(wxBrush brush, wxPen pen);
	virtual ~RangeMarker();

	virtual void Draw(wxDC &dc, wxRect rcData);
};

#endif /*MARKER_H_*/
