/////////////////////////////////////////////////////////////////////////////
// Name:	xydataset.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYDATASET_H_
#define XYDATASET_H_

#include <wx/dataset.h>
#include <wx/axis/axis.h>

class XYRenderer;

/**
 * Base class for XY datasets.
 */
class WXDLLEXPORT XYDataset : public Dataset, public ValueRange
{
public:
	XYDataset();
	virtual ~XYDataset();

	XYRenderer *GetRenderer()
	{
		return (XYRenderer *) m_renderer;
	}

	/**
	 * Returns x value at index.
	 * @param index index
	 * @return x value
	 */
	virtual double GetX(int index, int serie) = 0;

	/**
	 * Returns y value at index.
	 * @param index index
	 * @return y value
	 */
	virtual double GetY(int index, int serie) = 0;

	/**
	 * Returns maximal y value.
	 * @return maximal y value
	 */
	virtual double GetMaxY();

	/**
	 * Returns minimal y value.
	 * @return minimal y value
	 */
	virtual double GetMinY();

	/**
	 * Returns maximal x value.
	 * @return maximal x value
	 */
	virtual double GetMaxX();

	/**
	 * Returns minimal x value.
	 * @return minimal x value
	 */
	virtual double GetMinX();

	//
	// ValueDataset
	//
	virtual double GetMinValue(bool verticalAxis);

	virtual double GetMaxValue(bool verticalAxis);


protected:
	virtual bool AcceptRenderer(Renderer *r);

private:
};

/**
 * Base class for step datasets.
 * Data specified by xy step, not by xy coordinate as in XYDataset.
 */
class XYStepDataset : public XYDataset
{
public:
	 // TODO
};

#endif /*XYDATASET_H_*/
