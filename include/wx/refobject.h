#ifndef REFOBJECT_H_
#define REFOBJECT_H_

/**
 * Object with reference counter.
 * DEPRECATED: use wxWidgets reference counting.
 */
class WXDLLEXPORT RefObject
{
public:
	RefObject()
	{
		refCount = 1;
	}

	virtual ~RefObject()
	{
	}

	void AddRef()
	{
		refCount++;
	}

	void Unref()
	{
		refCount--;
		if (refCount < 0) {
			wxLogError(wxT("RefObject::Unref: refCount < 0\n"));
			delete this;
		}
		else if (refCount == 0)
			delete this;
	}

private:
	int refCount;
};

#define SAFE_UNREF(ptr) do {							\
	if (ptr != NULL) {									\
		ptr->Unref();									\
	}													\
	ptr = NULL;											\
} while (0)

#define SAFE_REPLACE_UNREF(dst, src) do {				\
	SAFE_UNREF(dst);									\
	if (src != NULL)									\
		((RefObject *)src)->AddRef();					\
	dst = src;											\
} while (0)

#define SAFE_UNREF_ELEMENTS(arrPtr, arrSize) do {	\
	if (arrPtr != NULL) {								\
		for (int n = 0; n < arrSize; n++) {				\
			SAFE_UNREF(arrPtr[n]);						\
		}												\
		delete arrPtr;									\
		arrPtr = NULL;									\
	}													\
} while (0)

#endif /*REFOBJECT_H_*/
