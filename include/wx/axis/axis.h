
/////////////////////////////////////////////////////////////////////////////
// Name:	axis.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef AXIS_H_
#define AXIS_H_

#include <wx/dataset.h>
#include <wx/array.h>

#include <wx/drawobject.h>

enum AXIS_LOCATION {
	AXIS_LEFT = 1,
	AXIS_RIGHT,
	AXIS_TOP,
	AXIS_BOTTOM,
};

/**
 * Base class for all axes.
 */
class Axis : public DrawObject
{
	friend class Plot;
public:
	Axis(AXIS_LOCATION location);
	virtual ~Axis();

	/**
	 * Returns axis location.
	 * @return axis location
	 */
	AXIS_LOCATION GetLocation()
	{
		return location;
	}

	/**
	 * Checks whether axis is vertical.
	 */
	bool IsVertical()
	{
		return (location == AXIS_LEFT) || (location == AXIS_RIGHT);
	}

	/**
	 * Checks whether axis is horizontal.
	 */
	bool IsHorizontal()
	{
		return !IsVertical();
	}

	/**
	 * internal. Don't use from programs.
	 */
	void AddDataset(Dataset *dataset)
	{
		if (AcceptDataset(dataset)) {
			datasets.Add(dataset);
		}
	}

	/**
	 * Sets label for this axis.
	 * @param _label label
	 */
	void SetAxisLabel(wxString _label)
	{
		axisLabel = _label;
		FireNeedRedraw();
	}

	/**
	 * Returns label for this axis.
	 * @return label
	 */
	wxString GetAxisLabel()
	{
		return axisLabel;
	}

	/**
	 * Used to determine minimal size needed to draw axis contents,
	 * minimal width for vertical axes, minimal height for horizontal.
	 * @return extent
	 */
	virtual wxCoord GetExtent(wxDC &dc) = 0;

	/**
	 * Transforms coordinate from data space to graphics space.
	 * @param dc device context
	 * @param minG minimal graphics space coordinate
	 * @param range graphics space range
	 * @param value value in data space
	 * @return value in graphics space
	 */
	virtual wxCoord ToGraphics(wxDC &dc, int minG, int range, double value) = 0;

	/**
	 * Performs axis bounds update after dataset/s change.
	 */
	virtual void UpdateBounds() = 0;

	/**
	 * Performs axis drawing.
	 * @param dc device context
	 * @param rc rectangle where to draw
	 */
	virtual void Draw(wxDC &dc, wxRect rc) = 0;

	/**
	 * Draws grid lines for axis.
	 * @param dc device context
	 * @param rc data area rectangle of plot
	 */
	virtual void DrawGridLines(wxDC &dc, wxRect rcData) = 0;

private:
	AXIS_LOCATION location;

	wxString axisLabel;

protected:
	/**
	 * Checks whether dataset can be accepted by this axis.
	 * Must be implemented by derivative classes.
	 * @param dataset dataset to be checked
	 * @return true - if dataset can be accepted, false overwise
	 */
	virtual bool AcceptDataset(Dataset *dataset) = 0;

	Array<Dataset, 1, true> datasets;

	wxPen gridLinesPen;
};

#endif /*AXIS_H_*/
