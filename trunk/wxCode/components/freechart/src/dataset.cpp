
/////////////////////////////////////////////////////////////////////////////
// Name:	dataset.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/dataset.h>

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

void Dataset::NeedRedraw(DrawObject *obj)
{
	FireDatasetChanged();
}

void Dataset::BeginUpdate()
{
	m_updating = true;
}

void Dataset::EndUpdate()
{
	m_updating = false;
	FireDatasetChanged();
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


ValueRange::ValueRange()
{
}

ValueRange::~ValueRange()
{
}


DateTimeDataset::DateTimeDataset()
{
}

DateTimeDataset::~DateTimeDataset()
{
}
