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
 * A data point represents a unique point on a chart's plot. Data points can be rendered in many
 * different ways as appropriate for a given chart, for example, points on a line, bars, segements
 * of a pie etc.
 *
 * Closely related data points are collected together to form a data series (see DataSeries).
 */
class WXDLLIMPEXP_FREECHART DataPoint : public wxObject
{
public:
    /**
     * Default constructor. Instantiates the data point, but without any data.
     */
    DataPoint (const wxString& comment = wxEmptyString);

    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~DataPoint();

    /**
     * Empties this point of all data. Empty datapoints are useful in category plots because
     * of the relationship between a datapoint's position in the data series and the category
     * that it corresponds to.
     */
    virtual void Clear() = 0;

    /**
     * Returns the comment that has been set for this datapoint or an empty string if none
     * has been set.
     * @return The comment for this datapoint or an empty string.
     */
    virtual const wxString& GetComment() const;

    /**
     * Facilitates direct access to the data held by a data point. Normally used in conjunction with
     * GetDimensionValue.
     * @return The number of dimensions in this data point.
     * @see GetDimensionValue
     */
    virtual size_t GetDimensionCount() const = 0;

    /**
     * Returns the object for the given dimension in a datapoint. This gives direct access to the data
     * held by a data point. Normally the convenience functions implemented by specialised versions
     * of DataSet (e.g. UniDataSet, BiDataSet and NaryDataSet) are used instead.
     * @param dimension The dimension for which to return the data.
     * @return The data held in the specified dimension.
     * @see GetDimensionCount
     */
    virtual const wxAny& GetDimensionData(size_t dimension) const = 0;

    /**
     * Returns the value for the given dimension in a numerical datapoint. This gives direct access to the value
     * held by a data point. Normally the convenience functions implemented by specialised versions
     * of DataSet (e.g. UniDataSet, BiDataSet and NaryDataSet) are used instead.
     * @param dimension The dimension for which to return the value.
     * @return The value held in the specified dimension.
     * @see GetDimensionCount
     */
    virtual double GetDimensionValue(size_t dimension) const = 0;

    /**
     * Returns whether this object has any valid data stored.
     */
    virtual bool HasData() const;

    /**
     * Sets a comment for this data point. The comment can be shown during
     * mouse hovering or as a callout on some plots.
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

    /**
     * Provides direct access to the value held by a numerical data point in an abstract way (works with
     * data sets of all dimensions). Normally the convenience functions implemented by specialised
     * versions of DataSet (e.g. UniDataSet, BiDataSet and NaryDataSet) are used instead.
     * @param dimension The dimension for which to set the data.
     * @param val The value to be set.
     */
    virtual void SetDimensionValue(size_t dimension, double value) = 0;

protected:
    bool m_hasData;
    wxString m_comment;
};


/***************************************
 * UNI DATA POINT
 ***************************************/

/**
 * Base class for all data points with one dimension. Further subclasses can be made from this class
 * or it can be used 'as is'.
 */
class WXDLLIMPEXP_FREECHART UniDataPoint : public DataPoint
{
public:
    /**
     * Default constructor. Instantiates the data point with no data (HasData() will return false).
     */
    UniDataPoint();

    /**
     * Default constructor. Instantiates the data point with valid data and an optional comment.
     * @param value The value that is represented by this data point.
     * @param comment A comment about this data point. The comment can be shown during
     * mouse hovering or as a callout on some plots.
     */
    UniDataPoint (double val, const wxString& comment = wxEmptyString);

    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~UniDataPoint();

    /**
     * Gets the value for this data point.
     * This is a convenience method to access the abstract GetDimensionValue. The value
     * can also be accessed directly as it is a public member.
     * @return The value that is represented by this data point.
     */
    virtual double GetValue() const;


    /**
     * Sets the value for this data point.
     * This is a convenience method to access the abstract SetDimensionValue. The value
     * can also be accessed directly as it is a public member.
     * @param value The value that is to be represented by this data point.
     */
    virtual void SetValue (double val);

    // Abstract Data Point method implementations.

    virtual void Clear() wxOVERRIDE;

    virtual size_t GetDimensionCount() const wxOVERRIDE;

    virtual const wxAny& GetDimensionData(size_t dimension) const wxOVERRIDE;

    virtual double GetDimensionValue(size_t dimension) const wxOVERRIDE;

    virtual void SetDimensionData(size_t dimension, const wxAny& data) wxOVERRIDE;

    virtual void SetDimensionValue(size_t dimension, double val) wxOVERRIDE;

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
     * Default constructor. Instantiates the data point with valid data and an optional comment.
     * @param first The 'first' value that is represented by this data point.
     * @param second The 'second' value that is represented by this data point.
     * @param comment A comment about this data point. The comment can be shown during
     * mouse hovering or as a callout on some plots.
     */
    BiDataPoint (double first,  double second, const wxString& comment = wxEmptyString);

    /**
     * Default destructor. Note that this is a virtual destructor to allow vectors to
     * be formed of subclasses.
     */
    virtual ~BiDataPoint();

    /**
     * Gets the first and second values for this data point.
     *
     * This is a convenience method to access the abstract GetDimensionValue. The values
     * can also be accessed directly as they are public members.
     * @param first The variable into which the first dimension of the data represented by this data point should be copied.
     * @param second The variable into which the second dimension of the data represented by this data point should be copied.
     */
    virtual void GetValues (double& first, double& second) const;

    /**
     * Sets the value for this data point.
     *
     * This is a convenience method to access the abstract SetDimensionValue. The values
     * can also be accessed directly as they are public members.
     * @param first The value of the first dimension that is represented by this data point.
     * @param second The value of the second dimension that is represented by this data point.
     */
    virtual void SetValues (double first, double second);

    // Abstract Data Point method implementations.

    virtual void Clear() wxOVERRIDE;

    virtual size_t GetDimensionCount() const wxOVERRIDE;

    virtual const wxAny& GetDimensionData(size_t dimension) const wxOVERRIDE;

    virtual double GetDimensionValue(size_t dimension) const wxOVERRIDE;

    virtual void SetDimensionData(size_t dimension, const wxAny& data) wxOVERRIDE;

    virtual void SetDimensionValue(size_t dimension, double val) wxOVERRIDE;

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

    virtual double GetDimensionValue(size_t dimension) const wxOVERRIDE;

    virtual bool HasData() const wxOVERRIDE;

    virtual void SetDimensionData(size_t dimension, const wxAny& data) wxOVERRIDE;

    virtual void SetDimensionValue(size_t dimension, double val) wxOVERRIDE;

    wxVector<wxAny> data;
};

#endif // DATAPOINT_H_
