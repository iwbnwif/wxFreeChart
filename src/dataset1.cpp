/////////////////////////////////////////////////////////////////////////////
// Name:        dataeet.cpp
// Purpose:     Default data set classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dataset1.h>
#include <wx/plot/ohlcplot.h> // For OHLCItem.
#include <wx/render/xylinerenderer.h> // For clip axis helpers.

#include "wx/arrimpl.cpp" // For DatasetArray.

wxDEFINE_EVENT(EVT_DATASET_CHANGED, wxCommandEvent);

/***************************************
 * DATA INTERPRETER
 ***************************************/
DataInterpreter::DataInterpreter()
{
}

DataInterpreter::~DataInterpreter()
{
}

wxAny DataInterpreter::AsAny(double value, size_t dimension, int options) const
{
    return wxAny(value);
}

wxAny DataInterpreter::AsAny(const wxAny& data, size_t dimension, int options) const
{
    return data;
}

double DataInterpreter::AsValue(const wxAny& data, size_t dimension, int options) const
{
    if (data.CheckType<int>())
        return data.As<int>();
        
    if (data.CheckType<long>())
        return data.As<long>();
        
    if (data.CheckType<float>())
        return data.As<float>();
        
    if (data.CheckType<double>())
        return data.As<double>();
        
    if (data.CheckType<wxDateTime>())
        return data.As<wxDateTime>().GetTicks();
        
    if (data.CheckType<OHLCItem>())
    {
        if (options == 0)
            return data.As<OHLCItem>().high;
        else
            return data.As<OHLCItem>().low;
    }
        
    wxFAIL_MSG("Unsupported wxAny type.");
    return 0.0;
}

DataTypeTrait DataInterpreter::GetTrait(const wxAny& data, size_t dimension) const
{
    if (data.CheckType<int>())
        return TypeTraitRatio;
        
    if (data.CheckType<long>())
        return TypeTraitRatio;
        
    if (data.CheckType<float>())
        return TypeTraitRatio;
        
    if (data.CheckType<double>())
        return TypeTraitRatio;
        
    if (data.CheckType<wxDateTime>())
        return TypeTraitRatio;
        
    if (data.CheckType<OHLCItem>())
        return TypeTraitRatio;

    return TypeUndefined;
}

/***************************************
 * DATA INTERPRETER
 ***************************************/
DataItemLocator::DataItemLocator(size_t dataset, size_t series, size_t index, bool valid)
{
    m_dataset = dataset;
    m_series = series;
    m_index = index;
    m_valid = valid;
}

size_t DataItemLocator::GetDataset()
{
    return m_dataset;
}

size_t DataItemLocator::GetSeries()
{
    return m_series;
}

size_t DataItemLocator::GetIndex()
{
    return m_index;
}

bool DataItemLocator::IsValid()
{
    return m_valid;
}


void ClipHoriz(Axis *axis, double &x, double &y, double x1, double y1)
{
    if (!axis->IsVisible(x)) {
        double p = axis->BoundValue(x);
        y = (y1 - y) * (p - x) / (x1 - x) + y;
        x = p;
    }
}

void ClipVert(Axis *axis, double &x, double &y, double x1, double y1)
{
    if (!axis->IsVisible(y)) {
        double p = axis->BoundValue(y);
    x = (p - y) * (x1 - x) / (y1 - y) + x;
        y = p;
    }
}

/***************************************
 * DATA SET
 ***************************************/
DataSet::DataSet (const wxString& name)
{
    m_interpreter = new DataInterpreter();
    
    m_renderer = NULL;
    m_updating = false;
    m_changed = false;
}

DataSet::~DataSet()
{
     for (size_t n = 0; n < m_markers.Count(); n++) 
    {
        Marker *marker = m_markers[n];
        wxDELETE(marker);
    }

    SAFE_UNREF(m_renderer);   
    
    delete m_interpreter;
}

