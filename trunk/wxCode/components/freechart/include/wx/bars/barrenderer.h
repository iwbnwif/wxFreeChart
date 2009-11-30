/////////////////////////////////////////////////////////////////////////////
// Name:	barrenderer.h
// Purpose: bar renderer and bar types declarations
// Author:	Moskvichev Andrey V.
// Created:	14.11.2008
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef BARRENDERER_H_
#define BARRENDERER_H_

#include "wx/xy/xyrenderer.h"
#include "wx/areadraw.h"

class CategoryDataset;
class BarRenderer;

/**
 * Bar types base class.
 */
class WXDLLIMPEXP_FREECHART BarType
{
public:
	BarType(double base);
	virtual ~BarType();

	/**
	 * Performs bar drawing.
	 * @param barRenderer bar renderer
	 * @param dc device context
	 * @param rc rectangle where to draw
	 * @param horizAxis horizontal axis
	 * @param vertAxis vertical axis
	 * @param vertical true to draw vertical bars
	 * @param item dataset item index
	 * @param dataset dataset to draw bars
	 */
	virtual void Draw(BarRenderer *barRenderer, wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, int item, CategoryDataset *dataset);

	//
	// Called from BarRenderer. Don't call from programs.
	//
	virtual double GetMinValue(CategoryDataset *dataset);
	virtual double GetMaxValue(CategoryDataset *dataset);

protected:
	/**
	 * Called to calculate bar geometry params.
	 * Must be implemented by derivate classes.
	 * @param dataset dataset
	 * @param item item index
	 * @param serie serie index
	 * @param width output for bar width
	 * @param shift output for bar shift
	 * @param base output for bar base
	 * @param value output for bar value
	 */
	virtual void GetBarGeometry(CategoryDataset *dataset, int item, int serie,
			int &width, wxCoord &shift, double &base, double &value) = 0;

	double m_base;
};

/**
 * Normal bar type. Draws series parallel to each other.
 */
class WXDLLIMPEXP_FREECHART NormalBarType : public BarType
{
public:
	/**
	 * Constructs new normal bar type.
	 * @param barWidth bar width
	 * @param serieGap distance between series bars
	 * @param base bars base, point from bars are drawn
	 */
	NormalBarType(int barWidth, int serieGap = 1, double base = 0.0);
	virtual ~NormalBarType();

protected:
	virtual void GetBarGeometry(CategoryDataset *dataset, int item, int serie,
			int &width, wxCoord &shift, double &base, double &value);

private:
	int m_barWidth;
	int m_serieGap;
};

/**
 * Draws series in stack, after each other.
 */
class WXDLLIMPEXP_FREECHART StackedBarType : public BarType
{
public:
	/**
	 * Constructs new stacked bar type.
	 * @param barWidth bar width
	 * @param base bars base, point from bars are drawn
	 */
	StackedBarType(int barWidth, double base);
	virtual ~StackedBarType();

	virtual double GetMinValue(CategoryDataset *dataset);
	virtual double GetMaxValue(CategoryDataset *dataset);

protected:
	virtual void GetBarGeometry(CategoryDataset *dataset, int item, int serie,
			int &width, wxCoord &shift, double &base, double &value);

private:
	int m_barWidth;
};

/**
 * Draws series overlapped.
 */
class WXDLLIMPEXP_FREECHART LayeredBarType : public BarType
{
public:
	/**
	 * Constructs new layered bar type.
	 * @param initialBarWidth maximal bar width
	 * @param base bars base, point from bars are drawn
	 */
	LayeredBarType(int initialBarWidth, double base);
	virtual ~LayeredBarType();

protected:
	virtual void GetBarGeometry(CategoryDataset *dataset, int item, int serie,
			int &width, wxCoord &shift, double &base, double &value);

private:
	int m_initialBarWidth;
};

/**
 * Bar renderer.
 */
class WXDLLIMPEXP_FREECHART BarRenderer : public Renderer
{
	DECLARE_CLASS(BarRenderer)
public:
	/**
	 * Constructs new bar renderer.
	 * @param barType bar type to be drawn by this renderer,
	 * renderer takes ownership for bar type object
	 */
	BarRenderer(BarType *barType);
	virtual ~BarRenderer();

	//
	// Renderer
	//
	virtual void DrawLegendSymbol(wxDC &dc, wxRect rcSymbol, int serie);

	/**
	 * Draws dataset.
	 * @param dc device context
	 * @param horizAxis horizontal axis
	 * @param vertAxis vertical axis
	 * @param vertical true to draw vertical bars
	 * @param dataset dataset to be drawn
	 */
	void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, CategoryDataset *dataset);

	/**
	 * Sets bar type. BarRenderer owns this object.
	 * @param barType new bar type,
	 * renderer takes ownership for bar type object
	 */
	void SetBarType(BarType *barType);

	/**
	 * Returns bar type.
	 * @return bar type
	 */
	BarType *GetBarType();

	/**
	 * Sets area draw object to draw specified serie.
	 * @param serie serie index
	 * @param ad area draw for serie
	 */
	void SetBarDraw(int serie, AreaDraw *areaDraw);

	/**
	 * Returns area draw object, used to draw specified serie.
	 * @param serie serie index
	 * @return area draw object
	 */
	AreaDraw *GetBarDraw(int serie);

	double GetMinValue(CategoryDataset *dataset);
	double GetMaxValue(CategoryDataset *dataset);

private:
	BarType *m_barType;

	AreaDrawCollection m_barDraws;
};

#endif /*BARRENDERER_H_*/
