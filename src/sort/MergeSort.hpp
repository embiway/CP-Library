/*
	Implementation of Merge Sort sorting algorithm. This is an
	efficient algorithm which has a worst case complexity of O(n * log n).
	Therefore, it technically can be faster than quicksort, but due to
	its large constant factor, and quicksort's average complexity,
	it is usually slower :(

	- void merge_sort(It st, It en, Compare comp)
		Time:  O(N * log N)
		Space: O(N)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename It, typename Compare>
void merge_sort(It st, It en, Compare comp) {
	int range = en - st;
	if (range > 1) {
		It mid = st + range / 2, s = st, m = mid;
		merge_sort(st, mid, comp);
		merge_sort(mid, en, comp);
		typedef typename iterator_traits<It>::value_type T;
		T *temp = new T[en - st + 1]; int idx = 0;
		while (s != mid && m != en) temp[idx++] = comp(*s, *m) ? *s++ : *m++;
		while (s != mid) temp[idx++] = *s++;
		while (m != en) temp[idx++] = *m++;
		for (int i = 0; i < range; i++) *(st + i) = temp[i];
		delete[] temp;
	}
}

template <typename It>
void merge_sort(It st, It en) {
	typedef typename iterator_traits<It>::value_type T;
	merge_sort(st, en, less<T>());
}