inline size_t DataSet::GetSeriesSize(size_t series) const
{
    return m_series.at(series)->GetSize();
}

inline DataInterpreter* DataSet::GetInterpreter() const
{
    return m_interpreter;
}

double DataSet::GetMaxValue1(size_t dimension) const
{
    wxASSERT(GetSeriesCount() > 0 && GetSeriesSize(0) > 0);
    
    double max = InterpretAsValue(0, 0, dimension, 0);
    
    for (size_t ser = 0; ser < GetSeriesCount(); ser++)
    {
        for (size_t pt = 0; pt < GetSeriesSize(ser); pt++)
            max = wxMax(max, InterpretAsValue(ser, pt, dimension, 0));
    }
    
    return max;
}

double DataSet::GetMinValue1(size_t dimension) const
{
    wxASSERT(GetSeriesCount() > 0 && GetSeriesSize(0) > 0);
    
    double min = InterpretAsValue(0, 0, dimension, 1);
    
    for (size_t ser = 0; ser < GetSeriesCount(); ser++)
    {
        for (size_t pt = 0; pt < GetSeriesSize(ser); pt++)
            min = wxMin(min, InterpretAsValue(ser, pt, dimension, 1));
    }
    
    return min;
}

inline const wxString& DataSet::GetName() const
{
    return m_name;
}

inline const wxSharedPtr<DataPoint> DataSet::GetPoint(size_t series, size_t index, size_t dimension) const
{
    return GetSeries(series)->GetPoint(index);
}

inline const wxAny& DataSet::GetPointData(size_t series, size_t index, size_t dimension) const
{
    return GetSeries(series)->GetPoint(index)->GetDimensionData(dimension);
}

inline const double DataSet::GetPointValue(size_t series, size_t index, size_t dimension) const
{
    const wxAny& data = GetPointData(series, index, dimension);
    wxASSERT(GetInterpreter()->GetTrait(data, dimension) != TypeUndefined);
    
    return GetInterpreter()->AsValue(data, dimension);
}

Renderer* DataSet::GetRenderer()
{
    return m_renderer;
}

const Renderer* DataSet::GetRenderer() const
{
    return m_renderer;
}

inline const wxSharedPtr<DataSeries> DataSet::GetSeries(size_t index) const
{
    return m_series.at(index);
}

inline const size_t DataSet::GetSeriesCount() const
{
    return m_series.size();
}

bool DataSet::AcceptRenderer(Renderer* r)
{
    return true;
}

DataSeries* DataSet::AddSeries(DataSeries* series)
{
    m_series.push_back(wxSharedPtr<DataSeries>(series));
    
    return series;
}

wxString DataSet::GetSeriesName (size_t serie) const
{
    return m_series.at(serie)->GetName();
}

void DataSet::SetInterpreter(DataInterpreter* interpreter)
{
    wxREPLACE(m_interpreter, interpreter);
}

void DataSet::SetName (const wxString& name)
{
}

inline const wxAny DataSet::InterpretAsAny(size_t series, size_t index, size_t dimension, int options) const
{
    return m_interpreter->AsAny(GetPointData(series, index, dimension), dimension, options);
}

inline const wxAny DataSet::InterpretValueAsAny(size_t series, size_t index, size_t dimension, int options) const
{
   return m_interpreter->AsAny(GetPointValue(series, index, dimension), dimension, options);
}

inline double DataSet::InterpretAsValue(size_t series, size_t index, size_t dimension, int options) const
{
    return m_interpreter->AsValue(GetPointData(series, index, dimension), dimension, options);
}

void DataSet::SetRenderer(Renderer *renderer)
{
    SAFE_REPLACE_UNREF(m_renderer, renderer);
    DatasetChanged();
}

Renderer *DataSet::GetBaseRenderer()
{
    return m_renderer;
}

void DataSet::NeedRedraw(DrawObject *WXUNUSED(obj))
{
    DatasetChanged();
}

