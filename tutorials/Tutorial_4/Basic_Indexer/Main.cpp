
// COS30008, 2022

#include "ArrayIndexer.h"

#include <iostream>

using namespace std;

int main()
{
    int lArray[] = { 1, 2, 3, 4, 5 };
    IntArrayIndexer lIndexer( lArray, sizeof( lArray ) / sizeof( int ) );
    
    string lKeys[] = { "0", "1", "2", "3", "4" };
    int lSum = 0;
    
    for ( size_t i = 0; i < lIndexer.size(); i++ )
    {
        lSum += lIndexer[lKeys[i]];
    }
    
    cout << "Indexed sum of [1,2,3,4,5] is " << lSum << endl;
    
    return 0;
}