/////////////////////////////////////////////////////////////////////////////
// Name:        dataeet.cpp
// Purpose:     Default data set classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dataset1.h>

#include <wx/xy/xylinerenderer.h>

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

    return TypeUndefined;
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
}

DataSet::~DataSet()
{
    delete m_interpreter;
}

inline size_t DataSet::GetCount(size_t serie) const
{
    return m_series.at(serie)->GetCount();
}

double DataSet::GetMaxValue1(size_t series, size_t dimension) const
{
    wxASSERT(series < GetSerieCount() && GetCount(series) > 0);
    
    double max = InterpretDataAsValue(series, 0, dimension);
    
    for (size_t pt = 0; pt < GetCount(series); pt++)
    {
        max = wxMax(max, InterpretDataAsValue(series, pt, dimension));
    }
    
    return max;
}

double DataSet::GetMinValue1(size_t series, size_t dimension) const
{
    wxASSERT(series < GetSerieCount() && GetCount(series) > 0);
    
    double min = InterpretDataAsValue(series, 0, dimension);
    
    for (size_t pt = 0; pt < GetCount(series); pt++)
    {
        min = wxMin(min, InterpretDataAsValue(series, pt, dimension));
    }
    
    return min;
}

inline const wxString& DataSet::GetName() const
{
    return m_name;
}

inline DataInterpreter* DataSet::GetInterpreter() const
{
    return m_interpreter;
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

void DataSet::AddSeries(DataSeries* series)
{
    m_series.push_back(wxSharedPtr<DataSeries>(series));
}

size_t DataSet::GetSerieCount() const
{
    return GetSeriesCount();
}

wxString DataSet::GetSerieName (size_t serie) const
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

inline const wxAny DataSet::InterpretDataAsAny(size_t series, size_t index, size_t dimension) const
{
    return m_interpreter->AsAny(GetPointData(series, index, dimension), dimension);
}

inline const wxAny DataSet::InterpretValueAsAny(size_t series, size_t index, size_t dimension) const
{
   return m_interpreter->AsAny(GetPointValue(series, index, dimension), dimension);
}

inline double DataSet::InterpretDataAsValue(size_t series, size_t index, size_t dimension) const
{
    return m_interpreter->AsValue(GetPointData(series, index, dimension), dimension);
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
    double max = GetValue(0, 0);
    
    for (size_t ser = 0; ser < GetSerieCount(); ser++)
    {
        for (size_t pt = 0; pt < GetCount(ser); pt++)
            max = wxMax(max, GetValue(ser, pt));
    }
    
    return max;       
}

double UniDataSet::GetMinValue(bool vertical) const
{
    double min = GetValue(0, 0);
    
    for (size_t ser = 0; ser < GetSerieCount(); ser++)
    {
        for (size_t pt = 0; pt < GetCount(ser); pt++)
            min = wxMin(min, GetValue(ser, pt));
    }
    
    return min;       
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

const XYRenderer* BiDataSet::GetRenderer() const
{
    return wxDynamicCast(m_renderer, XYRenderer);
}

XYRenderer* BiDataSet::GetRenderer()
{
    return wxDynamicCast(m_renderer, XYRenderer);
}

double BiDataSet::GetMaxValue(bool vertical) const
{
    wxASSERT_MSG(GetRenderer(), "Attempting to plot data without an associated renderer");
    
    const XYRenderer* renderer = GetRenderer();
    
    return renderer->GetMax(this, vertical ? 1 : 0);
}

double BiDataSet::GetMinValue(bool vertical) const
{
    wxASSERT_MSG(GetRenderer(), "Attempting to plot data without an associated renderer");
    
    return GetRenderer()->GetMin(this, vertical ? 1 : 0);
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

Renderer* NaryDataSet::GetRenderer()
{
    return m_renderer;
}

const Renderer* NaryDataSet::GetRenderer() const
{
    return m_renderer;
}

double NaryDataSet::GetMaxValue(bool vertical) const
{
    double max = GetMaxValue1(0, vertical ? 1 : 0);

    for (size_t ser = 0; ser < GetSerieCount(); ser++)
        max = wxMax(max, GetMaxValue1(ser, vertical ? 1 : 0));
        
    return max;
}

double NaryDataSet::GetMinValue(bool vertical) const
{
    double min = GetMaxValue1(0, vertical ? 1 : 0);

    for (size_t ser = 0; ser < GetSerieCount(); ser++)
        min = wxMin(min, GetMinValue1(ser, vertical ? 1 : 0));
        
    return min;
}