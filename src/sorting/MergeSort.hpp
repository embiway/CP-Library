/*
	Implementation of Merge Sort sorting algorithm. This is an
	efficient algorithm which has a worst case complexity of O(n * log n).
	It can sort an array of size 5 * 10^7 in ~ 20 sec. Note that using a
	temporary array (int* temp = new int[]) makes the program significantly
	faster than if a static array was used.

	- void merge_sort(T arr[], int N)
		Time:  O(N * log N)
		Space: O(N)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T>
void merge(T arr[], int start, int mid, int end)
{
	T *temp = new T[end - start + 1];
	int idx = 0;

	for (int i = start, p = start, q = mid + 1; i <= end; i++)
	{
		if (p > mid) 	  		  temp[idx++] = arr[q++];
		else if (q > end) 		  temp[idx++] = arr[p++];
		else if (arr[p] < arr[q]) temp[idx++] = arr[p++];
		else					  temp[idx++] = arr[q++];
	}

	for (int i = 0; i < idx; i++) arr[start++] = temp[i];
	delete[] temp;
}

template <typename T>
void merge_sort(T arr[], int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		merge_sort(arr, start, mid);
		merge_sort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

template <typename T>
void merge_sort(T arr[], int N) { merge_sort(arr, 0, N - 1); }
