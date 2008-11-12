/////////////////////////////////////////////////////////////////////////////
// Name:	categorydataset.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CATEGORYDATASET_H_
#define CATEGORYDATASET_H_

#include <wx/dataset.h>
#include <wx/xy/xyrenderer.h>

/**
 * Dataset for data values in form [category name, value].
 */
class CategoryDataset : public XYDataset//, public ValueRange
{
public:
	CategoryDataset();
	virtual ~CategoryDataset();

	/**
	 * Returns value associated with category at index.
	 * @param index value associated with category
	 * @return value associated with category
	 */
	virtual double GetValue(int index, int serie) = 0;

	virtual int GetSerieCount() = 0;

	/**
	 * Returns category name at index.
	 * @param index index of category name
	 * @return category name
	 */
	virtual wxString GetName(int index) = 0;

	/**
	 * Returns category count.
	 * @return category count
	 */
	virtual int GetCount() = 0;

	virtual bool HasValue(int index, int serie);

	//
	// ValueRange
	//
	virtual double GetMinValue(bool verticalAxis);

	virtual double GetMaxValue(bool verticalAxis);

	//
	// XYDataset
	//
	virtual double GetX(int index, int serie);

	virtual double GetY(int index, int serie);

	virtual int GetCount(int serie);


	// TODO: need separate renderer class for rendering cetegory datasets
	XYRenderer *GetRenderer()
	{
		return (XYRenderer *) m_renderer;
	}

protected:
	virtual bool AcceptRenderer(Renderer *r);
};

#endif /*CATEGORYDATASET_H_*/
