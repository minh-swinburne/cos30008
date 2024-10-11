// C++ program to sort an array without comparison
// operator.
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int* sortArr(int arr[], int n, int min, int max)
{
	// Count of elements in given range 
	int m = max - min + 1;
	int* result = new int[n];
	int index = 0;

	// Count frequencies of all elements
	vector<int> c(m, 0);
	for (int i = 0; i < n; i++)
		c[arr[i] - min]++;

	// Traverse through range. For every
	// element, print it its count times.
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < c[i]; j++)
		{
			if (index < n) // Ensure index is within bounds
			{
				result[index] = i + min;
				index++;
			}
			else { break; }
		}
	}
	return result;
}

// Driver Code
int main()
{
	int arr[] = { 10, 10, 1, 4, 4, 100, 0 };
	cout << "Initial array: ";
	for (size_t i : arr)
		cout << i << " ";
	cout << endl;

	int min = 0, max = 100;
	int n = sizeof(arr) / sizeof(arr[0]);
	int* sortedArr = sortArr(arr, n, min, max);

	cout << "Sorted array: ";
	for (size_t i = 0; i < n; i++)
		cout << sortedArr[i] << " ";
	cout << endl;

	delete[] sortedArr;
	return 0;
}
