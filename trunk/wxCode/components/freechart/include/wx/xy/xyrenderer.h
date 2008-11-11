
/////////////////////////////////////////////////////////////////////////////
// Name:	xyrenderer.h
// Purpose: xy renderer base class declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYRENDERER_H_
#define XYRENDERER_H_

#include <wx/renderer.h>
#include <wx/axis/axis.h>
#include <wx/xy/xydataset.h>

/**
 * Base class for all XYDataset renderers.
 */
class XYRenderer : public Renderer
{
public:
	XYRenderer();
	virtual ~XYRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset) = 0;
};

#endif /*XYRENDERER_H_*/
