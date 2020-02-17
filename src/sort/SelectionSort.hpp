/*
	Selection Sort comparative sorting algorithm
	Usually slower than Insertion Sort and faster than Bubble Sort
	Time complexity: O(N^2)
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <typename It, typename Compare>
void selection_sort(It st, It en, Compare comp) {
	for (It i = st; i < en - 1; i++) {
		It mini = i;
		for (It j = i + 1; j != en; j++) {
			if (comp(*j, *mini)) mini = j;
		}
		std::swap(*i, *mini);
	}
}

template <typename It>
void selection_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	selection_sort(st, en, std::less<T>());
}
