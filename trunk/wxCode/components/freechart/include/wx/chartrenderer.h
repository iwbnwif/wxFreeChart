/////////////////////////////////////////////////////////////////////////////
// Name:	chartrenderer.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef RENDERER_H_
#define RENDERER_H_

#include <wx/wxfreechartdefs.h>
#include <wx/drawobject.h>
#include <wx/refobject.h>

/**
 * Base class for all renderers.
 */
class WXDLLEXPORT Renderer : public DrawObject, public RefObject
{
public:
	Renderer();
	virtual ~Renderer();
};

#endif /*RENDERER_H_*/
