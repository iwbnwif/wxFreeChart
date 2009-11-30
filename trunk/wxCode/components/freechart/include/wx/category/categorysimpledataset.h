/////////////////////////////////////////////////////////////////////////////
// Name:	categorysimpledataset.h
// Purpose: category simple dataset declarations
// Author:	Moskvichev Andrey V.
// Created:	2009/11/26
// Copyright:	(c) 2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef CATEGORYSIMPLEDATASET_H_
#define CATEGORYSIMPLEDATASET_H_

#include <wx/category/categorydataset.h>

#include <wx/dynarray.h>

class CategorySerie
{
public:
	CategorySerie(const wxString &name, double *values, int count);
	virtual ~CategorySerie();

	const wxString &GetName();

	double GetValue(int index);

private:
	wxString m_name;
	int m_count;
	double *m_values;
};

WX_DECLARE_EXPORTED_OBJARRAY(CategorySerie *, CategorySerieArray);

/**
 * Simple category dataset implementation.
 */
class CategorySimpleDataset : public CategoryDataset
{
	DECLARE_CLASS(CategorySimpleDataset)
public:
	/**
	 * Constructs new category simple dataset.
	 * @param names category names array
	 * @param count names count
	 */
	CategorySimpleDataset(wxString *names, int count);
	virtual ~CategorySimpleDataset();

	void AddSerie(const wxString &name, double *values, int count);

	void AddSerie(CategorySerie *serie);

	//
	// CategoryDataset
	//
	virtual double GetValue(int index, int serie);

	virtual int GetSerieCount();

	virtual wxString GetName(int index);

	virtual int GetCount();

	virtual wxString GetSerieName(int serie);

private:
	wxArrayString m_names;
	CategorySerieArray m_series;
};

#endif /* CATEGORYSIMPLEDATASET_H_ */
