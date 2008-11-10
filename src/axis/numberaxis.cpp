
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
	tickFormat = wxT("%.2f");

	minValue = 0;
	maxValue = 100;

	minorTick = 1;
	majorTick = 10;

	intValues = false;
	hasTicks = false;
	fixedBounds = false;
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

void NumberAxis::FixedBounds(double _minValue, double _maxValue)
{
	minValue = _minValue;
	maxValue = _maxValue;

	majorTick = (maxValue - minValue) / 5.0; //XXX temporary TODO if using intValues - make integer step
	hasTicks = true;
	fixedBounds = true;

	FireNeedRedraw();
}

void NumberAxis::UpdateBounds()
{
	if (fixedBounds)
		return ; // bounds are fixed, so don't update

	hasTicks = false;

	for (int n = 0; n < datasets.GetSize(); n++) {
		Dataset *dataset = datasets[n];
		double _minValue, _maxValue;

		bool verticalAxis = IsVertical();
		if (dynamic_cast<ValueRange *>(dataset) != NULL) {
			ValueRange *valueDataset = dynamic_cast<ValueRange *>(dataset);

			_minValue = valueDataset->GetMinValue(verticalAxis);
			_maxValue = valueDataset->GetMaxValue(verticalAxis);
		}
		else {
			wxLogError(wxT("NumberAxis::DataChanged: BUG invalid dataset class")); // BUG!
			return ;
		}

		if (n == 0) {
			minValue = _minValue;
			maxValue = _maxValue;
		}
		else {
			minValue = MIN(minValue, _minValue);
			maxValue = MAX(maxValue, _maxValue);
		}
	}

	majorTick = (maxValue - minValue) / 5.0; //XXX temporary TODO if using intValues - make integer step


	if (!IsNormalValue(majorTick)) {
		// XXX overflow condition bugfix
		minValue = 0;
		maxValue = 0;
		majorTick = 0;

		hasTicks = false;
	}
	else {
		if (ABS(maxValue - minValue) > 0.000000001)
			hasTicks = true;
	}

	FireNeedRedraw();
}

wxSize NumberAxis::GetLongestLabelExtent(wxDC &dc)
{
	wxSize sizeMinValue = dc.GetTextExtent(wxString::Format(tickFormat, minValue));
	wxSize sizeMaxValue = dc.GetTextExtent(wxString::Format(tickFormat, maxValue));

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

	if (IsVertical()) {
		coord = minG + maxTextExtent.GetHeight() / 2;
		gRange = range - maxTextExtent.GetHeight();

		k = (maxValue - value) / (maxValue - minValue);
	}
	else {
		coord = minG + maxTextExtent.GetWidth() / 2;
		gRange = range - maxTextExtent.GetWidth();

		k = (value - minValue) / (maxValue - minValue);
	}

	if (gRange < 0)
		gRange = 0;

	return (wxCoord) (k * gRange + coord);
}

double NumberAxis::GetValue(int step)
{
	return minValue + step * majorTick;
}

void NumberAxis::GetLabel(int step, wxString &label)
{
	double value = GetValue(step);

	if (intValues) {
		label = wxString::Format(wxT("%i"), (int) value);
	}
	else {
		label = wxString::Format(tickFormat, value);
	}
}

bool NumberAxis::IsEnd(int step)
{
	double value = GetValue(step);
	return value > maxValue;
}

bool NumberAxis::HasTicks()
{
	return hasTicks;
}
