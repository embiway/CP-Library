/*
	Implementation of Radix Sort sorting algorithm. radix_sort is also able
	to take negative numbers by temporarily converting them to positive
	The algorithm converts the array to base 256, to improve the constant
	factor. Overall, it is faster than std::sort Concerning the time
	complexity, W is the number of bits in the integer type.

	- void radix_sort(It st, It en)
		Time:  O(N * W)
		Space: O(N + W)

*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename It>
void radix_sort_unsigned(It st, It en) {
	typedef typename iterator_traits<It>::value_type T;
	int bits = sizeof(T) << 3, range = en - st, *cnt = new int[256];
	T *bucket = new T[range];
	for (int p = 0; p < bits; p += 8) {
	    memset(cnt, 0, 1024);
		for (It i = st; i != en; i++) ++cnt[(*i >> p) & 255];
		for (int i = 1; i < 256; i++) cnt[i] += cnt[i - 1];
		for (It i = en - 1; i != st - 1; i--) bucket[--cnt[(*i >> p) & 255]] = *i;
		copy(bucket, bucket + range, st);
	}
	delete[] cnt;
	delete[] bucket;
}

template <typename It>
void radix_sort(It st, It en) {
	typedef typename iterator_traits<It>::value_type T;
	for (It i = st; i != en; i++) *i ^= numeric_limits<T>::min();
	radix_sort_unsigned(st, en);
	for (It i = st; i != en; i++) *i ^= numeric_limits<T>::min();
}
