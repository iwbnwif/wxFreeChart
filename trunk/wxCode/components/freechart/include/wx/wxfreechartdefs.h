
#ifndef WXFREECHARTDEFS_H
#define WXFREECHARTDEFS_H

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


#define ABS(a) ((a) < 0) ? (-1*(a)) : (a)

#ifndef MAX
#define MAX(a,b)	    (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)	    (((a) < (b)) ? (a) : (b))
#endif

#ifndef N
#define N(arr) sizeof(arr) / sizeof(*arr)
#endif /* N */

#define SAFE_DELETE(ptr) if (ptr != NULL) { delete ptr; ptr = NULL; }

#define SAFE_DELETE_WITH_ELEMENTS(arrPtr, arrSize) do { \
	if (arrPtr != NULL) {								\
		for (int n = 0; n < arrSize; n++) {				\
			SAFE_DELETE(arrPtr[n]);						\
		}												\
		delete arrPtr;									\
		arrPtr = NULL;									\
	}													\
} while (0)

#define SAFE_REPLACE(dst, src) do {					\
	SAFE_DELETE(dst);									\
	dst = src;											\
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
		maxValue = MAX(maxValue, value);
	}
	va_end(args);
	return maxValue;
}

#endif /* WXFREECHARTDEFS_H */
