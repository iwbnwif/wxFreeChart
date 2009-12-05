/////////////////////////////////////////////////////////////////////////////
// Name:	axisplot.cpp
// Purpose: axis plot implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axisplot.h>
#include <wx/drawutils.h>

#include "wx/arrimpl.cpp"

WX_DEFINE_EXPORTED_OBJARRAY(DataAxisLinkArray)


#define CHECK_INDEX(name, index, v) do {											\
	if (index >= v.Count()) {														\
		wxLogError(wxT("%s index out of bounds: %i %i"), name, index, v.Count());	\
		return ;																	\
	}																				\
} while (0)


AxisPlot::AxisPlot()
{
	m_legendPlotGap = 2;

	m_drawGridVertical = true;
	m_drawGridHorizontal = true;

	m_legend = NULL;
	m_dataBackground = NULL;
	SetDataBackground(new FillAreaDraw());
}

AxisPlot::~AxisPlot()
{
	for (size_t n = 0; n < m_datasets.Count(); n++) {
		Dataset *dataset = m_datasets[n];
		dataset->RemoveObserver(this);
	}

	for (size_t n = 0; n < m_horizontalAxes.Count(); n++) {
		Axis *axis = m_horizontalAxes[n];
		wxDELETE(axis);
	}

	for (size_t n = 0; n < m_verticalAxes.Count(); n++) {
		Axis *axis = m_verticalAxes[n];
		wxDELETE(axis);
	}

	for (size_t n = 0; n < m_markers.Count(); n++) {
		Marker *marker = m_markers[n];
		wxDELETE(marker);
	}

	SAFE_REMOVE_OBSERVER(this, m_dataBackground);
	wxDELETE(m_dataBackground);

	wxDELETE(m_legend);
}

void AxisPlot::SetDataBackground(AreaDraw *dataBackground)
{
	SAFE_REPLACE_OBSERVER(this, m_dataBackground, dataBackground);
	wxREPLACE(m_dataBackground, dataBackground);
}

void AxisPlot::AddAxis(Axis *axis)
{
	if (!AcceptAxis(axis)) {
		wxLogError(wxT("AxisPlot::AddAxis: axis unacceptable"));
		return ;
	}

	switch (axis->GetLocation()) {
	case AXIS_LEFT:
		m_leftAxes.Add(axis);
		m_verticalAxes.Add(axis);
		break;
	case AXIS_RIGHT:
		m_rightAxes.Add(axis);
		m_verticalAxes.Add(axis);
		break;
	case AXIS_TOP:
		m_topAxes.Add(axis);
		m_horizontalAxes.Add(axis);
		break;
	case AXIS_BOTTOM:
		m_bottomAxes.Add(axis);
		m_horizontalAxes.Add(axis);
		break;
	default:
		// BUG!
		wxLogError(wxT("AxisPlot::AddAxis: invalid location value %i"), axis->GetLocation());
		return ;
	}

	axis->AddObserver(this);
}

bool AxisPlot::HasData()
{
	return m_datasets.Count() != 0;
}

void AxisPlot::AddDataset(Dataset *dataset)
{
	if (!AcceptDataset(dataset)) {
		wxLogError(wxT("AxisPlot::AddAxis: dataset unacceptable"));
		return ;
	}

	m_datasets.Add(dataset);
	dataset->AddObserver(this);
	//dataset->AddRef();
	FirePlotNeedRedraw();
}

size_t AxisPlot::GetDatasetCount()
{
	return m_datasets.Count();
}

Dataset *AxisPlot::GetDataset(size_t index)
{
	return m_datasets[index];
}

void AxisPlot::AddMarker(Marker *marker)
{
	m_markers.Add(marker);
}

void AxisPlot::LinkDataHorizontalAxis(size_t nData, size_t nAxis)
{
	CHECK_INDEX(wxT("data"), nData, m_datasets);
	CHECK_INDEX(wxT("horizontal axis"), nAxis, m_horizontalAxes);

	m_links.Add(new DataAxisLink(m_datasets[nData], m_horizontalAxes[nAxis]));
	m_horizontalAxes[nAxis]->AddDataset(m_datasets[nData]);

	//UpdateAxis(m_datasets[nData]);
	m_horizontalAxes[nAxis]->UpdateBounds();

	// redundant
	//FirePlotNeedRedraw();
}

void AxisPlot::LinkDataVerticalAxis(size_t nData, size_t nAxis)
{
	CHECK_INDEX(wxT("data"), nData, m_datasets);
	CHECK_INDEX(wxT("vertical axis"), nAxis, m_verticalAxes);

	m_links.Add(new DataAxisLink(m_datasets[nData], m_verticalAxes[nAxis]));
	m_verticalAxes[nAxis]->AddDataset(m_datasets[nData]);

	//UpdateAxis(m_datasets[nData]);
	m_verticalAxes[nAxis]->UpdateBounds();

	// redundant
	//FirePlotNeedRedraw();
}

