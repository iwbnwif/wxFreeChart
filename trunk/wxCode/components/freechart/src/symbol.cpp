
/////////////////////////////////////////////////////////////////////////////
// Name:	symbol.cpp
// Purpose:
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/symbol.h>

Symbol::Symbol()
{
}

Symbol::~Symbol()
{
}

void Symbol::SetColor(wxColour _color)
{
	// default behaviour - do nothing
}

MaskedSymbol::MaskedSymbol(const char **maskData, wxCoord _size)
{
	maskBmp = wxBitmap(maskData);
	size = _size;

	initialized = false;
}

MaskedSymbol::~MaskedSymbol()
{
}

void MaskedSymbol::SetColor(wxColour color)
{
	wxImage tmpImage = maskBmp.ConvertToImage();
	tmpImage.Replace((unsigned char) -1, (unsigned char) -1, (unsigned char)  -1, color.Red(), color.Green(), color.Blue());
	tmpImage.Rescale(size, size, wxIMAGE_QUALITY_HIGH);

	symbolBitmap = wxBitmap(tmpImage);
	symbolBitmap.SetMask(new wxMask(wxBitmap(tmpImage), *wxBLACK));
	initialized = true;
}

wxSize MaskedSymbol::GetExtent()
{
	return wxSize(size, size);
}

void MaskedSymbol::Draw(wxDC &dc, wxCoord x, wxCoord y)
{
	if (!initialized)
		return ;

	wxSize extent = GetExtent();
	wxMemoryDC symbolDC(symbolBitmap);

	dc.Blit(x - extent.x / 2, y - extent.y / 2, extent.x, extent.y, &symbolDC, 0, 0, wxCOPY, true);
}
