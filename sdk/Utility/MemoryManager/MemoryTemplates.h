
#ifndef MEMORYMGR_H_
#define MEMORYMGR_H_

#include "Macros.h"

#include <cstddef>
#include <algorithm>
#include <iostream>
#include <cstddef>

using namespace std;

template <typename T>
T *reallocEM(T *array, size_t old_size, size_t new_size)
{
   T *temp = new T[new_size];

   delete [] array;
   
   return copy(array, array + old_size, temp);
}


template <typename T>
bool SafeAlloc(T* &ptr, size_t cnt)
{
	_ASSERT(!ptr);
	if(cnt)
	{
		ptr = new T[cnt * sizeof(T)];
		_ASSERT(ptr);
		if(!ptr)
			return false;
	}
	
	memset(ptr, 0, cnt *sizeof(T));

	return true;
}

template <typename T>
void SafeRealloc(T* &ptr, size_t cnt)
{
   // simulate what realloc would do
   // allocate enough so that the old and the new memory have space
   T *temp = new T[cnt * sizeof(T)];
   
   size_t old_size = sizeof(*ptr);
   
   // delete old memory
   delete [] ptr;
   
   // copy temp starting whereever ptr has started before
   copy(ptr, ptr + old_size, temp);

 	_ASSERT(ptr);
}

//char* StrDup(const char *string);
#endif
