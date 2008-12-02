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
#include "wx/areabackground.h"

class CategoryDataset;

class BarType
{
public:
	BarType();
	virtual ~BarType();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, int item, CategoryDataset *dataset);

	void SetBarArea(int serie, AreaBackground *ab)
	{
		m_barAreas.SetAreaBackground(serie, ab);
	}

protected:
	virtual void GetBar(int item, int serie, CategoryDataset *dataset,
			int &width, wxCoord &shift, double &base, double &value) = 0;

	double m_base;

	AreaBackgroundCollection m_barAreas;
};

class NormalBarType : public BarType
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

	double base;
};

class StackedBarType : public BarType
{
public:
	StackedBarType(int barWidth, double base);
	virtual ~StackedBarType();

protected:
	virtual void GetBar(int item, int serie, CategoryDataset *dataset,
			int &width, wxCoord &shift, double &base, double &value);

private:
	int m_barWidth;

	double base;
};

class LayeredBarType : public BarType
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

class BarRenderer : public Renderer
{
public:
	BarRenderer(BarType *barType);
	virtual ~BarRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, CategoryDataset *dataset);

	void SetBarType(BarType *barType);

protected:
	BarType *m_barType;
};

class GanttBarRenderer : public BarRenderer
{
public:
	GanttBarRenderer(BarType *barType);
	virtual ~GanttBarRenderer();

	virtual void Draw(wxDC &dc, wxRect rc, Axis *horizAxis, Axis *vertAxis, bool vertical, CategoryDataset *dataset);

private:

};

#endif /*BARRENDERER_H_*/
