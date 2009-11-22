/////////////////////////////////////////////////////////////////////////////
// Name:	xyzdataset.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYZDATASET_H_
#define XYZDATASET_H_

#include <wx/xy/xydataset.h>

class XYZRenderer;

/**
 * Dataset with (x,y,z) coordinate data.
 */
class WXDLLIMPEXP_FREECHART XYZDataset : public XYDataset
{
public:
	XYZDataset();
	virtual ~XYZDataset();

	XYZRenderer *GetRenderer()
	{
		return (XYZRenderer *) m_renderer;
	}

	virtual double GetZ(int index, int serie) = 0;

	virtual double GetMinZ();

	virtual double GetMaxZ();
};

#endif /*XYZDATASET_H_*/
