
#pragma once

#include <stdexcept>

template <typename DataType>
struct SinglyLinkedList
{
    DataType fData;
    SinglyLinkedList* fNext;
    
    SinglyLinkedList( const DataType& aData, SinglyLinkedList* aNext = nullptr ) :
        fData(aData),
        fNext(aNext)
    {}

    SinglyLinkedList( DataType&& aData, SinglyLinkedList* aNext = nullptr ) :
        fData(std::move(aData)),
        fNext(aNext)
    {}

    const SinglyLinkedList* operator[](size_t aIndex) const
    {
        const SinglyLinkedList* lElement = this;

        for (size_t i = 0; i <= aIndex; i++)
        {
            if (lElement == nullptr)
                throw std::out_of_range("Illegal index!");

            if (i == aIndex)
                return lElement;

            lElement = lElement->fNext;
        }
    }

    void insert(SinglyLinkedList* aElement)
    {
        aElement->fNext = fNext;
        fNext = aElement;
    }

    const SinglyLinkedList* pop()
    {
        SinglyLinkedList* lNext = fNext;
        fNext = fNext->fNext;

        return lNext;
    }
};
