
// COS30008, Tutorial 5, 2022

#ifdef _MSC_VER
// VS 2019 does not implement exception specification
#pragma warning( disable : 4290 )   
#endif

#include <iostream>
#include <stdexcept>

#define P1
#define P2
#define P3
#define P4
#define P5

#include "DataWrapper.h"

using namespace std;

int main( int argc, char* argv[] )
{
    if ( argc != 2 )
    {
        cerr << "Arguments missing." << endl;
        cerr << "Usage: DataWrapper <filename>" << endl;
        
        return 1;
    }
        
#ifdef P1

    DataWrapper lData;
    
    if ( !lData.load( argv[1] ) )
    {
        cerr << "Cannot load data file " << argv[1] << endl;
        
        return 2;
    }
    
    cout << "Data loaded." << endl;
    //cout << "Size: " << lData.size() << endl;
    //cout << "First data: " << lData[0].fIndex << " (index) - " << lData[0].fDatum << " (datum)" << endl;

#endif
    
#ifdef P2

    cout << "Checking error handling..." << endl;

    try
    {
        lData[lData.size()];
    }
    catch (out_of_range e) {
        cout << "Worked nicely. Message: " << e.what() << endl;
    }
    
    cout << "Using basic indexer: " << endl;
    
    for ( size_t i = 0; i < lData.size(); i++ )
    {
        cout << lData[i].getAsChar();
    }

    cout << endl;

#endif

#ifdef P3
    
    cout << "Using lambda with identity mapping logic: " << endl;

    auto lIdentityMapper = [&lData] (size_t aIndex) throw(out_of_range) -> const char
    {
		// Implementation
        if (aIndex >= lData.size())
            throw out_of_range("Index out of range: Maximum " + to_string(lData.size() - 1) + ", got " + to_string(aIndex));

        return lData[aIndex].getAsChar();
    };
    
    for ( size_t i = 0; i < lData.size(); i++ )
    {
        cout << lData.get( i, lIdentityMapper );
    }

    cout << endl;

#endif

#ifdef P4
    
    cout << "Using lambda with ordered mapping logic: " << endl;

    auto lOrderedMapper = [&lData] (size_t aIndex) throw(out_of_range) -> const char
    {
		// Implementation
        if (aIndex >= lData.size())
            throw out_of_range("Index out of range: Maximum " + to_string(lData.size() - 1) + ", got " + to_string(aIndex));

        for (size_t j = 0; j < lData.size(); j++)
        {
            if (lData[j].fIndex == aIndex)
            {
                return lData[j].getAsChar();
            }
        }
    };
    
    for ( size_t i = 0; i < lData.size(); i++ )
    {
        cout << lData.get( i, lOrderedMapper );
    }

    cout << endl;

#endif

#ifdef P5

    cout << "Using sorted data wrapper: " << endl;

    DataWrapper lSorted = lData.sorted();

    auto lSortedMapper = [&lSorted](size_t aIndex) throw(out_of_range) -> const char
        {
            // Implementation
            if (aIndex >= lSorted.size())
                throw out_of_range("Index out of range: Maximum " + to_string(lSorted.size() - 1) + ", got " + to_string(aIndex));

            return lSorted[aIndex].getAsChar();
        };

    for (size_t i = 0; i < lSorted.size(); i++)
    {
        cout << lSorted.get(i, lSortedMapper);
    }

    cout << endl;

#endif
    
    return 0;
}
