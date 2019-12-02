/*
	Implementation of Bubble Sort sorting algorithm. This
	is one of the slowest sorting algorithms, so it is not
	advised to be used. For reference, an array of size 10^6
	takes ~ 20 sec. to run.

	- void bubble_sort(T arr[], int N)
		Time:  O(N ^ 2)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T>
void bubble_sort(T arr[], int N)
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (arr[i] > arr[j]) swap(arr[i], arr[j]);
		}
	}
}
