#pragma once
#include <bits/stdc++.h>

template <typename It, typename Compare>
void heap_sort(It st, It en, Compare comp) {
	int N = en - st;
	auto heapify = [&] (int i) {
		while (true) {
			int j = i << 1 | 1;
			if (j >= N) break;
			if (j + 1 < N && *(st + j) < *(st + j + 1)) ++j;
			if (*(st + i) >= *(st + j)) break;
			std::swap(*(st + i), *(st + j)); i = j;
		}
	};
	for (int i = N / 2 - 1; i >= 0; i--) heapify(i);
	while (N > 1) std::swap(*st, *(st + --N)), heapify(0);
}

template <typename It>
void heap_sort(It st, It en) {
	typedef typename std::iterator_traits<It>::value_type T;
	heap_sort(st, en, std::less<T>());
}
