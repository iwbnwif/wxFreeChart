/////////////////////////////////////////////////////////////////////////////
// Name:	xyarearenderer.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYAREARENDERER_H_
#define XYAREARENDERER_H_

#include <wx/xy/xyrenderer.h>

class XYAreaRenderer : public XYRenderer
{
public:
	XYAreaRenderer();
	virtual ~XYAreaRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, XYDataset *dataset);

	virtual void Draw(wxDC &dc, wxRect rcData, wxCoord x0, wxCoord y0, wxCoord x1, wxCoord y1);

private:
	wxPen m_outlinePen;
	wxBrush m_areaBrush;
};

#endif /*XYAREARENDERER_H_*/
