
// COS30008, Tutorial 7, 2022

#include "ofstream12.h"
#include "ifstream12.h"

#include <iostream>
#include <string>
//#include <bit>

using namespace std;

static void write4096()
{
	/*if constexpr (endian::native == endian::little)
		cout << "little-endian";
	else if constexpr (endian::native == endian::big)
		cout << "big-endian";
	else
		cout << "mixed-endian";
	cout << endl;*/

	cout << "Write 4096 codes" << endl;

	ofstream12 lWriter( "sample.lzw" );

	if ( !lWriter.good() )
	{
		cerr << "Error: Unable to open output file!" << endl;
		exit( 1 );
	}

	//cout << lWriter.isOpen() << endl;

	for ( size_t i = 4096; i > 0; )
	{
		lWriter << --i;
	}
}

static void read4096()
{
	cout << "Read 4096 codes" << endl;

	ifstream12 lReader("sample.lzw");

	if (!lReader.good())
	{
		cerr << "Error: Unable to open input file!" << endl;
		exit(1);
	}

	size_t lValue;

	while (lReader >> lValue)
	{
		cout << lValue << " ";
	}

	cout << endl << "End of file" << endl;
}

int main()
{
	write4096();

	cout << "WRITING SUCCEEDED" << endl;

	read4096();

	cout << "READING SUCCEEDED" << endl;

	return 0;
}
