/////////////////////////////////////////////////////////////////////////////
// Name:    drawobject.h
// Purpose:
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DRAWOBJECT_H_
#define DRAWOBJECT_H_

#define wxNoBrush *wxTheBrushList->FindOrCreateBrush(*wxBLACK, wxBRUSHSTYLE_TRANSPARENT)
#define wxNoPen *wxThePenList->FindOrCreatePen(*wxBLACK, 1, wxPENSTYLE_TRANSPARENT)

class WXDLLIMPEXP_FREECHART DrawObject;

/**
 * Base class for objects drawn on chart or perform drawing of
 * another objects (like renderers, area draws, etc).
 */
class WXDLLIMPEXP_FREECHART DrawObject
{
public:
    DrawObject()
    {
    }

    virtual ~DrawObject()
    {
    }
};

#endif /*DRAWOBJECT_H_*/
