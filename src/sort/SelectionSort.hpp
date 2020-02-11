/*
	Implementation of Selection Sort sorting algorithm.
	Although it has the same time complexity as Bubble Sort,
	it is faster, with ~ 16 sec for an array of size 2 * 10^6,
	due more efficient operations.

	- void selection_sort(It st, It en, Compare comp)
		Time:  O(N ^ 2)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename It, typename Compare>
void selection_sort(It st, It en, Compare comp) {
	for (It i = st; i < en - 1; i++) {
		It mini = i;
		for (It j = i + 1; j != en; j++) {
			if (comp(*j, *mini)) mini = j;
		}
		swap(*i, *mini);
	}
}

template <typename It>
void selection_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	selection_sort(st, en, less<T>());
}
