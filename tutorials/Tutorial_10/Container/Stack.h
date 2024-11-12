
// COS30008, Tutorial 10, 2024

#pragma once

#include <stdexcept>

template<class T>
class Stack
{
private:
	T* fElements;
	size_t fStackPointer;
	size_t fStackSize;

public:
	Stack(size_t aSize)
	{
		fElements = new T[aSize];
		fStackSize = aSize;
		fStackPointer = 0;
	}

	~Stack()
	{
		delete[] fElements;
	}

	bool isEmpty() const
	{
		return fStackPointer == 0;
	}

	size_t size() const
	{
		return fStackPointer;
	}

	void push(const T& aItem)
	{
		if (fStackPointer < fStackSize)
		{
			fElements[fStackPointer++] = aItem;
		}
		else
		{
			throw std::overflow_error("Stack<>::push(): stack full");
		}
	}

	void push(T&& aItem)
	{
		if (fStackPointer < fStackSize)
		{
			fElements[fStackPointer++] = aItem;
		}
		else
		{
			throw std::overflow_error("Stack<>::push(): stack full");
		}
	}

	void pop()
	{
		if (!isEmpty())
		{
			fStackPointer--;
		}
		else
		{
			throw std::underflow_error("Stack<>::pop(): empty stack");
		}
	}

	const T& top() const
	{
		if (!isEmpty())
		{
			return fElements[fStackPointer - 1];
		}
		else
		{
			throw std::underflow_error("Stack<>::top(): empty stack");
		}
	}
};