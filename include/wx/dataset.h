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

#include <time.h>

class Dataset;
class DateTimeDataset;

wxDECLARE_EVENT(EVT_DATASET_CHANGED, wxCommandEvent);        

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

    /**
     * Sets renderer for this dataset.
     * @param renderer new renderer
     */
    void SetRenderer(Renderer *renderer);

    Renderer *GetBaseRenderer();

    /**
     * Called to begin dataset update.
     * Each call must have corresponding EndUpdate call.
     * Increment dataset update counter.
     */
    void BeginUpdate();

    /**
     * Called to end dataset update.
     * Decrement dataset update counter, and fires
     * DatasetChanged event when counter equal zero.
     */
    void EndUpdate();

    /**
     * Adds marker to plot. Plot takes ownership of marker.
     * @param marker marker to be added
     */
    void AddMarker(Marker *marker);

    /**
     * Returns marker count.
     * @return marker count
     */
    size_t GetMarkersCount();

    /**
     * Returns marker at specified index.
     * @param index index of marker
     * @return marker at specified index
     */
    Marker *GetMarker(size_t index);

    //
    // DrawObjectObserver
    //
    // Received from renderer, or marker
    virtual void NeedRedraw(DrawObject *obj);

    /**
     * Called to indicate, that dataset is changed.
     * For call by derivate classes.
     */
    void DatasetChanged();

protected:
    /**
     * Checks whether renderer is acceptable by this dataset.
     */
    virtual bool AcceptRenderer(Renderer *r) = 0;

    Renderer *m_renderer;
private:
    bool m_updating;
    bool m_changed;

    MarkerArray m_markers;
};

WX_DECLARE_USER_EXPORTED_OBJARRAY(DataSet*, DatasetArrayBase, WXDLLIMPEXP_FREECHART);

class WXDLLIMPEXP_FREECHART DatasetArray : public DatasetArrayBase
{
public:
    DatasetArray();
    virtual ~DatasetArray();

    void Add(DataSet* dataset);

    void Remove(DataSet* dataset);

    void RemoveAt(size_t index, size_t count = 1);
};

#endif /*DATASET_H_*/
