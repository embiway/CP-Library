/*
	Implementation of Insertion Sort sorting algorithm.
	Insertion Sort is faster than Bubble Sort, and has a
	similar time complexity to Selection Sort. For an array
	of size 2 * 10^6, it takes ~ 20 sec.

	- void insertion_sort(T arr[], int N)
		Time:  O(N ^ 2)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T>
void insertion_sort(T arr[], int N)
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j && arr[j] < arr[j - 1]; j--) swap(arr[j], arr[j - 1]);
	}
}
