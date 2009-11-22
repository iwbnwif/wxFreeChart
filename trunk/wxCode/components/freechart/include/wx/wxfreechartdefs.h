/////////////////////////////////////////////////////////////////////////////
// Name:	wxfreechartdefs.h
// Purpose: base declarations
// Author:	Moskvichev Andrey V.
// Created:	2008/11/07
// RCS-ID:	$Id: wxAdvTable.h,v 1.3 2008/11/07 16:42:58 moskvichev Exp $
// Copyright:	(c) 2008-2009-2009 Moskvichev Andrey V.
// Licence:	wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef WXFREECHARTDEFS_H
#define WXFREECHARTDEFS_H

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// dll impexp macros. Thanks to Mike Sazonov
#ifdef WXMAKINGDLL_FREECHART
#define WXDLLIMPEXP_FREECHART WXEXPORT
#define WXDLLIMPEXP_DATA_FREECHART(type) WXEXPORT type
#elif defined(WXUSINGDLL) && !defined(_LOCAL_)
#define WXDLLIMPEXP_FREECHART WXIMPORT
#define WXDLLIMPEXP_DATA_FREECHART(type) WXIMPORT type
#else // not making nor using DLL
#define WXDLLIMPEXP_FREECHART
#define WXDLLIMPEXP_DATA_FREECHART(type) type
#endif

#define ABS(a) ((a) < 0) ? (-1*(a)) : (a)


#define wxREPLACE(dst, src) do {					\
	wxDELETE(dst);									\
	dst = src;										\
} while (0)

inline static double *NewZeroDoubleArray(int size)
{
	double *array = new double[size];

	for (int n = 0; n < size; n++) {
		array[n] = 0;
	}
	return array;
}

inline static int RoundHigh(double value)
{
	int iv = (int) value;

	if (((double) iv) > value)
		iv++;
	return iv;
}

static inline int maxV(int count, int first, ...)
{
	int maxValue = first;
	int n;
	va_list args;

	va_start(args, first);

	for (n = 1; n < count; n++) {
		int value = va_arg(args, int);
		maxValue = wxMax(maxValue, value);
	}
	va_end(args);
	return maxValue;
}

#endif /* WXFREECHARTDEFS_H */
