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

class Renderer;

enum DataTypeTrait
{
    TypeUndefined,
    TypeTraitNominal,
    TypeTraitOrdinal,
    TypeTraitInterval,
    TypeTraitRatio
};


/**
 * Helper class to assist clients of data sets in interpreting the content of
 * the dataset.
 * This class is designed to be overidden in order to extend the list of types that
 * are able to be stored in a data set and plotted on a chart. The default version
 * of this class provides interpretation of int, float, double and wxDateTime types.
 */
class WXDLLIMPEXP_FREECHART DataInterpreter
{
public:

    DataInterpreter();
    virtual ~DataInterpreter();
    
    /**
     * Re-interprets a value representation of the data back to its wxAny format. This is of limited
     * use for complex data types, but is useful for data types that are able to be represented by a 
     * rational value.
     * @param value The internal representation of the wxAny object.
     * @param dimension The dimension of the object to be interpreted. This is necessary because
     * two or more dimensions may use the same data type, but it is necessary to differentiate 
     * them because they may have different interpretations (see Julian date axis example).
     * @param options Possible options to modify how a particular data object is re-interpreted.
     * This is not used in the default class, but can be used by subclasses along with
     * specialised Axis and Renderer classes to fine tune the part of the data that is
     * treated as being ordinal.
     * @return The typed data.
     */
    virtual wxAny AsAny(double value, size_t dimension, int options = 0) const;

    /**
     * Re-interprets an object representation to a different wxAny format.
     * @param data The internal representation of the wxAny object.
     * @param dimension The dimension of the object to be interpreted. This is necessary because
     * two or more dimensions may use the same data type, but it is necessary to differentiate 
     * them because they may have different interpretations (see Julian date axis example).
     * @param options Possible options to modify how a particular data object is re-interpreted.
     * This is not used in the default class, but can be used by subclasses along with
     * specialised Axis and Renderer classes to fine tune the part of the data that is
     * treated as being ordinal.
     * @return The typed data.
     */
    virtual wxAny AsAny(const wxAny& data, size_t dimension, int options = 0) const;

    /**
     * Interprets the content of the data contained within the wxAny container in an
     * ordinal way and returns the coresponding value.
     * @param data The wxAny object to be interpreted. The object must contain one of
     * the known types otherwise an error (assert) will be raised.
     * @param dimension The dimension of the object to be interpreted. This is necessary because
     * two or more dimensions may use the same data type, but it is necessary to differentiate 
     * them because they may have different interpretations (see Julian date axis example).
     * @param options Possible options to modify how a particular data object is interpreted.
     * This is not used in the default class, but can be used by subclasses along with
     * specialised Axis and Renderer classes to fine tune the part of the data that is
     * treated as being ordinal.
     * @return The interpreted value of the data.
     */
    virtual double AsValue(const wxAny& data, size_t dimension, int options = 0) const;
    
    /**
     * Get the trait for the data type that is being interpreted.
     * @param data
     * @return The type trait for this object. If the object is not recognised by this
     * class then TypeUndefined is returned. This provides an application with an opportunity
     * to gracefully manage the situation rather than an assert being raised later.
     */
    virtual DataTypeTrait GetTrait(const wxAny& data, size_t dimension) const;
};


/**
 * Simple class to help locate a data point in a specific dataset and series.
 */
class WXDLLIMPEXP_FREECHART DataItemLocator
{
public:
    /**
     * Constructor to fully identify a data point.
     */
    DataItemLocator (size_t dataset, size_t series, size_t index, bool valid);
    
    /**
     * Gets the dataset index where this data point is stored.
     * @return The dataset holding this data point.
     */
    size_t GetDataset();
    
    /**
     * Gets the series index where this data point is stored.
     * @return The series holding this data point.
     */
    size_t GetSeries();
    
    /**
     * Gets the index of this data point within the data series.
     * @return The index of this data point.
     */
    size_t GetIndex();
    
    /**
     * Gets the validity of this data point locator.
     * @return True if the locator contains valid information to locate a data point.
     */
    bool IsValid();

private:    
    size_t m_dataset;
    size_t m_series;
    size_t m_index;
    bool m_valid;
};

//
// Helper functions and macros.
//
void ClipHoriz(Axis *axis, double &x, double &y, double x1, double y1);

void ClipVert(Axis *axis, double &x, double &y, double x1, double y1);

#define FOREACH_SERIE(index, dataset) \
    for (size_t index = 0; index < dataset->GetSeriesCount(); index++)

#define FOREACH_DATAITEM(index, serie, dataset) \
    for (size_t index = 0; index < dataset->GetSeriesSize(serie); index++)

wxDECLARE_EVENT(EVT_DATASET_CHANGED, wxCommandEvent);        
        
/***************************************
 * DATA SET
 ***************************************/

/**
 * Base class for all objects representing a data set.
 *
 * A DataSet is a collection of DataSeries that can be plotted against a common set of axis using a common Renderer.
 * Therefore, all data points within all series of a data set must be of a common data type (e.g. a double or a complex
 * data type such as wxDateTime).
 */
class WXDLLIMPEXP_FREECHART DataSet : public wxEvtHandler, public RefObject
{
public:

    /**
     * Default constructor that creates an empty data set with the option to provide a
     * name.
     * @todo Currently dataset names are not used.
     * @param name The name that can be used to describe this data set.
     * @par Example
     * @code DataSet* dataset = new DataSet("Example dataset"); @endcode
     */
    DataSet (const wxString& name = wxEmptyString);

    /**
     * Default destructor.
     */
    virtual ~DataSet();
    
