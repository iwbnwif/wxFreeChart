/////////////////////////////////////////////////////////////////////////////
// Name:	xysimpledataset.h
// Purpose: xy simple dataset class declaration
// Author:	Moskvichev Andrey V.
// Created:	2009/11/25
// Copyright:	(c) 2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef XYSIMPLEDATASET_H_
#define XYSIMPLEDATASET_H_

#include <wx/xy/xydataset.h>

#include <wx/dynarray.h>

/**
 * Holds data for one XY serie.
 */
class WXDLLIMPEXP_FREECHART XYSerie
{
public:
	/**
	 * Constructs new xy serie.
	 * @param data double [x, y] array
	 * @param count point count in data array
	 */
	XYSerie(double *data, int count);

	virtual ~XYSerie();

	double GetX(int index);

	double GetY(int index);

	int GetCount();

	const wxString &GetName();

	void SetName(const wxString &name);

private:
	double *m_data;
	int m_count;
	wxString m_name;
};

WX_DECLARE_EXPORTED_OBJARRAY(XYSerie *, XYSerieArray);

/**
 * Simple xy dataset.
 */
class WXDLLIMPEXP_FREECHART XYSimpleDataset : public XYDataset
{
	DECLARE_CLASS(XYSimpleDataset)
public:
	XYSimpleDataset();
	virtual ~XYSimpleDataset();

	/**
	 * Adds new xy serie.
	 * @param data double [x, y] array
	 * @param count point count in data array
	 */
	void AddSerie(double *data, int count);

	/**
	 * Constructs new xy serie.
	 * @param serie new serie
	 */
	void AddSerie(XYSerie *serie);

	//
	// XYDataset
	//
	virtual double GetX(int index, int serie);

	virtual double GetY(int index, int serie);

	virtual int GetSerieCount();

	virtual int GetCount(int serie);

	virtual wxString GetSerieName(int serie);

	void SetSerieName(int serie, const wxString &name);

private:
	XYSerieArray m_series;
};

#endif /*XYSIMPLEDATASET_H_*/
