/////////////////////////////////////////////////////////////////////////////
// Name:	drawobject.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DRAWOBJECT_H_
#define DRAWOBJECT_H_

#include <wx/observable.h>

#define wxNoBrush *wxTheBrushList->FindOrCreateBrush(*wxBLACK, wxTRANSPARENT)
#define wxNoPen *wxThePenList->FindOrCreatePen(*wxBLACK, 1, wxTRANSPARENT)

class WXDLLIMPEXP_FREECHART DrawObject;

/**
 * Interface to receive DrawObject events.
 */
class WXDLLIMPEXP_FREECHART DrawObserver
{
public:
	DrawObserver()
	{
	}

	virtual ~DrawObserver()
	{
	}

	virtual void NeedRedraw(DrawObject *obj) = 0;
};

/**
 * Base class for objects drawn on chart or perform drawing of
 * another objects (like renderers).
 */
class WXDLLIMPEXP_FREECHART DrawObject : public Observable<DrawObserver>
{
public:
	DrawObject()
	{
	}

	virtual ~DrawObject()
	{
	}

protected:
	FIRE_WITH_THIS(NeedRedraw);
};

#endif /*DRAWOBJECT_H_*/
