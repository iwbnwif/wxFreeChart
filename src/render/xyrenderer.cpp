/////////////////////////////////////////////////////////////////////////////
// Name:    xyrenderer.cpp
// Purpose: xy renderer implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/render/xyrenderer.h>

IMPLEMENT_CLASS(XYRenderer, Renderer)

XYRenderer::XYRenderer()
{
}

XYRenderer::~XYRenderer()
{
}

double XYRenderer::GetMax(const BiDataSet* dataset, size_t dimension) const
{
    wxASSERT(dataset);
    
    return dataset->GetMaxValue1(dimension);
}

double XYRenderer::GetMin(const BiDataSet* dataset, size_t dimension) const
{
    wxASSERT(dataset);
    
    return dataset->GetMinValue1(dimension);
}