/////////////////////////////////////////////////////////////////////////////
// Name:        dataeeries.h
// Purpose:     Default data series classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATASERIES_H_
#define DATASERIES_H_

#include <wx/wxfreechartdefs.h>

#include <wx/datapoint.h>

/**
 * Base class for all objects representing data series. 
 * 
 * A data series is a vector container of tightly related data points (see DataPoint). 
 * All data points in a data series are depicted in a connected manner, for example as points 
 * along a line, as a histogram or as segments of a pie.
 * 
 * There are no default specialisations of DataSeries because it is capable of serialising
 * all 3 default DataPoint specialisations. Convenience accessors to the differently
 * dimensioned data point classes are provided at the data set level. Therefore, 
 * access to data point data at the series level must be via the abstract functions (e.g.
 * GetDimensionValue(), SetDimensionValue().
 * 
 * DataSeries is derived from wxEvtHandler and posts a change event every time an element
 * is changed. Therefore, a watcher can subscribe to change events for a data series and
 * respond accordingly.
 */
class WXDLLIMPEXP_FREECHART DataSeries : public wxEvtHandler
{
public:
    /**
     * Default constructor that includes the option of setting the name for the series.
     * @param name The name for the series. Note: the name can be used for searching for the
     * series within a data set (see DataSet).
     */
    DataSeries(const wxString& name = wxEmptyString);
    
    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~DataSeries();
    
    /**
     * Adds a new data point to this series. 
     * 
     * The first data point that is added to the series specifies the number of dimensions
     * for that series and cannot be changed. Adding a data point that has a different number
     * of dimensions will raise an assert. Similarly attempting to add anything that is not
     * derived from DataPoint will also raise an assert.
     * @param dataPoint
     */
    virtual void AddPoint(DataPoint* dataPoint);
    
    /**
     * Delete all data points within this series and reset the dimension count.
     */
    virtual void Clear();
        
    /**
     * Returns the number of data points within this series.
     * @return The number of data points within this series.
     */
    virtual const size_t GetCount();

    /**
     * Returns the name assigned to this series.
     * This is the name used for the caption.
     * @return 
     */
    virtual const wxString& GetName();
    
    /**
     * Returns the data point at the given index position.
     * @param index The position within the series where the required data point is stored.
     * @return The required data point object. Normally, this will encapsulate one of the default 
     * data point types (UniDataPoint, BiDataPoint, NaryDataPoint).
     * The contents of the data point can be accessed via the generic access method. For example:
     * @code
     * series->GetPoint(15).get()->GetDimensionValue(0);
     * @endcode
     */
    virtual wxSharedPtr<DataPoint> GetPoint(size_t index);

    /**
     * Sets the name for this series.
     * This is the name used for the caption.
     * @param name The name to be assigned to this series.
     */
    virtual void SetName(const wxString& name);
    
    // TODO: SetPoint, RemovePoint needed?
    
private:
    wxString m_name;
    wxVector<wxSharedPtr<DataPoint> > m_points;
};

#ifdef DONOTUSE

/**
 * A series of tightly related single dimension data points (see UniDataPoint).
 * 
 * UniDataPoints are referred to as single dimension because they only contain a single
 * value. In order to plot a UniDataSeries on a 2D chart, a second dimension needs to be
 * added. For example, in a category chart, the second dimension is implied by the ordering
 * of the data points within the vector. In a histogram, the second dimension is created by
 * the number of data points having the same value.
 */
class WXDLLIMPEXP_FREECHART UniDataSeries : public DataSeries
{
public:
    /**
     * Default constructor that includes the option of setting the name for the series.
     * @param name The name for the series. Note: the name can be used for searching for the
     * series within a data set (see DataSet).
     */
    UniDataSeries(const wxString& name = wxEmptyString);
    
    /**
     * Constructor that populates the series with a set of data and includes the option of 
     * setting the name for the series.
     * @param data A vector of single dimension data points that will be contained within
     * the series.
     * @param name The name for the series.
     */
    UniDataSeries(const wxVector<UniDataPoint>& data, const wxString& name = wxEmptyString);
    
    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~UniDataSeries();
    
    /**
     * Returns the number of datapoints contained within the series.
     * @return The number of datapoints contained within the series.
     */
    virtual const size_t GetCount() wxOVERRIDE;
    
    UniDataPoint& GetData(size_t index);

private:
    wxVector<UniDataPoint> m_data;
};

/**
 * A series of tightly related bi-dimensional data points (see BiDataPoint).
 * 
 * BiDataPoints are referred to as having two dimensions because they only contain two independent,
 * discrete values. BiDataPoints can be plotted directly by a X-Y (scatter) plot (see XYPlot) and
 * possibly more 2D plots in the future.
 * 
 * Unlike UniDataSeries, which requires an implied second dimensions, BiDataSeries are fully specified
 * in their own right.
 */
class WXDLLIMPEXP_FREECHART BiDataSeries : public DataSeries
{
public:
    /**
     * Default constructor that includes the option of setting the name for the series.
     * @param name The name for the series. Note: the name can be used for searching for the
     * series within a data set (see DataSet).
     */
    BiDataSeries(const wxString& name = wxEmptyString);
    
    /**
     * Constructor that populates the series with a set of data and includes the option of 
     * setting the name for the series.
     * @param data A vector of single dimension data points that will be contained within
     * the series.
     * @param name The name for the series.
     */
    BiDataSeries(const wxVector<UniDataPoint>& data, const wxString& name = wxEmptyString);
    
    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~BiDataSeries();
    
    /**
     * Returns the number of datapoints contained within the series.
     * @return The number of datapoints contained within the series.
     */
    virtual const size_t GetCount() wxOVERRIDE;

private:
    wxVector<BiDataPoint> m_data;
};

/**
 * A series of tightly related n-dimensional data points (see NaryDataPoint).
 * 
 * NaryDataPoints hold values for 3 or more dimensions. Note: that a dimension in this
 * context means a value that can be independently plottable. Therefore, OHLC data points
 * are represented by BiDataPoint because although each data point has 5 values, the values
 * are all plotted in a single dimension (against a second dimension of time).
 * 
 * At present, NaryDataSeries are only used by bubble plots.
 */
class WXDLLIMPEXP_FREECHART NaryDataSeries : public DataSeries
{
public:
    /**
     * Default constructor that includes the option of setting the name for the series.
     * @param name The name for the series. Note: the name can be used for searching for the
     * series within a data set (see DataSet).
     */
    NaryDataSeries(const wxString& name = wxEmptyString);
    
    /**
     * Constructor that populates the series with a set of data and includes the option of 
     * setting the name for the series.
     * @param data A vector of single dimension data points that will be contained within
     * the series.
     * @param name The name for the series.
     */
    NaryDataSeries(const wxVector<UniDataPoint>& data, const wxString& name = wxEmptyString);
    
    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~NaryDataSeries();
    
    /**
     * Returns the number of datapoints contained within the series.
     * @return The number of datapoints contained within the series.
     */
    virtual const size_t GetCount() wxOVERRIDE;

private:
    wxVector<NaryDataPoint> m_data;
};

#endif

#endif // DATASERIES_H_    