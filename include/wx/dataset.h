/////////////////////////////////////////////////////////////////////////////
// Name:    dataset.h
// Purpose: dataset base class declarations
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATASET_H_
#define DATASET_H_

#include <wx/wxfreechartdefs.h>

#include <wx/dynarray.h>
#include <wx/refobject.h>

#include <wx/marker.h>
#include <wx/render/chartrenderer.h>

class Dataset;
class DateTimeDataset;

/**
 * Base class for all datasets (XYDatasets, XYZDatasets, CategoryDatasets, OHLCDatasets, etc).
 *
 */
class WXDLLIMPEXP_FREECHART Dataset : public wxEvtHandler, public RefObject
{
    DECLARE_CLASS(Dataset)
public:
    Dataset();
    virtual ~Dataset();



protected:

private:

};

#endif /*DATASET_H_*/
