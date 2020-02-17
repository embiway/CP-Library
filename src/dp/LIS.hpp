/*
	Longest (strictly) Increasing Subsequence using dynamic programming + binary search
	Time complexity: O(N log N) where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

#define T typename std::iterator_traits<It>::value_type
template <typename It>
std::vector<T> LIS(It st, It en) {
	int N = en - st, len = 0, lo, hi, mid; T *dp = new T[N], *nxt = new T[N];
	for (int i = 0; i < N; i++) {
		lo = 0, hi = len;
		while (lo < hi) {
		    mid = (lo + hi) / 2;
		    if (*(st + dp[mid]) < *(st + i)) lo = mid + 1;
		    else hi = mid;
		}
		if (len == hi) ++len;
		dp[hi] = i, nxt[i] = hi ? dp[hi - 1] : -1;
	}
	std::vector<T> lis(len); for (int i = dp[len - 1]; i != -1; i = nxt[i]) lis[--len] = *(st + i);
	return lis;
}
