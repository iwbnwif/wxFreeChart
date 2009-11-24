/////////////////////////////////////////////////////////////////////////////
// Name:	barrenderer.h
// Purpose:
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

/**
 *
 */
class WXDLLIMPEXP_FREECHART BarType
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
	void SetBarDraw(int serie, AreaDraw *ad)
	{
		m_barDraws.SetAreaDraw(serie, ad);
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

	AreaDrawCollection m_barDraws;
};

/**
 * Standard bar type. Draws series parallel to each other.
 */
class WXDLLIMPEXP_FREECHART NormalBarType : public BarType
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
class WXDLLIMPEXP_FREECHART StackedBarType : public BarType
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
class WXDLLIMPEXP_FREECHART LayeredBarType : public BarType
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

/**
 * Bar plot renderer.
 */
class WXDLLIMPEXP_FREECHART BarRenderer : public Renderer
{
	DECLARE_CLASS(BarRenderer)
public:
	/**
	 * Constructs new bar renderer.
	 * @param barType bar type to be drawn by this renderer
	 */
	BarRenderer(BarType *barType);

	virtual ~BarRenderer();

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
	 * @param barType new bar type.
	 */
	void SetBarType(BarType *barType);

	double GetMinValue(CategoryDataset *dataset);
	double GetMaxValue(CategoryDataset *dataset);

protected:
	BarType *m_barType;
};

#endif /*BARRENDERER_H_*/
