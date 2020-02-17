/*
	Insertion Sort comparative sorting algorithm.
	Often preferred over Selection and Bubble Sort
	Time complexity: O(N^2)
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <typename It, typename Compare>
void insertion_sort(It st, It en, Compare comp) {
	for (It i = st; i != en - 1; i++) {
		for (It j = i + 1; j != st && comp(*j, *(j - 1)); j--) {
			std::swap(*j, *(j - 1));
		}
	}
}

template <typename It>
void insertion_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	insertion_sort(st, en, std::less<T>());
}
