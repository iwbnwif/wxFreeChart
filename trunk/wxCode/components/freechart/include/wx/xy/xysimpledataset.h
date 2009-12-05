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
	XYSerie(double *data, size_t count);

	virtual ~XYSerie();

	double GetX(size_t index);

	double GetY(size_t index);

	size_t GetCount();

	const wxString &GetName();

	void SetName(const wxString &name);

private:
	double *m_data;
	size_t m_count;
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
	void AddSerie(double *data, size_t count);

	/**
	 * Constructs new xy serie.
	 * @param serie new serie
	 */
	void AddSerie(XYSerie *serie);

	//
	// XYDataset
	//
	virtual double GetX(size_t index, size_t serie);

	virtual double GetY(size_t index, size_t serie);

	virtual size_t GetSerieCount();

	virtual size_t GetCount(size_t serie);

	virtual wxString GetSerieName(size_t serie);

	void SetSerieName(size_t serie, const wxString &name);

private:
	XYSerieArray m_series;
};

#endif /*XYSIMPLEDATASET_H_*/