void AxisPlot::SetLegend(Legend *legend)
{
	wxREPLACE(m_legend, legend);
	FirePlotNeedRedraw();
}

void AxisPlot::UpdateAxis(Dataset *dataset)
{
	for (size_t nLink = 0; nLink < m_links.Count(); nLink++) {
		DataAxisLink &link = m_links[nLink];

		if (dataset == NULL || link.m_dataset == dataset) {
			link.m_axis->UpdateBounds();
		}
	}
}

void AxisPlot::SetDrawGrid(bool drawGridVertical, bool drawGridHorizontal)
{
	m_drawGridVertical = drawGridVertical;
	m_drawGridHorizontal = drawGridHorizontal;

	FirePlotNeedRedraw();
}

void AxisPlot::DrawGridLines(wxDC &dc, wxRect rc)
{
	if (m_drawGridVertical) {
		for (size_t nAxis = 0; nAxis < m_verticalAxes.Count(); nAxis++) {
			m_verticalAxes[nAxis]->DrawGridLines(dc, rc);
		}
	}

	if (m_drawGridHorizontal) {
		for (size_t nAxis = 0; nAxis < m_horizontalAxes.Count(); nAxis++) {
			m_horizontalAxes[nAxis]->DrawGridLines(dc, rc);
		}
	}
}

Axis *AxisPlot::GetDatasetAxis(Dataset *dataset, bool vertical)
{
	for (size_t nLink = 0; nLink < m_links.Count(); nLink++) {
		DataAxisLink &link = m_links[nLink];

		if (link.m_dataset == dataset) {
			if (vertical == link.m_axis->IsVertical()) {
				return link.m_axis;
			}
		}
	}
	return NULL; // not found
}

void AxisPlot::NeedRedraw(DrawObject *WXUNUSED(obj))
{
	FirePlotNeedRedraw();
}

void AxisPlot::DatasetChanged(Dataset *dataset)
{
	UpdateAxis(dataset);
	FirePlotNeedRedraw();
}

void AxisPlot::AxisChanged(Axis *WXUNUSED(axis))
{
	FirePlotNeedRedraw();
}

void AxisPlot::BoundsChanged(Axis *WXUNUSED(axis))
{
	FirePlotNeedRedraw();
}

wxCoord AxisPlot::GetAxesExtent(wxDC &dc, AxisArray *axes)
{
	wxCoord ext = 0;
	for (size_t nAxis = 0; nAxis < axes->Count(); nAxis++) {
		ext += (*axes)[nAxis]->GetExtent(dc);
	}
	return ext;
}

bool AxisPlot::ToDataCoords(size_t nData, wxDC &dc, wxRect rc, wxCoord gx, wxCoord gy, double *x, double *y)
{
	Dataset *dataset = GetDataset(nData);
	wxCHECK_MSG(dataset != NULL, false, wxT("AxisPlot::ToDataCoords: Invalid dataset index"));

	Axis *horizAxis = GetDatasetHorizontalAxis(dataset);
	Axis *vertAxis = GetDatasetVerticalAxis(dataset);

	wxCHECK_MSG(horizAxis != NULL && vertAxis != NULL, false, wxT("AxisPlot::ToDataCoords: dataset not linked with horizontal or vertical axis"));

	wxRect rcData;
	wxRect rcLegend;

	CalcDataArea(dc, rc, rcData, rcLegend);
	if (!rcData.Contains(gx, gy)) {
		return false;
	}

	*x = horizAxis->ToData(dc, rcData.x, rcData.width, gx);
	*y = vertAxis->ToData(dc, rcData.y, rcData.height, gy);
	return true;
}

