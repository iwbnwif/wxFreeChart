
/////////////////////////////////////////////////////////////////////////////
// Name:	axisplot.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axisplot.h>
#include <wx/drawutils.h>

#define CHECK_INDEX(name, index, v) do {											\
	if (index >= (int) v.GetSize()) {												\
		wxLogError(wxT("%s index out of bounds: %i %i"), name, index, v.GetSize());	\
		return ;																	\
	}																				\
} while (0)


AxisPlot::AxisPlot()
{
	m_horizontalAxes.NotOwns();
	m_verticalAxes.NotOwns();

	m_drawGridVertical = true;
	m_drawGridHorizontal = true;

	m_legend = NULL;
	m_dataBackground = NULL;
	SetDataBackground(new FillAreaBackground());
}

AxisPlot::~AxisPlot()
{
	for (int n = 0; n < m_datasets.GetSize(); n++) {
		m_datasets[n]->RemoveObserver(this);
	}

	SAFE_REMOVE_OBSERVER(this, m_dataBackground);
	SAFE_DELETE(m_dataBackground);
}

void AxisPlot::SetDataBackground(AreaBackground *dataBackground)
{
	SAFE_REPLACE_OBSERVER(this, m_dataBackground, dataBackground);
	SAFE_REPLACE(m_dataBackground, dataBackground);
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
	return m_datasets.GetSize() != 0;
}

void AxisPlot::AddDataset(Dataset *dataset)
{
	if (!AcceptDataset(dataset)) {
		wxLogError(wxT("AxisPlot::AddAxis: dataset unacceptable"));
		return ;
	}

	m_datasets.Add(dataset);
	dataset->AddObserver(this);
	FirePlotNeedRedraw();
}

int AxisPlot::GetDatasetCount()
{
	return m_datasets.GetSize();
}

Dataset *AxisPlot::GetDataset(int index)
{
	return m_datasets[index];
}

void AxisPlot::LinkDataHorizontalAxis(int nData, int nAxis)
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

void AxisPlot::LinkDataVerticalAxis(int nData, int nAxis)
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
	SAFE_REPLACE(m_legend, legend);
	FirePlotNeedRedraw();
}

void AxisPlot::UpdateAxis(Dataset *dataset)
{
	for (int nLink = 0; nLink < m_links.GetSize(); nLink++) {
		DataAxisLink *link = m_links[nLink];

		if (dataset == NULL || link->dataset == dataset) {
			link->axis->UpdateBounds();
		}
	}
}

void AxisPlot::NeedRedraw(DrawObject *obj)
{
	FirePlotNeedRedraw();
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
		for (int nAxis = 0; nAxis < m_verticalAxes.GetSize(); nAxis++) {
			m_verticalAxes[nAxis]->DrawGridLines(dc, rc);
		}
	}

	if (m_drawGridHorizontal) {
		for (int nAxis = 0; nAxis < m_horizontalAxes.GetSize(); nAxis++) {
			m_horizontalAxes[nAxis]->DrawGridLines(dc, rc);
		}
	}
}

Axis *AxisPlot::GetDatasetAxis(Dataset *dataset, bool vertical)
{
	// TODO deprecated - don't use DataAxisLink
	for (int nLink = 0; nLink < m_links.GetSize(); nLink++) {
		DataAxisLink *link = m_links[nLink];

		if (link->dataset == dataset) {
			if (vertical == link->axis->IsVertical()) {
				return link->axis;
			}
		}
	}
	return NULL; // not found
}

void AxisPlot::DatasetChanged(Dataset *dataset)
{
	UpdateAxis(dataset);
	FirePlotNeedRedraw();
}

wxCoord AxisPlot::CountAxesExtent(wxDC &dc, Array<Axis, 1> *axes)
{
	wxCoord ext = 0;
	for (int nAxis = 0; nAxis < axes->GetSize(); nAxis++) {
		ext += (*axes)[nAxis]->GetExtent(dc);
	}
	return ext;
}

