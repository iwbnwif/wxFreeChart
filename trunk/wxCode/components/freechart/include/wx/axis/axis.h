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

#include <wx/wxfreechartdefs.h>
#include <wx/dataset.h>
#include <wx/array.h>

#include <wx/drawobject.h>
#include <wx/observable.h>

enum AXIS_LOCATION {
	AXIS_LEFT = 1,
	AXIS_RIGHT,
	AXIS_TOP,
	AXIS_BOTTOM,
};

class Axis;

class AxisObserver
{
public:
	AxisObserver();
	virtual ~AxisObserver();

	virtual void AxisChanged(Axis *axis) = 0;

	virtual void BoundsChanged(Axis *axis) = 0;
};

/**
 * Base class for all axes.
 */
class WXDLLEXPORT Axis : public wxObject, public Observable<AxisObserver>
{
	DECLARE_CLASS(Axis)

	friend class Plot;
public:
	/**
	 * Constructs new axis.
	 * @param location axis location (cannot be changed after axis created)
	 */
	Axis(AXIS_LOCATION location);
	virtual ~Axis();

	/**
	 * Returns axis location.
	 * @return axis location
	 */
	AXIS_LOCATION GetLocation()
	{
		return m_location;
	}

	/**
	 * Checks whether axis is vertical.
	 * @return true if axis is vertical, false - overwise
	 */
	bool IsVertical()
	{
		return (m_location == AXIS_LEFT) || (m_location == AXIS_RIGHT);
	}

	/**
	 * Checks whether axis is horizontal.
	 * @return true if axis is horizontal, false - overwise
	 */
	bool IsHorizontal()
	{
		return !IsVertical();
	}

	//
	// Window functions.
	//

	void SetWindowWidth(double winWidth)
	{
		if (m_winWidth != winWidth) {
			m_winWidth = winWidth;
			FireAxisChanged();
		}
	}

	double GetWindowWidth()
	{
		return m_winWidth;
	}

	void SetWindowPosition(double winPos)
	{
		if (m_winPos != winPos) {
			double minValue, maxValue;
			GetDataBounds(minValue, maxValue);

			m_winPos = wxClip(winPos, minValue, maxValue - m_winWidth);

			FireAxisChanged();
		}
	}

	double GetWindowPosition()
	{
		return m_winPos;
	}

	void SetUseWindow(bool useWin)
	{
		if (m_useWin != useWin) {
			m_useWin = useWin;
			FireAxisChanged();
		}
	}

	void SetWindow(double winPos, double winWidth)
	{
		m_winPos = winPos;
		m_winWidth = winWidth;
		FireAxisChanged();
	}

	bool IntersectsWindow(double v0, double v1);

	/**
	 * internal. Don't use from programs.
	 */
	void AddDataset(Dataset *dataset)
	{
		if (AcceptDataset(dataset)) {
			m_datasets.Add(dataset);
		}
	}

	/**
	 * Returns data bounds.
	 * @param minValue output minimal data value
	 * @param maxValue output maximal data value
	 */
	virtual void GetDataBounds(double &minValue, double &maxValue) = 0;

	/**
	 * Used to determine minimal size needed to draw axis contents,
	 * minimal width for vertical axes, minimal height for horizontal.
	 * @return extent
	 */
	virtual wxCoord GetExtent(wxDC &dc) = 0;

	/**
	 * Checks whether data value is visible.
	 * @param value value in data space
	 * @return true if data value is visible
	 */
	virtual bool IsVisible(double value);

	/**
	 * Returns nearest boundary value.
	 * @param value out of bounds value, for which will be returned boundary value
	 * @return nearest boundary value
	 */
	virtual double BoundValue(double value);

	/**
	 * Transforms coordinate from data space to graphics space.
	 * @param dc device context
	 * @param minCoord minimal graphics space coordinate
	 * @param gRange graphics space range
	 * @param value value in data space
	 * @return value in graphics space
	 */
	virtual wxCoord ToGraphics(wxDC &dc, int minCoord, int gRange, double value) = 0;

	/**
	 * Transforms coordinate from graphics space to data space.
	 * @param dc device context
	 * @param minCoord minimal graphics space coordinate
	 * @param gRange graphics space range
	 * @param value value in data space
	 * @return coordinate in data space
	 */
	virtual double ToData(wxDC &dc, int minCoord, int gRange, wxCoord g) = 0;

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

protected:
	/**
	 * Checks whether dataset can be accepted by this axis.
	 * Must be implemented by derivative classes.
	 * XXX: maybe remove this method later.
	 * @param dataset dataset to be checked
	 * @return true - if dataset can be accepted, false overwise
	 */
	virtual bool AcceptDataset(Dataset *dataset) = 0;

	Array<Dataset, 1, true> m_datasets;
	wxPen m_gridLinesPen;

	double m_winPos;
	double m_winWidth;
	bool m_useWin;

	FIRE_WITH_THIS(AxisChanged);
	FIRE_WITH_THIS(BoundsChanged);

private:
	AXIS_LOCATION m_location;
};

#endif /*AXIS_H_*/