void AxisPlot::CalcDataArea(wxDC &dc, wxRect rc, wxRect &rcData, wxRect &rcLegend)
{
	if (m_legend != NULL) {
		wxSize legendExtent = m_legend->GetExtent(dc, m_datasets);

		switch (m_legend->GetHorizPosition()) {
		case wxLEFT:
			rcLegend.x = rc.x;

			rc.x += legendExtent.x + m_legendPlotGap;
			rc.width -= legendExtent.x + m_legendPlotGap;
			break;
		case wxRIGHT:
			rcLegend.x = rc.x + rc.width - legendExtent.x + m_legendPlotGap;

			rc.width -= legendExtent.x + m_legendPlotGap;
			break;
		case wxCENTER:
			rcLegend.x = rc.x + rc.width / 2 - legendExtent.x / 2;
			break;
		default:
			//(wxT("Invalid legend horizontal position"));
			return ;
		}

		switch (m_legend->GetVertPosition()) {
		case wxTOP:
			rcLegend.y = rc.y;

			rc.y += legendExtent.y + m_legendPlotGap;
			rc.height -= legendExtent.y + m_legendPlotGap;
			break;
		case wxBOTTOM:
			rcLegend.y = rc.y + rc.height - legendExtent.y + m_legendPlotGap;

			rc.height -= legendExtent.y + m_legendPlotGap;
			break;
		case wxCENTER:
			rcLegend.y = rc.y + rc.height / 2 - legendExtent.y / 2;
			break;
		default:
			//(wxT("Invalid legend vertical position"));
			return;
		}

		rcLegend.width = legendExtent.x;
		rcLegend.height = legendExtent.y;

		CheckFixRect(rcLegend);
	}

	rcData = rc;

	// substract axes areas from data rectangle
	if (m_leftAxes.Count() != 0) {
		wxCoord ext = GetAxesExtent(dc, &m_leftAxes);

		rcData.x += ext;
		rcData.width -= ext;
	}
	if (m_rightAxes.Count() != 0) {
		wxCoord ext = GetAxesExtent(dc, &m_rightAxes);

		rcData.width -= ext;
	}
	if (m_topAxes.Count() != 0) {
		wxCoord ext = GetAxesExtent(dc, &m_topAxes);

		rcData.y += ext;
		rcData.height -= ext;
	}
	if (m_bottomAxes.Count() != 0) {
		wxCoord ext = GetAxesExtent(dc, &m_bottomAxes);

		rcData.height -= ext;
	}

	CheckFixRect(rcData);
}

void AxisPlot::DrawAxesArray(wxDC &dc, wxRect rc, AxisArray *axes, bool vertical)
{
	wxRect rcAxis(rc);

	for (size_t nAxis = 0; nAxis < axes->Count(); nAxis++) {
		Axis *axis = (*axes)[nAxis];
		wxCoord ext = axis->GetExtent(dc);

		if (vertical) {
			rcAxis.width = ext;
		}
		else {
			rcAxis.height = ext;
		}

		axis->Draw(dc, rcAxis);

		if (vertical) {
			rcAxis.x += ext;
		}
		else {
			rcAxis.y += ext;
		}
	}
}

void AxisPlot::DrawAxes(wxDC &dc, wxRect &rc, wxRect rcData)
{
	if (m_leftAxes.Count() != 0) {
		wxRect rcLeftAxes(rc.x, rcData.y, (rcData.x - rc.x), rcData.height);
		DrawAxesArray(dc, rcLeftAxes, &m_leftAxes, true);
	}
	if (m_rightAxes.Count() != 0) {
		wxRect rcRightAxes(rcData.x + rcData.width - 1, rcData.y, (rc.x + rc.width - rcData.x - rcData.width - 1), rcData.height);
		DrawAxesArray(dc, rcRightAxes, &m_rightAxes, true);
	}
	if (m_topAxes.Count() != 0) {
		wxRect rcTopAxes(rcData.x, rc.y, rcData.width, (rcData.y - rc.y));
		//wxRect rcTopAxes(rcData.x, rc.y + 2, rcData.width, (rcData.y - rc.y + 2));
		DrawAxesArray(dc, rcTopAxes, &m_topAxes, false);
	}
	if (m_bottomAxes.Count() != 0) {
		wxRect rcBottomAxes(rcData.x, rcData.y + rcData.height - 1, rcData.width, (rc.y + rc.height - rcData.y - rcData.height - 1));
		DrawAxesArray(dc, rcBottomAxes, &m_bottomAxes, false);
	}
}

void AxisPlot::DrawMarkers(wxDC &dc, wxRect rcData)
{
	for (size_t n = 0; n < m_markers.Count(); n++) {
		// TODO not implemented!
	}
}

void AxisPlot::DrawLegend(wxDC &dc, wxRect rcLegend)
{
	if (m_legend != NULL) {
		m_legend->Draw(dc, rcLegend, m_datasets);
	}
}

void AxisPlot::DrawDataArea(wxDC &dc, wxRect rcData)
{
	wxRect clipRc = rcData;
	clipRc.Deflate(1, 1);
	wxDCClipper clip(dc, clipRc);

	DrawGridLines(dc, rcData);
	DrawMarkers(dc, rcData);
	DrawDatasets(dc, rcData);
}

void AxisPlot::DrawData(wxDC &dc, wxRect rc)
{
	wxRect rcData;
	wxRect rcLegend;

	CalcDataArea(dc, rc, rcData, rcLegend);

	m_dataBackground->Draw(dc, rcData);

	DrawAxes(dc, rc, rcData);

	DrawDataArea(dc, rcData);

	DrawLegend(dc, rcLegend);
}
