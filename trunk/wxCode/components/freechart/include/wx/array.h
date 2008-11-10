#ifndef ARRAY_H_
#define ARRAY_H_

#include <string.h>

#include <wx/wxfreechartdefs.h>
#include <wx/refobject.h>

/**
 * Array holding array of T pointers.
 * This class manages lifetime of elements within it.
 * DEPRECATED: must be replaced by wxWidgets array classes.
 */
template <class T, int chunkSize, bool refs = false>
class Array
{
public:
	typedef T *TPtr;

	Array()
	{
		array = NULL;
		size = 0;
		reservedSize = 0;
		owns = true;
		//refs = false;
	}

	virtual ~Array()
	{
		RemoveAll();
	}

	void NotOwns()
	{
		owns = false;
	}

/*
	void Refs()
	{
		refs = true;
	}
*/

	void RemoveAll()
	{
		if (refs) {
			SAFE_DELETE(array);
		}
		else {
			if (owns) {
				SAFE_DELETE_WITH_ELEMENTS(array, size);
			}
			else {
				SAFE_DELETE(array);
			}
		}

		size = 0;
		reservedSize = 0;
	}

	void Add(T *element)
	{
		if (reservedSize == 0) {
			T **newArray = new TPtr[size + chunkSize];

			if (array != NULL) {
				memcpy(newArray, array, size * sizeof(TPtr));
				delete array;
			}

			reservedSize = chunkSize;
			array = newArray;
		}

		array[size] = element;

		if (refs) {
			((RefObject *) element)->AddRef();
		}

		size++;
		reservedSize--;
	}

	void RemoveAt(int index)
	{
		wxCHECK_RET(index < size, wxT("Array::RemoveAt"));

		if (owns) {
			delete array[index];
		}

		for (int n = index; n < size - 1; n++) {
			array[n] = array[n + 1];
		}

		size--;
		reservedSize++;
	}

	int GetSize()
	{
		return size;
	}

	void Shrink(int _size)
	{
		if (array == NULL)
			return ;
		if (size <= _size)
			return ; // nothing to do

		for (int n = _size - 1; n < size; n++) {
			SAFE_DELETE(array[n]);
		}

		T **newArray = new TPtr[_size + chunkSize];
		memcpy(newArray, array, _size * sizeof(TPtr));
		delete array;

		reservedSize = chunkSize;
		array = newArray;
		size = _size;
	}

	T *operator[] (int index)
	{
		wxCHECK_MSG(index < size, NULL, wxT("Array::Get"));
		return array[index];
	}

	T *Last()
	{
		if (size == 0)
			return NULL;

		return operator[] (size - 1);
	}

private:
	T **array;

	int size;
	int reservedSize;

	bool owns;
	//bool refs;
};

#endif /*ARRAY_H_*/
