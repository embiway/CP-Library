/*
	Implementation of Counting Sort sorting algorithm. The implementation
	shown here can also sort negative values. The algorithm relies on the
	fact that the integers to be sorted are small. The time complexity of
	counting_sort is linear to the range of the array.

	- void counting_sort(It st, It en) {
		Time:  O(N + range)
		Space: O(range)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename It>
void counting_sort(It st, It en) {
	typedef typename iterator_traits<It>::value_type T;
	T maxv = *st, minv = *st;
	for (It i = st; i != en; i++) maxv = max(maxv, *i), minv = min(minv, *i);
	T range = maxv - minv + 1, *cnt = new T[range];
	for (int i = 0; i < range; i++) cnt[i] = 0;
	for (It i = st; i != en; i++) ++cnt[*i - minv];
	for (T i = minv; i <= maxv; i++) {
		while (cnt[i - minv]--) *st++ = i;
	}
	delete[] cnt;
}
