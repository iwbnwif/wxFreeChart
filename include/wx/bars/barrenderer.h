/////////////////////////////////////////////////////////////////////////////
// Name:	barrenderer.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	14.11.2008
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef BARRENDERER_H_
#define BARRENDERER_H_

#include "wx/xy/xyrenderer.h"
#include "wx/areadraw.h"

class CategoryDataset;

/**
 *
 */
class WXDLLEXPORT BarType
{
public:
	BarType();
	virtual ~BarType();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, int item, CategoryDataset *dataset);

	/**
	 * Sets area draw object to draw specified serie.
	 * @param serie serie index
	 * @param ad area draw for serie
	 */
	void SetBarArea(int serie, AreaDraw *ad)
	{
		m_barAreas.SetAreaDraw(serie, ad);
	}

	//
	// Called from BarRenderer
	//
	virtual double GetMinValue(CategoryDataset *dataset);
	virtual double GetMaxValue(CategoryDataset *dataset);

protected:
	virtual void GetBar(int item, int serie, CategoryDataset *dataset,
			int &width, wxCoord &shift, double &base, double &value) = 0;

	double m_base;

	AreaDrawCollection m_barAreas;
};

/**
 * Standard bar type. Draws series parallel to each other.
 */
class WXDLLEXPORT NormalBarType : public BarType
{
public:
	NormalBarType(int barWidth, int serieGap = 1, double base = 0.0);
	virtual ~NormalBarType();

protected:
	virtual void GetBar(int item, int serie, CategoryDataset *dataset,
			int &width, wxCoord &shift, double &base, double &value);

private:
	int m_barWidth;
	int m_serieGap;
};

/**
 * Draws series in stack, after each other.
 */
class WXDLLEXPORT StackedBarType : public BarType
{
public:
	StackedBarType(int barWidth, double base);
	virtual ~StackedBarType();

	virtual double GetMinValue(CategoryDataset *dataset);
	virtual double GetMaxValue(CategoryDataset *dataset);

protected:
	virtual void GetBar(int item, int serie, CategoryDataset *dataset,
			int &width, wxCoord &shift, double &base, double &value);

private:
	int m_barWidth;
};

/**
 * Draws series overlapped.
 */
class WXDLLEXPORT LayeredBarType : public BarType
{
public:
	LayeredBarType(int initialBarWidth, double base);
	virtual ~LayeredBarType();

protected:
	virtual void GetBar(int item, int serie, CategoryDataset *dataset,
			int &width, wxCoord &shift, double &base, double &value);

private:
	int m_initialBarWidth;
	double m_base;
};

class WXDLLEXPORT BarRenderer : public Renderer
{
	DECLARE_CLASS(BarRenderer)
public:
	BarRenderer(BarType *barType);
	virtual ~BarRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, CategoryDataset *dataset);

	/**
	 * Sets bar type. BarRenderer owns this object.
	 * @param barType new bar type.
	 */
	void SetBarType(BarType *barType);

	virtual double GetMinValue(CategoryDataset *dataset);
	virtual double GetMaxValue(CategoryDataset *dataset);

protected:
	BarType *m_barType;
};

class WXDLLEXPORT GanttBarRenderer : public BarRenderer
{
	DECLARE_CLASS(GanttBarRenderer)
public:
	GanttBarRenderer(BarType *barType);
	virtual ~GanttBarRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, CategoryDataset *dataset);

private:

};

#endif /*BARRENDERER_H_*/
