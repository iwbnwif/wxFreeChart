/////////////////////////////////////////////////////////////////////////////
// Name:    categoryaxis.cpp
// Purpose: category axis implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/axis/categoryaxis.h>
#include <wx/dataset1.h>

IMPLEMENT_CLASS(CategoryAxis, Axis)

CategoryAxis::CategoryAxis(AXIS_LOCATION location)
: LabelAxis(location)
{
    m_categoryCount = 0;
}

CategoryAxis::~CategoryAxis()
{
}

bool CategoryAxis::AcceptDataset(DataSet* dataset)
{
    return (wxDynamicCast(dataset, UniDataSet)
                && m_datasets.Count() == 0);
}

wxSize CategoryAxis::GetLongestLabelExtent(wxDC &dc)
{
    dc.SetFont(GetLabelTextFont());
    return dc.GetTextExtent(m_longestCategory);
}

void CategoryAxis::GetDataBounds(double &minValue, double &maxValue) const
{
    minValue = 0;
    if (m_categoryCount > 1) {
        maxValue = m_categoryCount - 1;
    }
    else {
        maxValue = 0;
    }
}

bool CategoryAxis::UpdateBounds()
{
    UniDataSet *dataset = wxDynamicCast(m_datasets[0], UniDataSet);
    if (dataset == NULL) {
        wxLogError(wxT("CategoryAxis::UpdateBounds: Dataset is not UniDataSet")); // BUG!
        return false;
    }

    m_categoryCount = dataset->GetBaseCount();

    m_longestCategory = dataset->GetBaseValue(0).As<wxString>();
    for (size_t nCat = 1; nCat < m_categoryCount; nCat++) {
        wxString catName = dataset->GetBaseValue(nCat).As<wxString>();

        if (m_longestCategory.Length() < catName.Length()) {
            m_longestCategory = catName;
        }
    }

    return true;
}

double CategoryAxis::GetValue(size_t step)
{
    if (IsVertical()) {
        step = m_categoryCount - 1 - step;
    }
    return step;
}

void CategoryAxis::GetLabel(size_t step, wxString &label)
{
    wxASSERT(wxDynamicCast(m_datasets[0], UniDataSet));
    UniDataSet* dataset = wxDynamicCast(m_datasets[0], UniDataSet);

    if (IsVertical())
        step = m_categoryCount - 1 - step;

    label = dataset->GetBaseSeries()[step].As<wxString>();
}

bool CategoryAxis::IsEnd(size_t step)
{
    return step >= m_categoryCount;
}
