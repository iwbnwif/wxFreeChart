/////////////////////////////////////////////////////////////////////////////
// Name:        datapoint.h
// Purpose:     Default data point classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////


#ifndef DATAPOINT_H_
#define DATAPOINT_H_

#include <wx/wxfreechartdefs.h>


/***************************************
 * DATA POINT
 ***************************************/

/**
 * Abstract base class for all objects representing data points.
 *
 * A data point is an object that represents an individual piece of data, and in the case of wxFreeChart,
 * it is an individual piece of data that should be plotted on the chart. Data points can be rendered in many 
 * different ways depending on the chart type. For example, they can be rendered as points on a line, bars of different 
 * lengths, segements of a circle etc.
 * 
 * Closely related data points are collected together to form a DataSeries. In fact, as far as wxFreeChart is concerned, all
 * data points must belong to a DataSeries in order to be plottable.
 * 
 * DataPoint is an abstract base class so should not be used directly, but can be subclassed to incapsulate almost any
 * type of data. wxFreeChart provides three built in subclasses:
 * 
 * - UniDataPoint: This a container for a single dimensional data item, such as a percentage, colour or a temperature. Single
 * dimension data can be plotted as a pie chart (PiePlot) or histogram (HistoPlot). If a second axis is inherent in the data, 
 * such as the time at which the temperature reading was taken, then UniDataPoint can be plotted as a bar chart (BarPlot).
 * 
 * - BiDataPoint: This a container for two-dimensional data, such as combined temperature and pressure readings. Data points of
 * this type can be plotted directly on a two dimensional canvas, most commonly as a X-Y scatter chart (XYPlot).
 * 
 * - NaryDataPoint: This is an arbatary container for multi-dimensional data, such as combined temperature, pressure and 
 * relative humidity samples. At present, a NaryDataPoint is only used in bubble plots (BubblePlot).
 * .
 * 
 * It should be understood that these three subclasses are only provided for convenience and to allow the use of widely 
 * recognised terms. N-ary data could be represented using just the UniDataPoint class because DataPoint uses the templated 
 * wxAny as its storage class, so an n-ary data point could be formed by `wxVector<double>` for example. The converse is also
 * true, a UniDataPoint could be created using a NaryDataPoint where each storage vector has just one item and a BiDataPoint 
 * could be created with one that has two.
 * 
 * DataPoint data is not read directly by wxFreeChart but is _interpreted_ as part of a DataSet using a DataInterpreter. The
 * data interpreter allows specialised data to be stored directly in a DataPoint, but still plotted against one of the standard
 * chart Axis. For example, dates and times can be stored using a Julian Date Number (JDN), but interpreted and plotted 
 * against the built-in DateAxis which uses wxDateTime::GetTicks() internally.
 */
class WXDLLIMPEXP_FREECHART DataPoint : public wxObject
{
public:
    /**
     * Default constructor. This method will instantiate a data point, but without any data. A comment can be optionally
     * set.
     * @param comment An optional comment for this data point. Comments are typically shown when the user hovers the mouse over
     * a point, bar or segment on a plot.
     * @see IsEmpty().
     */
    DataPoint (const wxString& comment = wxEmptyString);

    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to be formed of subclasses.
     */
    virtual ~DataPoint();

    /**
     * Empties this point of all data. Empty datapoints are useful in category plots because of the relationship between 
     * a datapoint's position in the data series and the category that it corresponds to.
     * 
     * @see IsEmpty();
     */
    virtual void Clear() = 0;

    /**
     * Returns the comment that has been set for this datapoint or an empty string if none has been set.
     * @return The comment for this datapoint or an empty string.
     * @see SetComment();
     */
    virtual const wxString& GetComment() const;

    /**
     * Facilitates direct access to the data held by a data point. Normally used in conjunction with GetDimensionData.
     * @return The number of dimensions in this data point.
     * @see GetDimensionData
     */
    virtual size_t GetDimensionCount() const = 0;

