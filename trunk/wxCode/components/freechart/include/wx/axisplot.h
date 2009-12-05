/////////////////////////////////////////////////////////////////////////////
// Name:	axisplot.h
// Purpose: axis plot declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef AXISPLOT_H_
#define AXISPLOT_H_

#include <wx/plot.h>
#include <wx/axis/axis.h>

#include <wx/areadraw.h>
#include <wx/legend.h>
#include <wx/marker.h>

#include <wx/dynarray.h>

/**
 * Internal class, don't use in programs.
 */
class WXDLLIMPEXP_FREECHART DataAxisLink
{
public:
	DataAxisLink(Dataset *dataset, Axis *axis)
	{
		m_dataset = dataset;
		m_axis = axis;
	}

	DataAxisLink(const DataAxisLink &o)
	{
		m_dataset = o.m_dataset;
		m_axis = o.m_axis;
	}

	~DataAxisLink()
	{
	}

	Dataset *m_dataset;
	Axis *m_axis;
};

WX_DECLARE_EXPORTED_OBJARRAY(DataAxisLink, DataAxisLinkArray);

/**
 * Base class for plots that supports axes.
 */
class WXDLLIMPEXP_FREECHART AxisPlot : public Plot,
public DrawObserver, public DatasetObserver, public AxisObserver
{
public:
	AxisPlot();
	virtual ~AxisPlot();

	/**
	 * Adds axis to plot.
	 * @param axis axis to be added
	 */
	void AddAxis(Axis *axis);

	/**
	 * Adds dataset to plot.
	 * @param dataset dataset to be added
	 */
	void AddDataset(Dataset *dataset);

	/**
	 * Returns dataset count.
	 * @return dataset count
	 */
	size_t GetDatasetCount();

	/**
	 * Return dataset with index
	 * @param index index of dataset
	 * @return dataset or NULL if index is out of bounds
	 */
	Dataset *GetDataset(size_t index);

	/**
	 * Adds marker to plot. Plot takes ownership of marker.
	 * @param marker marker to be added
	 */
	void AddMarker(Marker *marker);

	/**
	 * Links dataset with horizontal axis
	 * @param nData index of dataset
	 * @param nAxis index of horizontal axis
	 */
	void LinkDataHorizontalAxis(size_t nData, size_t nAxis);

	/**
	 * Links dataset with vertical axis
	 * @param nData index of dataset
	 * @param nAxis index of vertical axis
	 */
	void LinkDataVerticalAxis(size_t nData, size_t nAxis);

	/**
	 * Set whether to draw grid lines.
	 * @param drawGridVertical if true - plot will draw vertical grid lines
	 * @param drawGridHorizontal if true - plot will draw horizontal grid lines
	 */
	void SetDrawGrid(bool drawGridVertical, bool drawGridHorizontal);

	/**
	 * Sets background for data area.
	 * @param dataBackground background for data area
	 */
	void SetDataBackground(AreaDraw *dataBackground);

	/**
	 * Sets legend to plot. Plot take ownership of legend.
	 * @param legend new legend for plot
	 */
	void SetLegend(Legend *legend);

	/**
	 * Translate coordinate from graphics to data space.
	 * @param nData number of dataset
	 * @param dc device context
	 * @param rc plot rectangle
	 * @param gx x coordinate in graphics space
	 * @param gy y coordinate in graphics space
	 * @param x output for x coordinate in data space
	 * @param y output for y coordinate in data space
	 * @return true if coordinate was succesfully translated, false - overwise
	 */
	bool ToDataCoords(size_t nData, wxDC &dc, wxRect rc, wxCoord gx, wxCoord gy, double *x, double *y);

	//
	// DrawObserver
	//
	virtual void NeedRedraw(DrawObject *obj);

	//
	// DatasetObserver
	//
	virtual void DatasetChanged(Dataset *dataset);

	//
	// AxisObserver
	//
	virtual void AxisChanged(Axis *axis);

	virtual void BoundsChanged(Axis *axis);

protected:
	//
	// Methods to be implemented by derivative classes
	//

	/**
	 * Checks whether axis is acceptable with this plot.
	 * @param axis axis to be checked
	 * @return true if axis can be accepted, false overwise
	 */
	virtual bool AcceptAxis(Axis *axis) = 0;

	/**
	 * Checks whether dataset is acceptable with this plot.
	 * @param dataset dataset to be checked
	 * @return true if dataset can be accepted, false overwise
	 */
	virtual bool AcceptDataset(Dataset *dataset) = 0;

	virtual void DrawDatasets(wxDC &dc, wxRect rc) = 0;

	/**
	 * Returns main dataset axis.
	 * NOTE: main axis is the first axis linked with dataset.
	 * Main axis is used to scale dataset values.
	 *
	 * @param dataset dataset
	 * @param vertical true if you want to get vertical axis, false - horizontal
	 * @return main axis for dataset or NULL if dataset has no main axis
	 */
	Axis *GetDatasetAxis(Dataset *dataset, bool vertical);

	/**
	 * Returns main vertical dataset axis.
	 * NOTE: main axis is the first axis linked with dataset.
	 * Main axis is used to scale dataset values.
	 * @param dataset dataset
	 * @return main axis for dataset or NULL if dataset has no main axis
	 */
	Axis *GetDatasetVerticalAxis(Dataset *dataset)
	{
		return GetDatasetAxis(dataset, true);
	}

	/**
	 * Returns main horizontal dataset axis.
	 * NOTE: main axis is the first axis linked with dataset.
	 * Main axis is used to scale dataset values.
	 * @param dataset dataset
	 * @return main axis for dataset or NULL if dataset has no main axis
	 */
	Axis *GetDatasetHorizontalAxis(Dataset *dataset)
	{
		return GetDatasetAxis(dataset, false);
	}

	wxCoord GetAxesExtent(wxDC &dc, AxisArray *axes);

private:
	//
	// Plot
	//
	virtual void DrawData(wxDC &dc, wxRect rc);

	virtual bool HasData();


	void UpdateAxis(Dataset *dataset = NULL);

	//
	// Draw functions
	//

	/**
	 * Calculate data area.
	 * @param dc device context
	 * @param rc whole plot rectangle
	 * @param rcData output data area rectangle
	 * @param rcLegent output rectangle for legend
	 */
	void CalcDataArea(wxDC &dc, wxRect rc, wxRect &rcData, wxRect &rcLegend);

	/**
	 * Draws all axes.
	 * @param dc device context
	 * @param rc whole plot rectangle
	 * @param rcData data area rectangle
	 */
	void DrawAxes(wxDC &dc, wxRect &rc, wxRect rcData);

	/**
	 * Draw axes array.
	 * @param dc device context
	 * @param rc rectangle where to draw axes
	 * @param axes axes array
	 * @param vertical true to draw vertical axes, false - horizontal
	 */
	void DrawAxesArray(wxDC &dc, wxRect rc, AxisArray *axes, bool vertical);


	/**
	 * Draws grid lines.
	 * @param dc device context
	 * @param rcData data area rectangle
	 */
	void DrawGridLines(wxDC &dc, wxRect rcData);

	/**
	 * Draws markers.
	 * @param dc device context
	 * @param rcData data area rectangle
	 */
	void DrawMarkers(wxDC &dc, wxRect rcData);

	/**
	 * Draws data.
	 * @param dc device context
	 * @param rcData data area rectangle
	 */
	void DrawDataArea(wxDC &dc, wxRect rcData);

	/**
	 * Draws legend.
	 * @param dc device context
	 * @param rcLegend legend area rectangle
	 */
	void DrawLegend(wxDC &dc, wxRect rcLegend);

	bool m_drawGridVertical;
	bool m_drawGridHorizontal;

	AxisArray m_leftAxes;
	AxisArray m_rightAxes;
	AxisArray m_topAxes;
	AxisArray m_bottomAxes;

	AxisArray m_horizontalAxes;
	AxisArray m_verticalAxes;

	DataAxisLinkArray m_links;

	DatasetArray m_datasets;
	AreaDraw *m_dataBackground; // data area background

	MarkerArray m_markers;

	wxCoord m_legendPlotGap; // distance between plot and legend

	Legend *m_legend;

	//bool m_plotConfigurationOk;
};

#endif /*AXISPLOT_H_*/
