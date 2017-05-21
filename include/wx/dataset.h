/////////////////////////////////////////////////////////////////////////////
// Name:        dataeet.h
// Purpose:     Default data set classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATASET_H_
#define DATASET_H_

#include <wx/wxfreechartdefs.h>

#include <wx/dataset.h>
#include <wx/dataseries.h>
#include <wx/marker.h>
#include <wx/refobject.h>


class Axis;
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
 * A DataSet is a collection of DataSeries that can be plotted against a common set of Axis using a common Renderer.
 * Therefore, *all* DataPoint objects within *all* DataSeries of a DataSet must be of a common data type (e.g. a `double` or 
 * a complex data type such as `wxDateTime`).
 */
class WXDLLIMPEXP_FREECHART DataSet : public wxEvtHandler, public RefObject
{
public:

    /**
     * Default constructor that creates an empty data set with the option to provide a name for the dataset.
     * @todo Currently dataset names are not used. In future it may be possible to access a dataset by its name rather than
     * by an index.
     * @param name The name that can be used to describe (and possibly access in future) this data set.
     * @par Example
     * @code BiDataSet* dataset = new BiDataSet("AvgTemp"); @endcode
     */
    DataSet (const wxString& name = wxEmptyString);

    /**
     * Default destructor.
     */
    virtual ~DataSet();
    
    /**
     * @{
     * @name Data Series Methods
     * The following methods manage the DataSeries within this DataSet.
     */

    /**
     * Add a DataSeries to this %DataSet. All DataSeries must contain DataPoint with the same number of dimensions and with 
     * data that is essentially the same type (e.g. that can be plotted against common Axis and with a common Renderer).
     * @param series A pointer to the DataSeries to add to this DataSet. The DataSet will take ownership of the pointer 
     * and automatically delete the DataSeries object when the DataSet is destroyed.
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

    /**
     * Gets a smart pointer to a series within the data set.
     * @param index The index of the DataSeries within the DataSet.
     * @return A smart pointer to the required DataSeries.
     */
    virtual const wxSharedPtr<DataSeries> GetSeries(size_t index) const;

    /**
     * Gets the number of series held by this data set.
     * @note This should not be confused with GetSeriesSize() which retrieves the number of data points within a specified series.
     * @return The number of series held by the data set.
     * @see GetSeriesSize()
     */
    virtual const size_t GetSeriesCount() const;

    /**
     * Gets the name associated with this data set.
     * This is a convenience function to access the DataSeries::GetName() method.
     * @note DataSet names are not currently used within the library, but may still be used by an application if desired. In
     * future, a data set may be accessed by its name.
     * @param series The index of the series whose name is required.
     * @return The name associated with the given series.
     */
    virtual const wxString& GetSeriesName (size_t series) const;

    /**
     * Gets the number of data points held by the given series within this data set.
     * This is a convenience function to access the DataSeries::GetSize() method. 
     * @note This should not be confused with GetSeriesCount() which retrieves the number of series held by this data set.
     * @param series The index of the series whose size is required.
     * @return The number of data points held by the give series.
     * @see GetSeriesCount()
     */
    virtual size_t GetSeriesSize(size_t serie) const;
   
    /**
    *@}
    */
   
    /**
     * @{
     * @name Data Point Access Methods
     * The following methods manage individual DataPoint with this DataSet.
     */

    /**
     * Gets the data interpreter that is used to interpret the contents of data points in this data set.
     * A data interpreter is used to convert the data in a DataPoint to a form that can be plotted on a chart. Only one
     * data interpreter can be assigned to each data set and therefore all data points must be of a consistent formation.
     * See the detailed description in the DataInterpreter class for more details.
     * @return A pointer to the DataInterpreter associated with this data set.
     */
    virtual DataInterpreter* GetInterpreter() const;
    
    /**
     * Retrieves the maximum numeric (interpreted) value for a given dimension in *all* of the series that belong to
     * this data set.
     * @par Important
     * This method is used by all ordinal, interval and rational axis types (e.g. NumberAxis, DateAxis, etc.).
     * The DataInterpreter *must* therefore include a function to convert the DataPoint data to a representative `double`
     * so that a 'maximum' data point can be identified *or* this method can be overridden to provide an alternative way 
     * of establishing a max value.
     * @param dimension The dimension to obtain the maximum value for.
     * @return The maximum value for the given data dimension in all series within this dataset.
     * 
     */
    virtual double GetMaxValue1(size_t dimension) const;
    