    /**
     * Returns the object for the given dimension in a datapoint. This gives direct access to the data held by a data point. 
     * Normally the convenience functions implemented by specialised versions of DataSet (e.g. UniDataSet, BiDataSet and 
     * NaryDataSet) are used instead which offer the opportunity to interpret the data in a form suitable for plotting.
     * @param dimension The dimension for which to return the data.
     * @return The data held in the specified dimension.
     * @see GetDimensionCount
     * @par Example
     * @code
     * // Example of access using data point access methods directly.
     * wxAny& data = myDataset->GetSeries(1)->GetPoint(52)->GetDimensionData(1);
     * double value = data.As<double>();
     * 
     * // Example access via a DataSet convenience method, 
     * // which includes interpretation of the object as a double:
     * double value = myDataset->GetValue(1, 52, 1);
     * 
     * // Or alternatively for BiDatSet:
     * double value = myDataset->GetFirst(1, 52);
     * 
     * // Example raw (uninterpreted) access via DataSet convenience method:
     * wxAny& data = myDataset->GetRawData(1, 52, 1);
     * double value = data.As<double>();
     * @endcode
     */
    virtual const wxAny& GetDimensionData(size_t dimension) const = 0;

    /**
     * Returns whether this object has any valid data stored.
     * @return `true` if there is no valid data currently stored in this data point, `false` otherwise.
     * @see Clear();
     */
    virtual bool IsEmpty() const;

    /**
     * Sets a comment for this data point. The comment can be shown during mouse hovering or as a callout 
     * on some plots.
     * @param comment The comment for this data point.
     */
    virtual void SetComment(const wxString& comment);

    /**
     * Provides direct access to the data held by the data point in an abstract way (works with
     * data sets of all dimensions). Normally the convenience functions implemented by specialised
     * versions of DataSet (e.g. UniDataSet, BiDataSet and NaryDataSet) are used instead.
     * @param dimension The dimension for which to set the data.
     * @param data The object to be assigned to this data point.
     */
    virtual void SetDimensionData(size_t dimension, const wxAny& data) = 0;

protected:
    bool m_isEmpty;
    wxString m_comment;
};


/***************************************
 * UNI DATA POINT
 ***************************************/

/**
 * Specialisation of DataPoint for all data points with one dimension. 
 * 
 * This a container for a single dimensional data item, such as a percentage, colour or a temperature. Single
 * dimension data can be plotted as a pie chart (PiePlot) or histogram (HistoPlot). If a second axis is inherent in the data, 
 * such as the time at which the temperature reading was taken, then UniDataPoint can be plotted as a bar chart (BarPlot).
 * 
 * Further subclasses can be made from this class or it can be used 'as is'.
 */
class WXDLLIMPEXP_FREECHART UniDataPoint : public DataPoint
{
public:
    /**
     * Default constructor. Instantiates the data point with no data (IsEmpty() will return `true`).
     */
    UniDataPoint();

    /**
     * Instantiates the data point with a double value as valid data. The double value is converted to wxAny with a `double` 
     * template type as valid data. A comment can also be optionally set.
     * @param value The value that is represented by this data point.
     * @param comment A comment about this data point. The comment can be shown during mouse hovering or as a 
     * callout on some plots.
     */
    UniDataPoint(double value, const wxString& comment = wxEmptyString);

    /**
     * Instantiates the data point with valid data. A comment can also be optionally set.
     * @param value The value that is represented by this data point.
     * @param comment A comment about this data point. The comment can be shown during mouse hovering or as a 
     * callout on some plots.
     */
    UniDataPoint(const wxAny& data, const wxString& comment = wxEmptyString);

    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to be formed of subclasses.
     */
    virtual ~UniDataPoint();

    /**
     * Sets a numerical value for this data point. This is a convenience method to access the abstract SetDimensionData with
     * a wxAny object of type `double`.
     * @param value The value that is to be represented by this data point.
     */
    virtual void SetValue(double val);

    // Pure virtual Data Point method implementations.

    virtual void Clear() wxOVERRIDE;

    virtual size_t GetDimensionCount() const wxOVERRIDE;

    /**
     * Returns the object for the given dimension in a datapoint. This gives direct access to the data held by a data point. 
     * Normally the convenience functions implemented by UniDataSet is used instead which offers the opportunity to interpret 
     * the data in a form suitable for plotting.
     * @param dimension The dimension for which to return the data. This must always be `0` for a UniDataPoint specialisation.
     * @return The data held in the specified dimension.
     * @see GetDimensionCount
     * @par Example
     * @code
     * // Example of access using data point access methods directly.
     * wxAny& data = myDataset->GetSeries(1)->GetPoint(52)->GetDimensionData(0);
     * double value = data.As<double>();
     * 
     * // Example access via UniDataSet convenience method, 
     * // which includes interpretation of the object as a double:
     * double value = myDataset->GetValue(1, 52);
     * 
     * // Example raw (uninterpreted) access via DataSet convenience method:
     * wxAny& data = myDataset->GetRawData(1, 52, 0);
     * double value = data.As<double>();
     * @endcode
     * @see UniDataSet::GetValue().
     */
    virtual const wxAny& GetDimensionData(size_t dimension) const wxOVERRIDE;

