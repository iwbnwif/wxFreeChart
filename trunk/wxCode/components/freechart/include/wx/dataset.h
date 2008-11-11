
/////////////////////////////////////////////////////////////////////////////
// Name:	dataset.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATASET_H_
#define DATASET_H_

#include <wx/wxfreechartdefs.h>

#include <wx/refobject.h>
#include <wx/observable.h>
#include <wx/renderer.h>

class Dataset;

/**
 * Class that receives notifications about dataset changes.
 *
 */
class DatasetObserver
{
public:
	DatasetObserver()
	{
	}

	virtual ~DatasetObserver()
	{
	}

	virtual void DatasetChanged(Dataset *dataset) = 0;
};

/**
 * Base class for all datasets (XYDatasets, CategoryDatasets, OHLCDatasets, etc).
 *
 */
class Dataset : public RefObject, public Observable<DatasetObserver>//, public DrawObjectObserver
{
public:
	Dataset()
	{
		renderer = NULL;
		updating = false;
		changed = false;
	}

	virtual ~Dataset()
	{
		SAFE_UNREF(renderer);
	}

	void SetRenderer(Renderer *_renderer)
	{
		SAFE_REPLACE_UNREF(renderer, _renderer);
		FireDatasetChanged();
	}

	void BeginUpdate()
	{
		updating = true;
	}

	void EndUpdate()
	{
		updating = false;
		FireDatasetChanged();
	}

	/**
	 * Returns serie count in this dataset.
	 * @return serie count
	 */
	virtual int GetSerieCount() = 0;

	/**
	 * Returns value count in serie specified by index.
	 * @param serie index
	 * @return value count
	 */
	virtual int GetCount(int serie) = 0;

	/**
	 * Returns serie name.
	 * @param serie index
	 * @return serie name
	 */
	virtual wxString GetSerieName(int serie) = 0;

protected:
	/**
	 * Checks whether renderer is acceptable by this dataset.
	 * TODO: this method must be removed, because acceptable renderer type depends on plot type.
	 */
	virtual bool AcceptRenderer(Renderer *r) = 0;

	void DatasetChanged()
	{
		if (updating) {
			changed = true;
		}
		else {
			changed = false;
			FireDatasetChanged();
		}
	}

	Renderer *renderer;
	bool updating;
	bool changed;

private:
	FIRE_WITH_THIS(DatasetChanged);
};

/**
 * Single value range.
 */
class ValueRange
{
public:
	ValueRange()
	{
	}

	virtual ~ValueRange()
	{
	}

	virtual double GetMinValue(bool vertical) = 0;

	virtual double GetMaxValue(bool vertical) = 0;
};

#endif /*DATASET_H_*/
