
// COS30008, Tutorial 10, 2022

#pragma once

#include <stdexcept>

#include <iostream>

template<class T>
class Handle
{
private:
    T* fPointer;
    size_t* fCount;

    void addRef()
	{
		if (fCount != nullptr)
		{
			(*fCount)++;
		}
	}

    void releaseRef()
    {
		if (fCount != nullptr)
		{
			if ((*fCount)-- == 0)
			{
				delete fPointer;
				delete fCount;
			}
		}
	}

public:
	Handle(T* aPointer = nullptr)
	{
		fPointer = aPointer;
		fCount = new size_t(1);
	}

	~Handle()
	{
		releaseRef();
	}

	Handle(const Handle<T>& aOtherHandle)
	{
		fPointer = aOtherHandle.fPointer;
		fCount = aOtherHandle.fCount;
		addRef();
	}

	Handle& operator=(Handle<T>& aOtherHandle)
	{
		if (this != &aOtherHandle)
		{
			// release current reference
			releaseRef();
			fPointer = aOtherHandle.fPointer;
			fCount = aOtherHandle.fCount;
			// add new reference
			addRef();
		}
	}

    T& operator*()
	{
		if (fPointer == nullptr)
		{
			throw std::runtime_error("Dereference of unbound handle!");
		}

		return *fPointer;
	}

    T* operator->()
	{
		if (fPointer == nullptr)
		{
			throw std::runtime_error("Access through unbound handle!");
		}

		return fPointer;
	}
};