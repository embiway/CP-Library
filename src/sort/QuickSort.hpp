/*
	Quick Sort comparative sorting algorithm
	Chooses fixed pivot at the middle (vulnerable of becoming O(N^2))
	Time complexity: O(N log N) average case, O(N^2) worst case
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <typename It, typename Compare>
void quick_sort(It st, It en, Compare comp) {
	typedef typename std::iterator_traits<It>::value_type T;
	int N = en - st;
	if (N > 1) {
		T pivot = *(st + N / 2); It i, j;
		for (i = st, j = en - 1; ; i++, j--) {
			while (comp(*i, pivot)) i++;
			while (comp(pivot, *j)) j--;
			if (i >= j) break;
			std::swap(*i, *j);
		}
		quick_sort(st, i, comp);
		quick_sort(i, en, comp);
	}
}

template <typename It>
void quick_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	quick_sort(st, en, std::less<T>());
}
