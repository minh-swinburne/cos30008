
// COS30008, Tutorial 10, 2024

#pragma once

#include "List.h"

#include <stdexcept>

using namespace std;

template<class T>
class Queue
{
private:
	List<T> fElements;

public:
	bool isEmpty() const
	{
		return fElements.empty();
	}

	size_t size() const
	{
		return fElements.size();
	}

	void enqueue(const T& aItem)
	{
		fElements.push_back(aItem);
	}

	void enqueue(T&& aItem)
	{
		fElements.push_back(aItem);
	}

	void dequeue()
	{
		if (isEmpty())
		{
			throw std::underflow_error("Queue<>::dequeue(): empty queue");
		}

		fElements.remove(fElements[0]);
	}

	const T& top() const
	{
		if (isEmpty())
		{
			throw std::underflow_error("Queue<>::front(): empty queue");
		}

		return fElements[0];
	}
};