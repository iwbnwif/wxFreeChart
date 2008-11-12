
/////////////////////////////////////////////////////////////////////////////
// Name:	axisplot.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef AXISPLOT_H_
#define AXISPLOT_H_

#include <wx/plot.h>
#include <wx/axis/axis.h>

#include <wx/areabackground.h>
#include <wx/legend.h>

/**
 * Base class plots that supports axes.
 */
class AxisPlot : public Plot, public DrawObserver, public DatasetObserver
{
public:
	AxisPlot();
	virtual ~AxisPlot();

	/**
	 * Adds axis to plot.
	 * @param _axis axis to be added
	 */
	void AddAxis(Axis *_axis);

	/**
	 * Adds dataset to plot.
	 * @param dataset dataset to be added
	 */
	void AddDataset(Dataset *dataset);

	/**
	 * Returns dataset count.
	 * @return dataset count
	 */
	int GetDatasetCount();

	/**
	 * Return dataset with index
	 * @param index index of dataset
	 * @return dataset or NULL if index is out of bounds
	 */
	Dataset *GetDataset(int index);

	/**
	 * Links dataset with horizontal axis
	 * @param nData index of dataset
	 * @param nAxis index of horizontal axis
	 */
	void LinkDataHorizontalAxis(int nData, int nAxis);

	/**
	 * Links dataset with vertical axis
	 * @param nData index of dataset
	 * @param nAxis index of vertical axis
	 */
	void LinkDataVerticalAxis(int nData, int nAxis);

	/**
	 * Set whether to draw grid lines.
	 * @param _drawGrid if true - plot will draw grid lines
	 */
	void SetDrawGrid(bool _drawGridVertical, bool _drawGridHorizontal);

	/**
	 * Sets background for data area.
	 * @param _dataBackground background for data area
	 */
	void SetDataBackground(AreaBackground *_dataBackground);

	void SetLegend(Legend *_legend);

	//
	// DrawObserver
	//
	virtual void NeedRedraw(DrawObject *obj);

	//
	// DatasetObserver
	//
	virtual void DatasetChanged(Dataset *dataset);

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

	//virtual bool CheckPlotConfiguration() = 0;

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

	Axis *GetDatasetVerticalAxis(Dataset *dataset)
	{
		return GetDatasetAxis(dataset, true);
	}

	Axis *GetDatasetHorizontalAxis(Dataset *dataset)
	{
		return GetDatasetAxis(dataset, false);
	}

	wxCoord GetAxesExtent(wxDC &dc, Array<Axis, 1> *axes);

private:
	//
	// Plot
	//
	virtual void DrawData(wxDC &dc, wxRect rc);

	virtual bool HasData();

	void DrawAxesArray(Array<Axis, 1> *axes, bool vertical, wxDC &dc, wxRect rc);

	void UpdateAxis(Dataset *dataset = NULL);

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
	 * Draws grid lines.
	 * @param dc device context
	 * @param rcData data area rectangle
	 */
	void DrawGridLines(wxDC &dc, wxRect rcData);


	void DrawDataArea(wxDC &dc, wxRect rcData);

	void DrawLegend(wxDC &dc, wxRect rcLegend);

	/**
	 * TODO deprecated, must be removed.
	 */
	class DataAxisLink
	{
	public:
		DataAxisLink(Dataset *_dataset, Axis *_axis)
		{
			dataset = _dataset;
			axis = _axis;
		}

		~DataAxisLink()
		{

		}

		Dataset *dataset;
		Axis *axis;
	};

	bool m_drawGridVertical;
	bool m_drawGridHorizontal;

	Array<Axis, 1> m_leftAxes;
	Array<Axis, 1> m_rightAxes;
	Array<Axis, 1> m_topAxes;
	Array<Axis, 1> m_bottomAxes;

	Array<Axis, 1> m_horizontalAxes;
	Array<Axis, 1> m_verticalAxes;

	// TODO deprecated - use Axis::AddDataset
	Array<DataAxisLink, 1> m_links;

	Array<Dataset, 1> m_datasets;
	AreaBackground *m_dataBackground;

	Legend *m_legend;

	//bool m_plotConfigurationOk;
};

#endif /*AXISPLOT_H_*/
