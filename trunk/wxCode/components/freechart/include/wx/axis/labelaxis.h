/////////////////////////////////////////////////////////////////////////////
// Name:	labelaxis.h
// Purpose:	label axis declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef LABELAXIS_H_
#define LABELAXIS_H_

#include <wx/axis/axis.h>

const wxCoord labelLineSize = 5;
const wxCoord labelGap = 2;

/**
 * Base class for axes for displaying data labels.
 */
class WXDLLEXPORT LabelAxis : public Axis
{
	DECLARE_CLASS(LabelAxis)
public:
	LabelAxis(AXIS_LOCATION location);
	virtual ~LabelAxis();

	virtual void Draw(wxDC &dc, wxRect rc);

	virtual void DrawGridLines(wxDC &dc, wxRect rc);

	virtual wxCoord ToGraphics(wxDC &dc, int minCoord, int gRange, double value);

	virtual double ToData(wxDC &dc, int minCoord, int gRange, wxCoord g);

	virtual wxCoord GetExtent(wxDC &dc);

	/**
	 * Sets axis title.
	 * @param new axis title
	 */
	void SetTitle(const wxString &title)
	{
		m_title = title;
		FireAxisChanged();
	}

	/**
	 * Returns axis title.
	 * @return axis title
	 */
	const wxString &GetTitle()
	{
		return m_title;
	}

	/**
	 * Sets axis title location.
	 * @param location new location for axis title,
	 * acceptable values wxLEFT, wxCENTER, wxRIGHT for horizontal axes,
	 * wxTOP, wxCENTER, wxBOTTOM for vertical axes.
	 */
	void SetTitleLocation(int location)
	{
		if (m_titleLocation != location) {
			m_titleLocation = location;
			FireAxisChanged();
		}
	}

	/**
	 * Returns axis title location.
	 * @return axis title location
	 */
	int GetTitleLocation()
	{
		return m_titleLocation;
	}

	/**
	 * Sets axis title font.
	 * @param axis title font
	 */
	void SetTitleFont(wxFont &font)
	{
		m_titleFont = font;
		FireAxisChanged();
	}

	/**
	 * Returns axis title font.
	 * @return axis title font
	 */
	const wxFont &GetTitleFont()
	{
		return m_titleFont;
	}

	/**
	 * Sets axis title colour.
	 * @param new axis title colour
	 */
	void SetTitleColour(wxColour &colour)
	{
		if (m_titleColour != colour) {
			m_titleColour = colour;
			FireAxisChanged();
		}
	}

	/**
	 * Returns axis title colour.
	 * @return axis title colour
	 */
	wxColour GetTitleColour()
	{
		return m_titleColour;
	}

	/**
	 * Sets minimal/maximal margins for axis.
	 * Eg bottom/top for vertical axes, left/right for horizontal.
	 * @param marginMin new minimal margin
	 * @param marginMax new maximal margin
	 */
	void SetMargins(wxCoord marginMin, wxCoord marginMax)
	{
		m_marginMin = marginMin;
		m_marginMax = marginMax;
		FireAxisChanged();
	}

	/**
	 * Sets pen for label lines.
	 * @param labelPen pen for label lines
	 */
	void SetLabelPen(wxPen labelPen)
	{
		m_labelPen = labelPen;
		FireAxisChanged();
	}

	/**
	 * Sets colour for labels.
	 * @param labelColour color for labels
	 */
	void SetLabelColour(wxColour labelColour)
	{
		m_labelColour = labelColour;
		FireAxisChanged();
	}

	/**
	 * Sets font for labels text.
	 * @param labelFont font for labels text
	 */
	void SetLabelFont(wxFont labelFont)
	{
		m_labelFont = labelFont;
		FireAxisChanged();
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

	virtual bool HasLabels();

private:
	void DrawLabels(wxDC &dc, wxRect rc);

	void DrawLabel(wxDC &dc, wxRect rc, const wxString &label, double value);

	void DrawBorderLine(wxDC &dc, wxRect rc);

	wxCoord m_marginMin;
	wxCoord m_marginMax;

	wxFont m_labelFont;
	wxPen m_labelPen;
	wxColour m_labelColour;

	wxString m_title;
	wxFont m_titleFont;
	wxColour m_titleColour;
	int m_titleLocation;
};

wxCoord ToGraphics(int minCoord, int gRange, double minValue, double maxValue, wxCoord margin, bool vertical, double value);
double ToData(int minCoord, int gRange, double minValue, double maxValue, wxCoord margin, bool vertical, wxCoord g);

#endif /*LABELAXIS_H_*/
