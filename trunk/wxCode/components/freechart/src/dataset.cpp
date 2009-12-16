/////////////////////////////////////////////////////////////////////////////
// Name:	dataset.cpp
// Purpose: dataset implementation
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// Copyright:	(c) 2008-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dataset.h>

#include "wx/arrimpl.cpp"

IMPLEMENT_CLASS(Dataset, wxObject)

DatasetObserver::DatasetObserver()
{
}

DatasetObserver::~DatasetObserver()
{
}

Dataset::Dataset()
{
	m_renderer = NULL;
	m_updating = false;
	m_changed = false;
}

Dataset::~Dataset()
{
	SAFE_UNREF(m_renderer);
}

void Dataset::SetRenderer(Renderer *renderer)
{
	SAFE_REPLACE_OBSERVER(this, m_renderer, renderer);
	SAFE_REPLACE_UNREF(m_renderer, renderer);
	DatasetChanged();
}

Renderer *Dataset::GetBaseRenderer()
{
	return m_renderer;
}

void Dataset::NeedRedraw(DrawObject *WXUNUSED(obj))
{
	FireDatasetChanged();
}

void Dataset::BeginUpdate()
{
	m_updating = true;
}

void Dataset::EndUpdate()
{
	if (m_updating) {
		m_updating = false;
		FireDatasetChanged();
	}
}

void Dataset::DatasetChanged()
{
	if (m_updating) {
		m_changed = true;
	}
	else {
		m_changed = false;
		FireDatasetChanged();
	}
}

DateTimeDataset *Dataset::AsDateTimeDataset()
{
	return NULL; // dataset not supports date/times by default.
}

DateTimeDataset::DateTimeDataset()
{
}

DateTimeDataset::~DateTimeDataset()
{
}

//
// DatasetArray
//

WX_DEFINE_EXPORTED_OBJARRAY(DatasetArrayBase)

DatasetArray::DatasetArray()
{
}

DatasetArray::~DatasetArray()
{
	for (size_t n = 0; n < Count(); n++) {
		Dataset *dataset = Item(n);
		SAFE_UNREF(dataset);
	}
}

void DatasetArray::Add(Dataset *dataset)
{
	dataset->AddRef();
	DatasetArrayBase::Add(dataset);
}

void DatasetArray::Remove(Dataset *dataset)
{
	SAFE_UNREF(dataset);
	DatasetArrayBase::Remove(dataset);
}

void DatasetArray::RemoveAt(size_t index, size_t count)
{
	for (size_t n = index; n < index + count; n++) {
		Dataset *dataset = Item(n);
		SAFE_UNREF(dataset);
	}

	DatasetArrayBase::RemoveAt(index, count);
}