    virtual void SetDimensionData(size_t dimension, const wxAny& data) wxOVERRIDE;

    // Data holder.
    wxAny data;
};


/***************************************
 * BI DATA POINT
 ***************************************/

class WXDLLIMPEXP_FREECHART BiDataPoint : public DataPoint
{
public:
    /**
     * Default constructor. Instantiates the data point with no data (HasData() will return false).
     */
    BiDataPoint();

    /**
     * Instantiates the data point with valid data and an optional comment.
     * @param first The 'first' value that is represented by this data point.
     * @param second The 'second' value that is represented by this data point.
     * @param comment A comment about this data point. The comment can be shown during
     * mouse hovering or as a callout on some plots.
     */
    BiDataPoint (double first, double second, const wxString& comment = wxEmptyString);

    /**
     * Instantiates the data point with valid data and an optional comment.
     * @param first The 'first' object that is represented by this data point.
     * @param second The 'second' object that is represented by this data point.
     * @param comment A comment about this data point. The comment can be shown during
     * mouse hovering or as a callout on some plots.
     */
    BiDataPoint(const wxAny& first, const wxAny& second, const wxString& comment = wxEmptyString);

    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~BiDataPoint();

    /**
     * Sets the value for this data point.
     *
     * This is a convenience method to access the abstract SetDimensionValue. The values
     * can also be accessed directly as they are public members.
     * @param first The value of the first dimension that is represented by this data point.
     * @param second The value of the second dimension that is represented by this data point.
     */
    virtual void SetValues(double first, double second);

    // Abstract Data Point method implementations.

    virtual void Clear() wxOVERRIDE;

    virtual size_t GetDimensionCount() const wxOVERRIDE;

    virtual const wxAny& GetDimensionData(size_t dimension) const wxOVERRIDE;

    virtual void SetDimensionData(size_t dimension, const wxAny& data) wxOVERRIDE;

    // Data holders.
    wxAny first;
    wxAny second;
};


/***************************************
 * NARY DATA POINT
 ***************************************/

class WXDLLIMPEXP_FREECHART NaryDataPoint : public DataPoint
{
public:
    /**
     * Default constructor. Instantiates the data point with valid data and an optional comment.
     * @param first The 'first' value that is represented by this data point.
     * @param second The 'second' value that is represented by this data point.
     * @param comment A comment about this data point. The comment can be shown during
     * mouse hovering or as a callout on some plots.
     */
    NaryDataPoint (const wxVector<double>& data, const wxString& comment = wxEmptyString);

    /**
     * Default constructor. Instantiates the data point with valid data and an optional comment.
     * @param first The 'first' value that is represented by this data point.
     * @param second The 'second' value that is represented by this data point.
     * @param comment A comment about this data point. The comment can be shown during
     * mouse hovering or as a callout on some plots.
     */
    NaryDataPoint (const wxVector<wxAny>& data, const wxString& comment = wxEmptyString);

    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~NaryDataPoint();

    /**
     * Populate the data point with all dimensions at once.
     * @param data A vector containing objects for all dimensions of the data point.
     */
    virtual void SetData(const wxVector<wxAny>& data);

    /**
     * Populate the data point with all dimensions at once.
     * @param data A vector containing values for all dimensions of the data point.
     */
    virtual void SetData(const wxVector<double>& data);

    // Abstract Data Point method implementations.

    virtual void Clear() wxOVERRIDE;

    virtual size_t GetDimensionCount() const wxOVERRIDE;

    virtual const wxAny& GetDimensionData(size_t dimension) const wxOVERRIDE;

    virtual bool IsEmpty() const wxOVERRIDE;

    virtual void SetDimensionData(size_t dimension, const wxAny& data) wxOVERRIDE;

    wxVector<wxAny> data;
};

#endif // DATAPOINT_H_
