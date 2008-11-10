
/////////////////////////////////////////////////////////////////////////////
// Name:	drawobject.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DRAWOBJECT_H_
#define DRAWOBJECT_H_

#include <wx/observable.h>


// TODO move from here
static wxBrush noBrush(*wxBLACK, wxTRANSPARENT);
static wxPen noPen(*wxBLACK, 1, wxTRANSPARENT);

class DrawObject;

class DrawObserver
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

class DrawObject : public Observable<DrawObserver>
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
