
/////////////////////////////////////////////////////////////////////////////
// Name:	numberaxis.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/numberaxis.h>
#include <wx/xy/xydataset.h>
#include <wx/category/categorydataset.h>

#ifdef WIN32
#include <float.h>

bool IsNormalValue(double v)
{
	switch (_fpclass(v)) {
		case _FPCLASS_SNAN:
		case _FPCLASS_QNAN:
		case _FPCLASS_NINF:
		case _FPCLASS_PINF:
			return false;
		default:
			return true;
	}
}
#else
#include <math.h>

bool IsNormalValue(double v)
{
	switch (fpclassify(v)) {
		case FP_NAN:
		case FP_INFINITE:
		case FP_SUBNORMAL:
			return false;
		default:
			return true;
	}
}

#endif

NumberAxis::NumberAxis(AXIS_LOCATION location)
: LabelAxis(location)
{
	// default values
	m_tickFormat = wxT("%.2f");

	m_minValue = 0;
	m_maxValue = 100;

	m_minorTick = 1;
	m_majorTick = 10;

	m_stepCount = 5;

	m_intValues = false;
	m_hasTicks = false;
	m_fixedBounds = false;
}

NumberAxis::~NumberAxis()
{
}


bool NumberAxis::AcceptDataset(Dataset *dataset)
{
	if (dynamic_cast<ValueRange *>(dataset) != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void NumberAxis::SetFixedBounds(double minValue, double maxValue)
{
	m_minValue = minValue;
	m_maxValue = maxValue;
	m_fixedBounds = true;

	UpdateTickValues();
}

void NumberAxis::UpdateBounds()
{
	if (m_fixedBounds)
		return ; // bounds are fixed, so don't update

	m_hasTicks = false;

	for (int n = 0; n < m_datasets.GetSize(); n++) {
		bool verticalAxis = IsVertical();
		ValueRange *valueDataset = (ValueRange *) m_datasets[n];

		double minValue = valueDataset->GetMinValue(verticalAxis);
		double maxValue = valueDataset->GetMaxValue(verticalAxis);

		if (n == 0) {
			m_minValue = minValue;
			m_maxValue = maxValue;
		}
		else {
			m_minValue = MIN(m_minValue, minValue);
			m_maxValue = MAX(m_maxValue, maxValue);
		}
	}

	UpdateTickValues();
}

void NumberAxis::UpdateTickValues()
{
	m_hasTicks = false;
	m_majorTick = (m_maxValue - m_minValue) / ((double) m_stepCount);

	if (!IsNormalValue(m_majorTick)) {
		// overflow condition bugfix
		m_minValue = 0;
		m_maxValue = 0;
		m_majorTick = 0;
	}
	else {
		if (ABS(m_maxValue - m_minValue) > 0.000000001)
			m_hasTicks = true;
	}
	FireNeedRedraw();
}

wxSize NumberAxis::GetLongestLabelExtent(wxDC &dc)
{
	wxSize sizeMinValue = dc.GetTextExtent(wxString::Format(m_tickFormat, m_minValue));
	wxSize sizeMaxValue = dc.GetTextExtent(wxString::Format(m_tickFormat, m_maxValue));

	if (sizeMinValue.x > sizeMaxValue.x) {
		return sizeMinValue;
	}
	else {
		return sizeMaxValue;
	}
}

wxCoord NumberAxis::DoToGraphics(wxDC &dc, int minG, int range, double value)
{
	wxSize maxTextExtent = GetLongestLabelExtent(dc);

	wxCoord coord;
	double gRange, k;

	double valueRange = m_maxValue - m_minValue;

	if (IsVertical()) {
		coord = minG + maxTextExtent.GetHeight() / 2;
		gRange = range - maxTextExtent.GetHeight();

		k = (m_maxValue - value) / valueRange;
	}
	else {
		coord = minG + maxTextExtent.GetWidth() / 2;
		gRange = range - maxTextExtent.GetWidth();

		k = (value - m_minValue) / valueRange;
	}

	if (gRange < 0)
		gRange = 0;

	return (wxCoord) (k * gRange + coord);
}

double NumberAxis::GetValue(int step)
{
	return m_minValue + step * m_majorTick;
}

void NumberAxis::GetLabel(int step, wxString &label)
{
	double value = GetValue(step);

	if (m_intValues) {
		label = wxString::Format(wxT("%i"), (int) value);
	}
	else {
		label = wxString::Format(m_tickFormat, value);
	}
}

bool NumberAxis::IsEnd(int step)
{
	double value = GetValue(step);
	return value > m_maxValue;
}

bool NumberAxis::HasLabels()
{
	return m_hasTicks;
}
