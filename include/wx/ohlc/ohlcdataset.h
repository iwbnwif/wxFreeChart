
/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcdataset.h
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCDATASET_H_
#define OHLCDATASET_H_

#include <wx/xy/xydataset.h>

#include <wx/datetimedataset.h>
#include <wx/valuerange.h>

#include <wx/ohlc/ohlcrenderer.h>

struct OHLCItem
{
	double open;
	double high;
	double low;
	double close;

	int volume;

	time_t date;
};

/**
 * Open-High-Low-Close dataset for quotes.
 */
class OHLCDataset : public Dataset, public ValueRange, public DateTimeDataset
{
public:
	OHLCDataset();
	virtual ~OHLCDataset();

	OHLCRenderer *GetRenderer()
	{
		return (OHLCRenderer *) renderer;
	}

	/**
	 * Returns item on index.
	 * @param index index of item
	 */
	virtual OHLCItem *GetItem(int index) = 0;

	virtual int GetCount() = 0;

	//
	// ValueDataset
	//
	virtual double GetMinValue(bool verticalAxis);

	virtual double GetMaxValue(bool verticalAxis);

	//
	// DateTimeDataset
	//
	virtual time_t GetDate(int index);

	//
	// Dataset
	//
	virtual int GetSerieCount();

	virtual wxString GetSerieName(int serie);

	virtual int GetCount(int serie);

protected:
	virtual bool AcceptRenderer(Renderer *r);
};

#endif /*OHLCDATASET_H_*/
