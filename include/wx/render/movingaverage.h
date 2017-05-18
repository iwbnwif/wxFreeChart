/////////////////////////////////////////////////////////////////////////////
// Name:    movingavg.h
// Purpose: moving average declaration
// Author:    Moskvichev Andrey V.
// Created:    2010/12/17
// Copyright:    (c) 2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef MOVINGAVERAGE_H_
#define MOVINGAVERAGE_H_

#include <wx/dataset1.h>

/**
 * Simple moving average indicator.
 */
class WXDLLIMPEXP_FREECHART MovingAverage : public BiDataSet
{
    DECLARE_CLASS(MovingAverage)
public:
    /**
     * Creates new moving average dataset.
     * @param ohlcDataset OHLC dataset, from which to calculate moving avg
     * @param period moving avg period
     */
    MovingAverage(BiDataSet* dataset, int period);
    virtual ~MovingAverage();

    virtual size_t GetSerieCount() const;

    virtual wxString GetSerieName(size_t serie) const;

    virtual size_t GetCount(size_t serie) const;

    virtual double GetX(size_t index, size_t serie) const;

    virtual double GetY(size_t index, size_t serie) const;

    //
    // DatasetObserver
    //
    virtual void DatasetChanged(Dataset *dataset);

private:
    BiDataSet* m_SourceDataset;
    int m_period;
};

#endif /* MOVINGAVERAGE_H_ */
