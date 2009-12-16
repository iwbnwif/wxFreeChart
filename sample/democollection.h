/////////////////////////////////////////////////////////////////////////////
// Name:	democollection.h
// Purpose: Demo collection class declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/12
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DEMOCOLLECTION_H_
#define DEMOCOLLECTION_H_

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wx/chart.h"

/**
 * Base class for chart demo.
 *
 */
class ChartDemo
{
public:
	ChartDemo(const wxChar *name)
	{
		m_name = name;
	}

	virtual ~ChartDemo()
	{
	}

	/**
	 * Called to create chart.
	 * @return created demo chart
	 */
	virtual Chart *Create() = 0;

	const wxString &GetName()
	{
		return m_name;
	}

private:
	wxString m_name;
};

/**
 * Demos collection.
 */
class DemoCollection
{
public:
	DemoCollection();
	virtual ~DemoCollection();

	/**
	 * Returns category count.
	 * @return category count
	 */
	int GetCategoryCount();

	/**
	 * Returns category name at index.
	 * @param index index of category
	 * @return category name
	 */
	const wxString &GetCategory(int index);

	/**
	 * Returns demo count in category.
	 * @param index index of category
	 * @return demo count in category
	 */
	int GetCategoryDemoCount(int index);

	/**
	 * Returns demo in category.
	 * @param catIndex index of category
	 * @param demoIndex index of demo in category
	 * @return demo
	 */
	ChartDemo *GetCategoryDemo(int catIndex, int demoIndex);

	static DemoCollection *Get();
};


#endif /* DEMOCOLLECTION_H_ */