    /**
     * Add a DataSeries to this %DataSet. All DataSeries must contain DataPoint with the same
     * number of dimensions and with data that is essentially the same type (e.g. that can 
     * be plotted against common Axis and with a common Renderer).
     * @param series A pointer to the DataSeries to add to this DataSet. The DataSet will take
     * ownership of the pointer and automatically delete the DataSeries object when the DataSet is destroyed.
     * @return A pointer to the added series or NULL if an error occurred. This is provided so that it is possible
     * to generate a new data series inline by passing `new xDataSeries("Name")` as a parameter and receiving
     * a pointer to the added series.
     * @par Example
     * @code 
     * DataSet* dataset = new DataSet("Example dataset");
     * BiDataSeries* series = dataset->AddSeries(new BiDataSeries("Example series");
     * 
     * if (series)
     *      ...
     * @endcode
     */
    virtual DataSeries* AddSeries(DataSeries* series);
    
    virtual DataInterpreter* GetInterpreter() const;
    
    /**
     * Retrieves the maximum value for a given dimension in all of the series that belong to
     * this data set.
     * @param dimension The dimension to obtain the maximum value for.
     * @return The maximum value for the given data dimension in all series within this dataset.
     * 
     */
    virtual double GetMaxValue1(size_t dimension) const;
    
    /**
     * Retrieves the minimum value for a given dimension in all of the series that belong to
     * this data set.
     * @param dimension The dimension to obtain the minimum value for.
     * @return The minimum value for the given data dimension in all series within this dataset.
     */
    virtual double GetMinValue1(size_t dimension) const;
    
    virtual const wxString& GetName() const;

    virtual const wxSharedPtr<DataPoint> GetPoint(size_t series, size_t index, size_t dimension) const;

    virtual const wxAny& GetPointData(size_t series, size_t index, size_t dimension) const;

    virtual const double GetPointValue(size_t series, size_t index, size_t dimension) const;

    virtual const Renderer* GetRenderer() const;

    virtual Renderer* GetRenderer();
    
    virtual const wxSharedPtr<DataSeries> GetSeries(size_t index) const;

    /**
     * Returns serie count in this dataset.
     * @return serie count
     */
    virtual const size_t GetSeriesCount() const;

    virtual void SetInterpreter(DataInterpreter* interpreter);

    virtual void SetName(const wxString& name);
    
    virtual const wxAny InterpretAsAny(size_t series, size_t index, size_t dimension, int options = 0) const;
    
    virtual const wxAny InterpretValueAsAny(size_t series, size_t index, size_t dimension, int options = 0) const;
    
    virtual double InterpretAsValue(size_t series, size_t index, size_t dimension, int options = 0) const;
    
    // Implement or defer all pure virtual methods from original Dataset class.

    virtual bool AcceptRenderer(Renderer* r);

    virtual size_t GetSeriesSize(size_t serie) const;

    virtual wxString GetSeriesName (size_t serie) const;
    
        /**
     * Sets renderer for this dataset.
     * @param renderer new renderer
     */
    void SetRenderer(Renderer *renderer);

    Renderer *GetBaseRenderer();

    /**
     * Called to begin dataset update.
     * Each call must have corresponding EndUpdate call.
     * Increment dataset update counter.
     */
    void BeginUpdate();

    /**
     * Called to end dataset update.
     * Decrement dataset update counter, and fires
     * DatasetChanged event when counter equal zero.
     */
    void EndUpdate();

    /**
     * Adds marker to plot. Plot takes ownership of marker.
     * @param marker marker to be added
     */
    void AddMarker(Marker *marker);

    /**
     * Returns marker count.
     * @return marker count
     */
    size_t GetMarkersCount();

    /**
     * Returns marker at specified index.
     * @param index index of marker
     * @return marker at specified index
     */
    Marker *GetMarker(size_t index);

    //
    // DrawObjectObserver
    //
    // Received from renderer, or marker
    virtual void NeedRedraw(DrawObject *obj);

    /**
     * Called to indicate, that dataset is changed.
     * For call by derivate classes.
     */
    void DatasetChanged();

protected:
    wxString m_name;
    DataInterpreter* m_interpreter;
    wxVector<wxSharedPtr<DataSeries> > m_series;

    Renderer *m_renderer;    
private:
    bool m_updating;
    bool m_changed;
    
    MarkerArray m_markers;

};

/***************************************
 * DATA SET ARRAY
 ***************************************/

WX_DECLARE_USER_EXPORTED_OBJARRAY(DataSet*, DatasetArrayBase, WXDLLIMPEXP_FREECHART);

class WXDLLIMPEXP_FREECHART DatasetArray : public DatasetArrayBase
{
public:
    DatasetArray();
    virtual ~DatasetArray();

    void Add(DataSet* dataset);

    void Remove(DataSet* dataset);

    void RemoveAt(size_t index, size_t count = 1);
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
    
    virtual double GetValue(size_t series, size_t index) const;
    
    // Abstract Data Set method implementations.   

    virtual double GetMaxValue(bool vertical) const;
    
    virtual double GetMinValue(bool vertical) const;

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
    
    virtual double GetFirst(size_t series, size_t index);
    
    virtual double GetSecond(size_t series, size_t index);
        
    // Abstract Data Set method implementations.   

    virtual double GetMaxValue(bool vertical) const;
    
    virtual double GetMinValue(bool vertical) const;
};

/***************************************
 * NARY DATA SET
 ***************************************/

class WXDLLIMPEXP_FREECHART NaryDataSet : public DataSet
{
public:
    NaryDataSet (const wxString& name = wxEmptyString);

    virtual ~NaryDataSet();
    
    // Abstract Data Set method implementations.   

    virtual double GetMaxValue(bool vertical) const;
    
    virtual double GetMinValue(bool vertical) const;
};


#endif // DATASET1_H_
