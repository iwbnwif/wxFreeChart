/////////////////////////////////////////////////////////////////////////////
// Name:    dataset.cpp
// Purpose: dataset implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dataset.h>
#include <wx/dataset1.h>

//
// Dataset
//

IMPLEMENT_CLASS(Dataset, wxObject)

wxDEFINE_EVENT(EVT_DATASET_CHANGED, wxCommandEvent);

Dataset::Dataset()
{

}

Dataset::~Dataset()
{

}



