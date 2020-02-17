/*
	Counting Sort non-comparative sorting algorithm
	Suitable for arrays with small ranges
	Time complexity: O(N + R)
	 where N is the size of the array, and R is the range of the elements
*/

#pragma once
#include <bits/stdc++.h>

template <typename It>
void counting_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	T maxv = *st, minv = *st;
	for (It i = st; i != en; i++) maxv = std::max(maxv, *i), minv = std::min(minv, *i);
	T range = maxv - minv + 1, *cnt = new T[range];
	for (int i = 0; i < range; i++) cnt[i] = 0;
	for (It i = st; i != en; i++) ++cnt[*i - minv];
	for (T i = minv; i <= maxv; i++) {
		while (cnt[i - minv]--) *st++ = i;
	}
	delete[] cnt;
}
