/*
	Implementation of Bubble Sort sorting algorithm. This
	is one of the slowest sorting algorithms, so it is not
	advised to be used, ever.

	- void bubble_sort(It st, It en, Compare comp) {
		Time:  O(N ^ 2)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename It, typename Compare>
void bubble_sort(It st, It en, Compare comp) {
	for (It i = st; i != en - 1; i++) {
		for (It j = i + 1; j != en; j++) {
			if (comp(*j, *i)) swap(*i, *j);
		}
	}
}

template <typename It>
void bubble_sort(It st, It en) {
	typedef typename iterator_traits<It>::value_type T;
	bubble_sort(st, en, less<T>());
}
