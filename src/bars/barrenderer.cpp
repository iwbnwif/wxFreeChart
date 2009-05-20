/////////////////////////////////////////////////////////////////////////////
// Name:	barrenderer.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	14.11.2008
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/bars/barrenderer.h"
#include "wx/category/categorydataset.h"

BarType::BarType()
{
}

BarType::~BarType()
{
}

void BarType::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, int item, CategoryDataset *dataset)
{
	FOREACH_SERIE(serie, dataset) {
		int width;
		wxCoord shift;
		double base, value;

		GetBar(item, serie, dataset, width, shift, base, value);

		double xBase, yBase;
		double xVal, yVal;

		if (vertical) {
			xBase = xVal = item;
			yBase = base;
			yVal = value;
		}
		else {
			xBase = base;
			yBase = yVal = item;
			xVal = value;
		}

		wxCoord xb = horizAxis->ToGraphics(dc, rc.x, rc.width, xBase);
		wxCoord yb = vertAxis->ToGraphics(dc, rc.y, rc.height, yBase);
		wxCoord x = horizAxis->ToGraphics(dc, rc.x, rc.width, xVal);
		wxCoord y = vertAxis->ToGraphics(dc, rc.y, rc.height, yVal);

		wxRect rcBar;
		if (vertical) {
			xb += shift;
			x += shift;

			rcBar.x = wxMin(xb, x);
			rcBar.y = wxMin(yb, y);
			rcBar.width = width;
			rcBar.height = ABS(yb - y);
		}
		else {
			yb += shift;
			y += shift;

			rcBar.x = wxMin(xb, x);
			rcBar.y = wxMin(yb, y);
			rcBar.width = ABS(xb - x);
			rcBar.height = width;
		}

		AreaDraw *barDraw = m_barDraws.GetAreaDraw(serie);
		barDraw->Draw(dc, rcBar);
	}
}

double BarType::GetMinValue(CategoryDataset *dataset)
{
	if (dataset->GetCount() == 0)
		return 0;

	double minValue = dataset->GetValue(0, 0);

	FOREACH_SERIE(serie, dataset) {
		for (int n = 0; n < dataset->GetCount(); n++) {
			minValue = wxMin(minValue, dataset->GetValue(n, serie));
		}
	}
	return wxMin(minValue, m_base);
}

double BarType::GetMaxValue(CategoryDataset *dataset)
{
	if (dataset->GetCount() == 0)
		return 0;

	double maxValue = dataset->GetValue(0, 0);

	FOREACH_SERIE(serie, dataset) {
		for (int n = 0; n < dataset->GetCount(); n++) {
			maxValue = wxMax(maxValue, dataset->GetValue(n, serie));
		}
	}
	return maxValue;
}

NormalBarType::NormalBarType(int barWidth, int serieGap, double base)
{
	m_barWidth = barWidth;
	m_serieGap = serieGap;
	m_base = base;
}

NormalBarType::~NormalBarType()
{
}

void NormalBarType::GetBar(int item, int serie, CategoryDataset *dataset, int &width, wxCoord &shift, double &base, double &value)
{
	width = m_barWidth;

	const int serieCount = dataset->GetSerieCount();
	if (serieCount > 1) {
		shift = serie * (m_barWidth + m_serieGap) - (m_serieGap * (serieCount - 1) + m_barWidth);
	}
	else {
		shift = -m_barWidth / 2;
	}

	base = m_base;
	value = dataset->GetValue(item, serie);
}

StackedBarType::StackedBarType(int barWidth, double base)
{
	m_barWidth = barWidth;
	m_base = base;
}

StackedBarType::~StackedBarType()
{
}

void StackedBarType::GetBar(int item, int serie, CategoryDataset *dataset, int &width, wxCoord &shift, double &base, double &value)
{
	width = m_barWidth;
	shift = -m_barWidth / 2;
	base = (serie >= 1) ? dataset->GetValue(item, serie - 1) : m_base;
	value = dataset->GetValue(item, serie);
	if (serie >= 1) {
		value += base;
	}
}

double StackedBarType::GetMinValue(CategoryDataset *dataset)
{
	return m_base;
}

double StackedBarType::GetMaxValue(CategoryDataset *dataset)
{
	if (dataset->GetCount() == 0)
		return 0;

	double maxValue = 0;

	for (int n = 0; n < dataset->GetCount(); n++) {
		double sum = m_base;

		FOREACH_SERIE(serie, dataset) {
			sum += dataset->GetValue(n, serie);
		}
		maxValue = wxMax(maxValue, sum);
	}
	return maxValue;
}

LayeredBarType::LayeredBarType(int initialBarWidth,double base)
{
	m_initialBarWidth = initialBarWidth;
	m_base = base;
}

LayeredBarType::~LayeredBarType()
{
}

void LayeredBarType::GetBar(int item, int serie, CategoryDataset *dataset, int &width, wxCoord &shift, double &base, double &value)
{
	width = (int) ( m_initialBarWidth * (1 - serie / (double)dataset->GetSerieCount()));
	shift = -width / 2;
	base = m_base;
	value = dataset->GetValue(item, serie);
}

IMPLEMENT_CLASS(BarRenderer, Renderer)

BarRenderer::BarRenderer(BarType *barType)
{
	m_barType = barType;
}

BarRenderer::~BarRenderer()
{
	SAFE_DELETE(m_barType);
}

void BarRenderer::SetBarType(BarType *barType)
{
	SAFE_REPLACE(m_barType, barType);
	FireNeedRedraw();
}

void BarRenderer::Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, CategoryDataset *dataset)
{
	for (int n = 0; n < dataset->GetCount(); n++) {
		m_barType->Draw(dc, rc, horizAxis, vertAxis, vertical, n, dataset);
	}
}

double BarRenderer::GetMinValue(CategoryDataset *dataset)
{
	return m_barType->GetMinValue(dataset);
}

double BarRenderer::GetMaxValue(CategoryDataset *dataset)
{
	return m_barType->GetMaxValue(dataset);
}

