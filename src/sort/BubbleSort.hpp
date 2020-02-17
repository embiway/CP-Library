/*
	Bubble Sort comparative sorting algorithm
	One of the slowest sorting algorithms, hence it is impractical
	Time complexity: O(N^2)
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <typename It, typename Compare>
void bubble_sort(It st, It en, Compare comp) {
	for (It i = st; i != en - 1; i++) {
		for (It j = i + 1; j != en; j++) {
			if (comp(*j, *i)) std::swap(*i, *j);
		}
	}
}

template <typename It>
void bubble_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	bubble_sort(st, en, std::less<T>());
}
