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

#endif // DATASERIES_H_    