void DataSet::BeginUpdate()
{
    m_updating = true;
}

void DataSet::EndUpdate()
{
    if (m_updating) {
        m_updating = false;
        if (m_changed) 
        {
            DatasetChanged();
        }
    }
}

void DataSet::DatasetChanged()
{
    if (m_updating)
        m_changed = true;

    else 
    {
        wxQueueEvent(this, new wxCommandEvent(EVT_DATASET_CHANGED));
        m_changed = false;
    }
}

void DataSet::AddMarker(Marker *marker)
{
    m_markers.Add(marker);
}

size_t DataSet::GetMarkersCount()
{
    return m_markers.Count();
}

Marker *DataSet::GetMarker(size_t index)
{
    return m_markers[index];
}

/***************************************
 * DATA SET ARRAY
 ***************************************/

WX_DEFINE_EXPORTED_OBJARRAY(DatasetArrayBase)

DatasetArray::DatasetArray()
{
}

DatasetArray::~DatasetArray()
{
    for (size_t n = 0; n < Count(); n++) {
        DataSet* dataset = Item(n);
        SAFE_UNREF(dataset);
    }
}

void DatasetArray::Add(DataSet* dataset)
{
    dataset->AddRef();
    DatasetArrayBase::Add(dataset);
}

void DatasetArray::Remove(DataSet *dataset)
{
    SAFE_UNREF(dataset);
    DatasetArrayBase::Remove(dataset);
}

void DatasetArray::RemoveAt(size_t index, size_t count)
{
    for (size_t n = index; n < index + count; n++) {
        DataSet* dataset = Item(n);
        SAFE_UNREF(dataset);
    }

    DatasetArrayBase::RemoveAt(index, count);
}

/***************************************
 * UNI DATA SET
 ***************************************/
UniDataSet::UniDataSet (const wxString& name)
{
}

UniDataSet::~UniDataSet()
{
}

void UniDataSet::AddCategory(const wxAny& category)
{
    m_baseSeries.push_back(category);
}

size_t UniDataSet::GetBaseCount()
{
    return m_baseSeries.size();
}

const wxVector<wxAny>& UniDataSet::GetBaseSeries() const
{
    return m_baseSeries;
}

const wxAny& UniDataSet::GetBaseValue(size_t index) const
{
    return m_baseSeries[index];
}

double UniDataSet::GetMaxValue(bool vertical) const
{
    return GetMaxValue1(0);
}

double UniDataSet::GetMinValue(bool vertical) const
{
    return GetMinValue1(0);
}

double UniDataSet::GetValue(size_t series, size_t index) const
{
    return m_series[series]->GetPoint(index).get()->GetDimensionValue(0);
}


/***************************************
 * BI DATA SET
 ***************************************/
BiDataSet::BiDataSet (const wxString& name)
{
    m_name = name;
}

BiDataSet::~BiDataSet()
{
}

double BiDataSet::GetFirst(size_t series, size_t index)
{
    return m_series[series]->GetPoint(index).get()->GetDimensionValue(0);
}

double BiDataSet::GetSecond(size_t series, size_t index)
{
    return m_series[series]->GetPoint(index).get()->GetDimensionValue(1);
}

double BiDataSet::GetMaxValue(bool vertical) const
{
    return GetMaxValue1(vertical ? 1 : 0);
}

double BiDataSet::GetMinValue(bool vertical) const
{
    return GetMinValue1(vertical ? 1 : 0);
}

/***************************************
 * NARY DATA SET
 ***************************************/
NaryDataSet::NaryDataSet (const wxString& name)
{
}

NaryDataSet::~NaryDataSet()
{
}

double NaryDataSet::GetMaxValue(bool vertical) const
{
    return GetMaxValue1(vertical ? 1 : 0);
}

double NaryDataSet::GetMinValue(bool vertical) const
{
    return GetMinValue1(vertical ? 1 : 0);
}
