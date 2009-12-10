/////////////////////////////////////////////////////////////////////////////
// Name:	axis.h
// Purpose: axis base class declarations
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef AXIS_H_
#define AXIS_H_

#include <wx/wxfreechartdefs.h>
#include <wx/dataset.h>

#include <wx/dynarray.h>

#include <wx/drawobject.h>
#include <wx/observable.h>

enum AXIS_LOCATION {
	AXIS_LEFT = 1,
	AXIS_RIGHT,
	AXIS_TOP,
	AXIS_BOTTOM,
};

class WXDLLIMPEXP_FREECHART Axis;

/**
 * Interface to receive axis events.
 */
class WXDLLIMPEXP_FREECHART AxisObserver
{
public:
	AxisObserver();
	virtual ~AxisObserver();

	/**
	 * Called when axis is changed.
	 * @param axis changed axis
	 */
	virtual void AxisChanged(Axis *axis) = 0;

	/**
	 * Called when axis bounds are changed.
	 * @param axis axis that bounds are changed
	 */
	virtual void BoundsChanged(Axis *axis) = 0;
};

/**
 * Base class for all axes.
 */
class WXDLLIMPEXP_FREECHART Axis : public wxObject, public Observable<AxisObserver>//, public RefObject
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

	/**
	 * Sets minimal/maximal margins for axis.
	 * Eg bottom/top for vertical axes, left/right for horizontal.
	 * @param marginMin new minimal margin
	 * @param marginMax new maximal margin
	 */
	void SetMargins(wxCoord marginMin, wxCoord marginMax);

	//
	// Dataset functions.
	//
	/**
	 * Returns dataset counts, linked with this axis.
	 * @return dataset counts, linked with this axis
	 */
	size_t GetDatasetCount();

	/**
	 * Returns dataset, linked with this axis at specified index.
	 * @param index dataset index
	 * @return dataset at index
	 */
	Dataset *GetDataset(size_t index);

	//
	// Window functions.
	//

	/**
	 * Sets window width. Window width is in data space.
	 * @param winWidth new window width
	 */
	void SetWindowWidth(double winWidth)
	{
		SetWindow(m_winPos, winWidth);
	}

	/**
	 * Returns window width.
	 * @return window width
	 */
	double GetWindowWidth()
	{
		return m_winWidth;
	}

	/**
	 * Sets window position. Window position is in data space.
	 * @param winPos new window position
	 */
	void SetWindowPosition(double winPos)
	{
		SetWindow(winPos, m_winWidth);
	}

	/**
	 * Returns window position.
	 * @return window position
	 */
	double GetWindowPosition()
	{
		return m_winPos;
	}

	/**
	 * Sets whether to use window.
	 * @param useWin true to use window
	 */
	void SetUseWindow(bool useWin)
	{
		if (m_useWin != useWin) {
			m_useWin = useWin;
			FireAxisChanged();
		}
	}

	/**
	 * Sets window params (position and width). Window params are in data space.
	 * @param winPos new window position
	 * @param winWidth new window width
	 */
	void SetWindow(double winPos, double winWidth)
	{
		if (m_winPos != winPos || m_winWidth != winWidth) {
			m_winPos = winPos;
			m_winWidth = winWidth;
			FireAxisChanged();
		}
	}

	/**
	 * Checks whether line in data space intersects window.
	 * @param v0 line begin in data space
	 * @param v0 line end in data space
	 * @return true if line intersects window
	 */
	bool IntersectsWindow(double v0, double v1);

	/**
	 * Returns window bounds.
	 * If window is not used, simply returns data bounds.
	 * @param winMin out for window minimal
	 * @param winMax out for window maximal
	 */
	void GetWindowBounds(double &winMin, double &winMax)
	{
		double minValue, maxValue;
		GetDataBounds(minValue, maxValue);

		if (m_useWin) {
			winMin = m_winPos;
			winMax = wxMin(maxValue, winMin + m_winWidth);
		}
		else {
			winMin = minValue;
			winMax = maxValue;
		}
	}

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
	 * @param dc device context
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
	virtual wxCoord ToGraphics(wxDC &dc, int minCoord, int gRange, double value);

	/**
	 * Transforms coordinate from graphics space to data space.
	 * @param dc device context
	 * @param minCoord minimal graphics space coordinate
	 * @param gRange graphics space range
	 * @param value value in data space
	 * @return coordinate in data space
	 */
	virtual double ToData(wxDC &dc, int minCoord, int gRange, wxCoord g);

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

	DatasetArray m_datasets;
	wxPen m_gridLinesPen;

	wxCoord m_marginMin;
	wxCoord m_marginMax;

	double m_winPos;
	double m_winWidth;
	bool m_useWin;

	FIRE_WITH_THIS(AxisChanged);
	FIRE_WITH_THIS(BoundsChanged);

private:
	AXIS_LOCATION m_location;
};

WX_DECLARE_EXPORTED_OBJARRAY(Axis *, AxisArray);

wxCoord ToGraphics(int minCoord, int gRange, double minValue, double maxValue, wxCoord margin, bool vertical, double value);
double ToData(int minCoord, int gRange, double minValue, double maxValue, wxCoord margin, bool vertical, wxCoord g);

#endif /*AXIS_H_*/
