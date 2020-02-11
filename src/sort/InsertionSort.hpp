/*
	Implementation of Insertion Sort sorting algorithm.
	Insertion Sort is faster than Bubble Sort, and usually
	faster than Selection Sort as well.

	- void insertion_sort(It st, It en, Compare comp)
		Time:  O(N ^ 2)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename It, typename Compare>
void insertion_sort(It st, It en, Compare comp) {
	for (It i = st; i != en - 1; i++) {
		for (It j = i + 1; j != st && comp(*j, *(j - 1)); j--) {
			swap(*j, *(j - 1));
		}
	}
}

template <typename It>
void insertion_sort(It st, It en) {
	typedef typename iterator_traits<It>::value_type T;
	insertion_sort(st, en, less<T>());
}