    /**
     * Retrieves the minimum numeric (interpreted) value for a given dimension in *all* of the series that belong to
     * this data set.
     * @par Important
     * This method is used by all ordinal, interval and rational axis types (e.g. NumberAxis, DateAxis, etc.).
     * The DataInterpreter *must* therefore include a function to convert the DataPoint data to a representative `double`
     * so that a 'minimum' data point can be identified *or* this method can be overridden to provide an alternative way 
     * of establishing a min value.
     * @param dimension The dimension to obtain the minimum value for.
     * @return The minimum value for the given data dimension in all series within this dataset.
     */
    virtual double GetMinValue1(size_t dimension) const;

    /**
     * Retrieves a specified data point within this data set. Data points are stored in data series, so this method requires
     * both the series and an index within that series in order to locate the data point. This is a convenience method
     * to access a data point directly without first dereferencing the series containing the data point.
     * 
     * The intended purpose of this method is to allow external access to the data held by the data set, for example 
     * it could be used to display the stored data in a table or grid.
     * 
     * @note This method bypasses the DataInterpreter layer, so the returned data point will be in the originally stored
     * data type.
     * @param series The series that contains the data point of interest.
     * @param index The index of the data point within its data series.
     * @return A constant pointer to the data point. The actual type of DataPoint will be that stored in the DataSeries.
     * 
     * @par Example
     * @code
     * // Retrieve a BiDataPoint from a BiDataSet and check its type.
     * BiDataSet* dataset = wxDynamicCast(myPlot->GetDataset(0), BiDataSet);
     * 
     * BiDataPoint* point = wxDynamicCast(dataset->GetPoint(0, 52), BiDataPoint);
     * if(point)
     * {
     *      wxLogMessage("Point data is (X,Y): %f, %f",
     *                      point->GetFirst(),
     *                      point->GetSecond());
     * }
     * @endcode
     */
    virtual const wxSharedPtr<DataPoint> GetPoint(size_t series, size_t index) const;

    /**
     * Gets the _interpreted_ data object for the specified point within this data set. Data points are stored in data series, 
     * so this method requires both the series and an index within that series in order to locate the data point. This is a 
     * convenience method to access a data point's data directly without first dereferencing the series containing the data point.
     * 
     * @note The DataInterpreter causes an additional lookup and an additional copy to occur during the wxAny to wxAny process.
     * This is because the returned wxAny can contain completely different object from the input wxAny.
     * 
     * @note Therefore, GetRawPointData should be used for speed sensitive implementations that do not require a wxAny to wxAny 
     * interpretation. This will also require the implementation of new Axis classes because the built-in Axis will always
     * attempt to interpret the data.
     * 
     * @todo See note above. Could a NULL DataInterpreter be used to force non-interpreted versions of the Axis methods to be used?
     * 
     * @param series The series that contains the data point of interest.
     * @param index The index of the data point within its data series.
     * @return A constant pointer to the data point. The actual type of DataPoint will be that stored in the DataSeries.
     * 
     * @par Example
     * @code
     * // Checks for validity of dataset if appropriate.
     * 
     * ...
     * 
     * // Note: cannot take a reference here as it is a copy of the temporary value created by the interpreter.
     * wxAny ohlcPoint = dataset->GetPointData(0, 52, 1);
     * OHLCItem item = ohlcPoint.As<OHLCItem>();
     * 
     * wxLogMessage("OHLC values are: %f, %f, %f, %f",
     *                      item.open,
     *                      item..high,
     *                      item.low,
     *                      item.close);
     * @endcode
     */
    virtual const wxAny GetPointData(size_t series, size_t index, size_t dimension, int interpreterOptions = 0) const;

    virtual const double GetPointValue(size_t series, size_t index, size_t dimension, int interpreterOptions = 0) const;

    virtual const wxAny& GetRawPointData(size_t series, size_t index, size_t dimension) const;

    virtual void SetInterpreter(DataInterpreter* interpreter);

    /**
    *@}
    */

    /**
     * @{
     * @name Miscellaneous Methods
     * Miscellaneous dataset methods.
     */
    
    /**
     * Gets a name
     * 
     */
    virtual const wxString& GetName() const;

    virtual const Renderer* GetRenderer() const;

    virtual Renderer* GetRenderer();
    

    virtual void SetName(const wxString& name);
    
    // Implement or defer all pure virtual methods from original Dataset class.

    virtual bool AcceptRenderer(Renderer* r);

    /**
     * Sets renderer for this dataset.
     * @param renderer new renderer
     */
    void SetRenderer(Renderer *renderer);

    Renderer* GetBaseRenderer();

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

    /**
    *@}
    */
    
protected:
    DataInterpreter* m_interpreter;
    wxVector<wxSharedPtr<DataSeries> > m_series;
    Renderer *m_renderer;    

private:
    wxString m_name;

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


#endif // DATASET_H_
