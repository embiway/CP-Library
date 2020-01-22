/*
	Implementation of Selection Sort sorting algorithm.
	Although it has the same time complexity as Bubble Sort,
	it is faster, with ~ 16 sec for an array of size 2 * 10^6,
	due to the more efficient operation.

	- void selection_sort(T arr[], int N)
		Time:  O(N ^ 2)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T>
void selection_sort(T arr[], int N) {
	for (int i = 0; i < N - 1; i++) {
		int mini = i;
		for (int j = i + 1; j < N; j++) {
			if (arr[j] < arr[mini]) {
				mini = j;
			}
		}
		swap(arr[i], arr[mini]);
	}
}
