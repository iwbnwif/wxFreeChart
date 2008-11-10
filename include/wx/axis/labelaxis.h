
/////////////////////////////////////////////////////////////////////////////
// Name:	labelaxis.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef LABELAXIS_H_
#define LABELAXIS_H_

#include <wx/axis/axis.h>

const wxCoord tickSize = 5; // TODO temporary
const wxCoord tickLabelGap = 2;

/**
 * Base class for axes for displaying data labels.
 */
class LabelAxis : public Axis
{
public:
	LabelAxis(AXIS_LOCATION location);
	virtual ~LabelAxis();

	virtual void Draw(wxDC &dc, wxRect rc);

	virtual void DrawGridLines(wxDC &dc, wxRect rc);

	virtual wxCoord ToGraphics(wxDC &dc, int minG, int range, double value);

	virtual wxCoord GetExtent(wxDC &dc);

	/**
	 * Sets minimal/maximal margins for axis.
	 * Eg bottom/top for vertical axes, left/right for horizontal.
	 * @param _marginMin new minimal margin
	 * @param _marginMax new maximal margin
	 */
	void SetMargins(wxCoord _marginMin, wxCoord _marginMax)
	{
		marginMin = _marginMin;
		marginMax = _marginMax;
		FireNeedRedraw();
	}

	/**
	 * Sets pen for tick marks.
	 * @param pen for tick marks
	 */
	void SetTickPen(wxPen _tickPen)
	{
		tickPen = _tickPen;
		FireNeedRedraw();
	}

	/**
	 * Sets color for tick labels.
	 * @param _tickLabelsColor color for tick labels
	 */
	void SetTickLabelsColor(wxColour _tickLabelsColor)
	{
		tickLabelsColor = _tickLabelsColor;
		FireNeedRedraw();
	}

	/**
	 * Sets font for tick labels.
	 * @param _tickFont font for tick labels
	 */
	void SetTickLabelsFont(wxFont _tickFont)
	{
		tickFont = _tickFont;
		FireNeedRedraw();
	}

protected:
	//
	// Functions that must be implemented by derivative classes
	//

	/**
	 * Returns value on step.
	 * @param step step index
	 * @return value on step
	 */
	virtual double GetValue(int step) = 0;

	/**
	 * Returns label on step.
	 * @param step step index
	 * @param label output label
	 */
	virtual void GetLabel(int step, wxString &label) = 0;

	virtual bool IsEnd(int step) = 0;

	virtual wxSize GetLongestLabelExtent(wxDC &dc) = 0;

	virtual wxCoord DoToGraphics(wxDC &dc, int minG, int range, double value) = 0;

	virtual bool HasTicks();

private:
	void DrawTicks(wxDC &dc, wxRect rc);

	void DrawTick(wxDC &dc, wxRect rc, wxString label, double value);

	void DrawBorderLine(wxDC &dc, wxRect rc);

	wxCoord marginMin;
	wxCoord marginMax;

	wxFont tickFont;
	wxPen tickPen;
	wxColour tickLabelsColor;
};

#endif /*LABELAXIS_H_*/
