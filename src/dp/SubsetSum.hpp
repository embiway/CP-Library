/*
	Three implementations to solve the Subset Sum problem
	 - get_sums() vector of all subset sums of a given array
	 - equal_sums() bitset of all integers which are a subset sum of a given array
	 - count_sums() number of integers which are a subset sum of a given array
	Time complexity:
	 1st method: O(N * 2 ^ {N / 2}) where N is the size of the array
	 2nd method: O(N * MAXSUM / 64) where N is the size of the array, and MAXSUM is the max sum to be calculated
	 3rd method: O(N * 2 ^ {N / 2}) where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <typename T, typename It, const bool SORTED = false>
std::vector<T> get_sums(It st, It en) {
	int N = en - st; std::vector<T> res(1 << N);
	for (int i = 0, curr = 1; i < N; i++) {
		for (int j = 0; j < curr; j++) res[j + curr] = res[j];
		for (int j = curr; j < curr << 1; j++) res[j] += *(st + i);
		if (SORTED) std::inplace_merge(res.begin(), res.begin() + curr, res.begin() + (curr <<= 1));
	}
	return res;
}

template <typename T, const int MAXSUM, typename It>
std::bitset<MAXSUM + 1> equal_sums(It st, It en) {
	std::bitset<MAXSUM + 1> bit; bit[0] = 1;
	for (It i = st; i != en; i++) bit |= bit << *i;
	return bit;
}

template <typename T, typename It>
uint64_t count_sums(It st, It en, T sum) {
	int N = en - st; std::unordered_map<T, uint64_t> left, right; left[0] = 1, right[0] = 1;
	for (int i = 0; i < N >> 1; i++) { auto L = left; for (auto &l : L) left[l.first + *(st + i)] += l.second; }
	for (int i = N >> 1; i < N; i++) { auto R = right; for (auto &r : R) right[r.first + *(st + i)] += r.second; }
	uint64_t res = 0;
	for (auto &l : left) if (right.count(sum - l.first)) res += l.second * right[sum - l.first];
	return res;
}