void AxisPlot::CalcDataArea(wxDC &dc, wxRect rc, wxRect &rcData, wxRect &rcLegend)
{
	rcData = rc;

	if (m_leftAxes.GetSize() != 0) {
		wxCoord ext = CountAxesExtent(dc, &m_leftAxes);

		rcData.x += ext;
		rcData.width -= ext;
	}
	if (m_rightAxes.GetSize() != 0) {
		wxCoord ext = CountAxesExtent(dc, &m_rightAxes);

		rcData.width -= ext;
	}
	if (m_topAxes.GetSize() != 0) {
		wxCoord ext = CountAxesExtent(dc, &m_topAxes);

		rcData.y += ext;
		rcData.height -= ext;
	}
	if (m_bottomAxes.GetSize() != 0) {
		wxCoord ext = CountAxesExtent(dc, &m_bottomAxes);

		rcData.height -= ext;
	}

	if (m_legend != NULL) {
		wxSize legendExtent = m_legend->GetExtent(dc, m_datasets);

		switch (m_legend->GetHorizPosition()) {
		case wxLEFT:
			rcLegend.x = rcData.x;

			rcData.x += legendExtent.x;
			rcData.width -= legendExtent.x;
			break;
		case wxRIGHT:
			rcLegend.x = rcData.x + rcData.width - legendExtent.x;

			rcData.width -= legendExtent.x;
			break;
		case wxCENTER:
			rcLegend.x = rcData.x + rcData.width / 2 - legendExtent.x / 2;
			break;
		default:
			//(wxT("Invalid legend horizontal position"));
			return ;
		}


		switch (m_legend->GetVertPosition()) {
		case wxTOP:
			rcLegend.y = rcData.y;

			rcData.y += legendExtent.y;
			rcData.height -= legendExtent.y;
			break;
		case wxBOTTOM:
			rcLegend.y = rcData.y + rcData.height - legendExtent.y;

			rcData.height -= legendExtent.y;
			break;
		case wxCENTER:
			rcLegend.y = rcData.y + rcData.height / 2 - legendExtent.y / 2;
			break;
		default:
			//(wxT("Invalid legend vertical position"));
			return;
		}

		rcLegend.width = legendExtent.x;
		rcLegend.height = legendExtent.y;

		CheckFixRect(rcLegend);
	}

	CheckFixRect(rcData);
}

void AxisPlot::DrawAxesArray(Array<Axis, 1> *axes, bool vertical, wxDC &dc, wxRect rc)
{
	wxRect rcAxis(rc);

	for (int nAxis = 0; nAxis < axes->GetSize(); nAxis++) {
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
	if (m_leftAxes.GetSize() != 0) {
		wxRect rcLeftAxes(rc.x, rcData.y, (rcData.x - rc.x), rcData.height);
		DrawAxesArray(&m_leftAxes, true, dc, rcLeftAxes);
	}
	if (m_rightAxes.GetSize() != 0) {
		wxRect rcRightAxes(rcData.x + rcData.width, rcData.y, (rc.x + rc.width - rcData.x - rcData.width), rcData.height);
		DrawAxesArray(&m_rightAxes, true, dc, rcRightAxes);
	}
	if (m_topAxes.GetSize() != 0) {
		wxRect rcTopAxes(rcData.x, rc.y, rcData.width, (rcData.y - rc.y));
		DrawAxesArray(&m_topAxes, false, dc, rcTopAxes);
	}
	if (m_bottomAxes.GetSize() != 0) {
		wxRect rcBottomAxes(rcData.x, rcData.y + rcData.height, rcData.width, (rc.y + rc.height - rcData.y - rcData.height));
		DrawAxesArray(&m_bottomAxes, false, dc, rcBottomAxes);
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
	wxDCClipper clip(dc, rcData);

	DrawGridLines(dc, rcData);
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
