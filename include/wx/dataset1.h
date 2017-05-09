/////////////////////////////////////////////////////////////////////////////
// Name:        dataeet.h
// Purpose:     Default data set classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATASET1_H_
#define DATASET1_H_

#include <wx/wxfreechartdefs.h>

#include <wx/dataset.h>
#include <wx/dataseries.h>

/***************************************
 * DATA SET
 ***************************************/

/**
 * Base class for all objects representing a data set.
 *
 * A data set is a collection of data series that can be plotted against a
 * common set of axis. Therefore, all data points within all series of a data
 * set must be of a common type.
 * 
 * 
 */
class WXDLLIMPEXP_FREECHART DataSet : public Dataset
{
public:

    /**
     * Default constructor that creates an empty data set with the option to provide a
     * name.
     * Currently dataset names are not used.
     * @param name The name that can be used to describe this data set.
     */
    DataSet (const wxString& name = wxEmptyString);

    /**
     * Default destructor.
     */
    virtual ~DataSet();
    
    /**
     * Add a data series to this data set. All series must contain data points with the same
     * number of dimensions and with data that is essentially the same type (i.e. that can 
     * be plotted against a common axis).
     * @param series
     */
    virtual void AddSeries(DataSeries* series);

    virtual const wxSharedPtr<DataSeries>  GetSeries(size_t index);

    virtual const size_t GetSeriesCount();

    virtual const wxString& GetName();

    virtual void SetName(const wxString& name);
    
    virtual void SetSeriesRenderer(size_t series, Renderer* renderer);
    
    // Implement or defer all pure virtual methods from original Dataset class.

    virtual bool AcceptRenderer (Renderer* r);

    virtual size_t GetCount (size_t serie);

    virtual double GetMaxValue (bool vertical) = 0;

    virtual double GetMinValue (bool vertical) = 0;

    virtual size_t GetSerieCount();

    virtual wxString GetSerieName (size_t serie);

protected:
    wxString m_name;
    wxVector<wxSharedPtr<DataSeries> > m_series;
    wxVector<wxSharedPtr<Renderer> > m_renderers;
};

/***************************************
 * UNI DATA SET
 ***************************************/

class WXDLLIMPEXP_FREECHART UniDataSet : public DataSet
{
public:
    UniDataSet (const wxString& name = wxEmptyString);

    virtual ~UniDataSet();
    
    void AddCategory(const wxAny& category);

    virtual size_t GetBaseCount();
    
    virtual const wxVector<wxAny>& GetBaseSeries() const;
    
    virtual const wxAny& GetBaseValue(size_t index) const;

    virtual double GetMaxValue(bool vertical);
    
    virtual double GetMinValue(bool vertical);

    virtual double GetValue(size_t series, size_t index) const;
    

private:
    wxVector<wxAny> m_baseSeries;
};

/***************************************
 * BI DATA SET
 ***************************************/

class WXDLLIMPEXP_FREECHART BiDataSet : public DataSet
{
public:
    BiDataSet (const wxString& name = wxEmptyString);

    virtual ~BiDataSet();

};

/***************************************
 * NARY DATA SET
 ***************************************/

class WXDLLIMPEXP_FREECHART NaryDataSet : public DataSet
{
public:
    NaryDataSet (const wxString& name = wxEmptyString);

    virtual ~NaryDataSet();

};


#endif // DATASET1_H_
