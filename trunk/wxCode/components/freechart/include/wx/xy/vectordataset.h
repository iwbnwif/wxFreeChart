
/////////////////////////////////////////////////////////////////////////////
// Name:	vectordataset.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef VECTORDATASET_H_
#define VECTORDATASET_H_

#include <wx/xy/xydataset.h>
#include <vector>

/**
 * Vector implementation of XYDataset.
 * Allows y data addition and removal.
 * Can be in auto or manual update mode.
 *
 * X values is the index (0....Count)
 */
class VectorDataset : public XYDataset
{
public:
	/**
	 * Construct new VectorDataset instance.
	 * @param _name name of dataset
	 * @param autoUpdate if true any changes in data will fire dataset updated event
	 */
	VectorDataset();
	virtual ~VectorDataset();

	virtual double GetX(int index);

	virtual double GetY(int index);

	virtual int GetCount();

	/**
	 * Adds y values to dataset.
	 * @param y y value
	 */
	void Add(double y)
	{
		values.push_back(y);
		DatasetChanged();
	}

	void Replace(unsigned int index, double y)
	{
		if (index < values.size()) {
			values.erase(values.begin() + index);
			values.insert(values.begin() + index, y);

			DatasetChanged();
		}
	}

	void RemoveAt(unsigned int index)
	{
		if (index < values.size()) {
			values.erase(values.begin() + index);

			DatasetChanged();
		}
	}

	/**
	 * Removes all values from dataset.
	 */
	void Clear()
	{
		values.clear();
		DatasetChanged();
	}

private:
	std::vector<double> values;
};

#endif /*VECTORDATASET_H_*/
