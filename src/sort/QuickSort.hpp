/*
	Implementation of Quick Sort sorting algorithm. The implementation
	shown here is at its simplest. The worst case complexity is N ^ 2,
	however the average will be N * log N. Surprisingly, it is nearly as
	fast as std::sort, despite being so primitive (could be due to overhead maybe...)

	- void quick_sort(It st, It en, Compare comp)
		Time Complexity:  O(N * log N)
		Space Complexity: O(log N)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename It, typename Compare>
void quick_sort(It st, It en, Compare comp) {
	int range = en - st;
	if (range > 1) {
		typedef typename iterator_traits<It>::value_type T;
		T pivot = *(st + range / 2); It i, j;
		for (i = st, j = en - 1; ; i++, j--) {
			while (comp(*i, pivot)) i++;
			while (comp(pivot, *j)) j--;
			if (i >= j) break;
			swap(*i, *j);
		}
		quick_sort(st, i, comp);
		quick_sort(i, en, comp);
	}
}

template <typename It>
void quick_sort(It st, It en) {
	typedef typename iterator_traits<It>::value_type T;
	quick_sort(st, en, less<T>());
}
