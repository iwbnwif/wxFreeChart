/////////////////////////////////////////////////////////////////////////////
// Name:	ohlcdataset.h
// Purpose: OHLC datasets base class declaration.
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCDATASET_H_
#define OHLCDATASET_H_

#include <wx/xy/xydataset.h>
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
 * Open-High-Low-Close datasets base class.
 */
class WXDLLIMPEXP_FREECHART OHLCDataset : public Dataset, public DateTimeDataset
{
public:
	OHLCDataset();
	virtual ~OHLCDataset();

	OHLCRenderer *GetRenderer()
	{
		return (OHLCRenderer *) m_renderer;
	}

	void SetSerieName(const wxString &serieName)
	{
		m_serieName = serieName;
		DatasetChanged();
	}

	/**
	 * Returns item on index.
	 * @param index index of item
	 */
	virtual OHLCItem *GetItem(int index) = 0;

	/**
	 * Returns item count.
	 * @return item count
	 */
	virtual int GetCount() = 0;

	//
	// Dataset
	//
	virtual double GetMinValue(bool verticalAxis);

	virtual double GetMaxValue(bool verticalAxis);

	virtual time_t GetDate(int index);

	virtual int GetSerieCount();

	virtual wxString GetSerieName(int serie);

	virtual int GetCount(int serie);

	virtual DateTimeDataset *AsDateTimeDataset();

protected:
	virtual bool AcceptRenderer(Renderer *r);

	wxString m_serieName;
};

#endif /*OHLCDATASET_H_*/
