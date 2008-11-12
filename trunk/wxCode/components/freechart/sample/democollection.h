/////////////////////////////////////////////////////////////////////////////
// Name:	democollection.h
// Purpose: Demo collection class declaration
// Author:	Moskvichev Andrey V.
// Created:	2008/11/12
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
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

	virtual Chart *Create() = 0;

	const wxString &GetName()
	{
		return m_name;
	}

private:
	wxString m_name;
};

class DemoCollection
{
public:
	DemoCollection();
	virtual ~DemoCollection();

	int GetCategoryCount();

	wxString GetCategory(int index);

	int GetCategoryDemoCount(int index);

	ChartDemo *GetCategoryDemo(int catIndex, int demoIndex);

	static DemoCollection *Get();
};


#endif /* DEMOCOLLECTION_H_ */
