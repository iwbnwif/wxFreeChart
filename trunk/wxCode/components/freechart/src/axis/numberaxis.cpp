/////////////////////////////////////////////////////////////////////////////
// Name:	numberaxis.cpp
// Purpose: number axis implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
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

IMPLEMENT_CLASS(NumberAxis, Axis)

NumberAxis::NumberAxis(AXIS_LOCATION location)
: LabelAxis(location)
{
	// default values
	m_tickFormat = wxT("%.2f");

	m_minValue = 0;
	m_maxValue = 100;

	m_labelInterval = 10;
	m_labelCount = 5;

	m_intValues = false;
	m_hasLabels = false;
	m_fixedBounds = false;
}

NumberAxis::~NumberAxis()
{
}


bool NumberAxis::AcceptDataset(Dataset *dataset)
{
	return true;
}

void NumberAxis::SetFixedBounds(double minValue, double maxValue)
{
	m_minValue = minValue;
	m_maxValue = maxValue;
	m_fixedBounds = true;

	UpdateTickValues();
	FireBoundsChanged();
}

void NumberAxis::UpdateBounds()
{
	if (m_fixedBounds) {
		return ; // bounds are fixed, so don't update
	}

	m_hasLabels = false;

	for (int n = 0; n < m_datasets.GetSize(); n++) {
		bool verticalAxis = IsVertical();

		double minValue = m_datasets[n]->GetMinValue(verticalAxis);
		double maxValue = m_datasets[n]->GetMaxValue(verticalAxis);

		if (n == 0) {
			m_minValue = minValue;
			m_maxValue = maxValue;
		}
		else {
			m_minValue = wxMin(m_minValue, minValue);
			m_maxValue = wxMax(m_maxValue, maxValue);
		}
	}

	if (m_minValue == m_maxValue) {
		if (m_maxValue > 0) {
			m_minValue = 0;
		}
		else {
			m_maxValue = 0;
		}
	}

	UpdateTickValues();
	FireBoundsChanged();
}

void NumberAxis::UpdateTickValues()
{
	m_hasLabels = false;
	m_labelInterval = (m_maxValue - m_minValue) / (double) (m_labelCount - 1);

	if (!IsNormalValue(m_labelInterval)) {
		// overflow condition bugfix
		m_minValue = 0;
		m_maxValue = 0;
		m_labelInterval = 0;
	}
	else {
		if (ABS(m_maxValue - m_minValue) > 0.000000001) {
			m_hasLabels = true;
		}
	}
	FireAxisChanged();
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

void NumberAxis::GetDataBounds(double &minValue, double &maxValue)
{
	minValue = m_minValue;
	maxValue = m_maxValue;
}

double NumberAxis::GetValue(int step)
{
	return m_minValue + step * m_labelInterval;
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
	return step >= m_labelCount;
}

bool NumberAxis::HasLabels()
{
	return m_hasLabels;
}
