/*
	Implementation of Shell Sort sorting algorithm. The gap sequence
	used is essentially the hibbard gap sequence, which is one of the
	fastest based on experiments.

	- void shell_sort(It st, It en, Compare comp)
		Time Complexity:  O(N ^ (4 / 3))
		Space Complexity: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename It, typename Compare>
void shell_sort(It st, It en, Compare comp) {
	int range = en - st, h = 1;
	while (h < range * 4 / 9) h = h * 9 / 4 + 1;
	for (; h > 0; h = h * 4 / 9) {
		for (It i = st + h, j; i != en; i++) {
			for (j = i; j - st >= h && comp(*j, *(j - h)); j -= h) {
				swap(*j, *(j - h));
			}
		}
	}
}

template <typename It>
void shell_sort(It st, It en) {
	typedef typename iterator_traits<It>::value_type T;
	shell_sort(st, en, less<T>());
}
