/*
	Implementation of Counting Sort sorting algorithm.
	This algoirthm relies on the fact that the integers to
	be sorted are small. The function counting_sort() takes
	in an extra argument denoting the largest value in the
	array. It is also implemented such that only positive
	integers may be sorted, although it can be easily modified
	to take negatives as well.

	- void counting_sort(T arr[], int N, int maxv)
		Time:  O(maxv + N)
		Space: O(maxv)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T>
void counting_sort(T arr[], int N, int maxv) {
	int* cnt = new int[maxv + 1];
	for (T i = 0; i <= maxv; i++) cnt[i] = 0;
	for (int i = 0; i < N; i++) ++cnt[arr[i]];
	for (T i = 0, z = 0; i <= maxv; i++) {
		while (cnt[i]--) arr[z++] = i;
	}
	delete[] cnt;
}
