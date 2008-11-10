
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
	horizontalAxes.NotOwns();
	verticalAxes.NotOwns();

	drawGridVertical = true;
	drawGridHorizontal = true;

	legend = NULL;
	dataBackground = NULL;
	SetDataBackground(new FillAreaBackground());
}

AxisPlot::~AxisPlot()
{
	for (int n = 0; n < datasets.GetSize(); n++) {
		datasets[n]->RemoveObserver(this);
	}

	SAFE_REMOVE_OBSERVER(this, dataBackground);
	SAFE_DELETE(dataBackground);
}

void AxisPlot::SetDataBackground(AreaBackground *_dataBackground)
{
	SAFE_REPLACE_OBSERVER(this, dataBackground, _dataBackground);
	SAFE_REPLACE(dataBackground, _dataBackground);
}

void AxisPlot::AddAxis(Axis *axis)
{
	if (!AcceptAxis(axis)) {
		wxLogError(wxT("AxisPlot::AddAxis: axis unacceptable"));
		return ;
	}

	switch (axis->GetLocation()) {
	case AXIS_LEFT:
		leftAxes.Add(axis);
		verticalAxes.Add(axis);
		break;
	case AXIS_RIGHT:
		rightAxes.Add(axis);
		verticalAxes.Add(axis);
		break;
	case AXIS_TOP:
		topAxes.Add(axis);
		horizontalAxes.Add(axis);
		break;
	case AXIS_BOTTOM:
		bottomAxes.Add(axis);
		horizontalAxes.Add(axis);
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
	return datasets.GetSize() != 0;
}

void AxisPlot::AddDataset(Dataset *dataset)
{
	if (!AcceptDataset(dataset)) {
		wxLogError(wxT("AxisPlot::AddAxis: dataset unacceptable"));
		return ;
	}

	datasets.Add(dataset);
	dataset->AddObserver(this);
	FirePlotNeedRedraw();
}

int AxisPlot::GetDatasetCount()
{
	return datasets.GetSize();
}

Dataset *AxisPlot::GetDataset(int index)
{
	return datasets[index];
}

void AxisPlot::LinkDataHorizontalAxis(int nData, int nAxis)
{
	CHECK_INDEX(wxT("data"), nData, datasets);
	CHECK_INDEX(wxT("horizontal axis"), nAxis, horizontalAxes);

	links.Add(new DataAxisLink(datasets[nData], horizontalAxes[nAxis]));
	horizontalAxes[nAxis]->AddDataset(datasets[nData]);

	UpdateAxis(datasets[nData]);
	FirePlotNeedRedraw();
}

void AxisPlot::LinkDataVerticalAxis(int nData, int nAxis)
{
	CHECK_INDEX(wxT("data"), nData, datasets);
	CHECK_INDEX(wxT("vertical axis"), nAxis, verticalAxes);

	links.Add(new DataAxisLink(datasets[nData], verticalAxes[nAxis]));
	verticalAxes[nAxis]->AddDataset(datasets[nData]);

	UpdateAxis(datasets[nData]);
	FirePlotNeedRedraw();
}

void AxisPlot::SetLegend(Legend *_legend)
{
	SAFE_REPLACE(legend, _legend);
	FirePlotNeedRedraw();
}

void AxisPlot::UpdateAxis(Dataset *dataset)
{
	for (int nLink = 0; nLink < links.GetSize(); nLink++) {
		DataAxisLink *link = links[nLink];

		if (dataset == NULL || link->dataset == dataset) {
			link->axis->UpdateBounds();
		}
	}
}

void AxisPlot::NeedRedraw(DrawObject *obj)
{
	FirePlotNeedRedraw();
}

void AxisPlot::SetDrawGrid(bool _drawGridVertical, bool _drawGridHorizontal)
{
	drawGridVertical = _drawGridVertical;
	drawGridHorizontal = _drawGridHorizontal;

	FirePlotNeedRedraw();
}

void AxisPlot::DrawGridLines(wxDC &dc, wxRect rc)
{
	if (drawGridVertical) {
		for (int nAxis = 0; nAxis < verticalAxes.GetSize(); nAxis++) {
			verticalAxes[nAxis]->DrawGridLines(dc, rc);
		}
	}

	if (drawGridHorizontal) {
		for (int nAxis = 0; nAxis < horizontalAxes.GetSize(); nAxis++) {
			horizontalAxes[nAxis]->DrawGridLines(dc, rc);
		}
	}
}

Axis *AxisPlot::GetDatasetAxis(Dataset *dataset, bool vertical)
{
	// TODO deprecated - don't use DataAxisLink
	for (int nLink = 0; nLink < links.GetSize(); nLink++) {
		DataAxisLink *link = links[nLink];

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

	if (leftAxes.GetSize() != 0) {
		wxCoord ext = CountAxesExtent(dc, &leftAxes);

		rcData.x += ext;
		rcData.width -= ext;
	}
	if (rightAxes.GetSize() != 0) {
		wxCoord ext = CountAxesExtent(dc, &rightAxes);

		rcData.width -= ext;
	}
	if (topAxes.GetSize() != 0) {
		wxCoord ext = CountAxesExtent(dc, &topAxes);

		rcData.y += ext;
		rcData.height -= ext;
	}
	if (bottomAxes.GetSize() != 0) {
		wxCoord ext = CountAxesExtent(dc, &bottomAxes);

		rcData.height -= ext;
	}

	if (legend != NULL) {
		wxSize legendExtent = legend->GetExtent(dc, datasets);

		switch (legend->GetHorizPosition()) {
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


		switch (legend->GetVertPosition()) {
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
	if (leftAxes.GetSize() != 0) {
		wxRect rcLeftAxes(rc.x, rcData.y, (rcData.x - rc.x), rcData.height);
		DrawAxesArray(&leftAxes, true, dc, rcLeftAxes);
	}
	if (rightAxes.GetSize() != 0) {
		wxRect rcRightAxes(rcData.x + rcData.width, rcData.y, (rc.x + rc.width - rcData.x - rcData.width), rcData.height);
		DrawAxesArray(&rightAxes, true, dc, rcRightAxes);
	}
	if (topAxes.GetSize() != 0) {
		wxRect rcTopAxes(rcData.x, rc.y, rcData.width, (rcData.y - rc.y));
		DrawAxesArray(&topAxes, false, dc, rcTopAxes);
	}
	if (bottomAxes.GetSize() != 0) {
		wxRect rcBottomAxes(rcData.x, rcData.y + rcData.height, rcData.width, (rc.y + rc.height - rcData.y - rcData.height));
		DrawAxesArray(&bottomAxes, false, dc, rcBottomAxes);
	}
}

void AxisPlot::DrawLegend(wxDC &dc, wxRect rcLegend)
{
	if (legend != NULL) {
		legend->Draw(dc, rcLegend, datasets);
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

	dataBackground->Draw(dc, rcData);

	DrawAxes(dc, rc, rcData);

	DrawDataArea(dc, rcData);

	DrawLegend(dc, rcLegend);
}
