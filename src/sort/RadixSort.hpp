/*
	Radix Sort non-comparative sorting algorithm (base 256)
	Preferred over std::sort for integer sorting (over 5x faster)
	Time complexity: O(NW)
	 where N is the size of the array, and W is the size of the array in bits
*/

#pragma once
#include <bits/stdc++.h>

template <typename It>
void radix_sort_unsigned(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	int bits = sizeof(T) << 3, range = en - st, *cnt = new int[256];
	T *bucket = new T[range];
	for (int p = 0; p < bits; p += 8) {
	    memset(cnt, 0, 1024);
		for (It i = st; i != en; i++) ++cnt[(*i >> p) & 255];
		for (int i = 1; i < 256; i++) cnt[i] += cnt[i - 1];
		for (It i = en - 1; i != st - 1; i--) bucket[--cnt[(*i >> p) & 255]] = *i;
		std::copy(bucket, bucket + range, st);
	}
	delete[] cnt;
	delete[] bucket;
}

template <typename It>
void radix_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	for (It i = st; i != en; i++) *i ^= std::numeric_limits<T>::min();
	radix_sort_unsigned(st, en);
	for (It i = st; i != en; i++) *i ^= std::numeric_limits<T>::min();
}
