/*
	Shell Sort comparative sorting algorithm
	Uses Hibbard gap sequence which has a good complexity
	Time complexity: O(N^(4/3))
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <typename It, typename Compare>
void shell_sort(It st, It en, Compare comp) {
	int range = en - st, h = 1;
	while (h < range * 4 / 9) h = h * 9 / 4 + 1;
	for (; h > 0; h = h * 4 / 9) {
		for (It i = st + h, j; i != en; i++) {
			for (j = i; j - st >= h && comp(*j, *(j - h)); j -= h) {
				std::swap(*j, *(j - h));
			}
		}
	}
}

template <typename It>
void shell_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	shell_sort(st, en, std::less<T>());
}
