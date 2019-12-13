/*
	A Longest Increasing Subsequence implementation using binary search.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)

	- void init(const auto& a, const int N = MAXN)
		Time:  O(N)
		Space: O(1)

	- int get_length(const int N = MAXN)
		Time:  O(N * log N)
		Space: O(N)

	- T* get_dp()
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct LIS
{
	T a[MAXN], dp[MAXN];

	void init(const auto& a, const int N = MAXN) { for (int i = 0; i < N; i++) this->a[i] = a[i]; }

	int get_length(const int N = MAXN)
	{
		int len = 0;
		for (int i = 0; i < N; i++)
		{
			int x = lower_bound(dp, dp + len, a[i]) - dp;
			dp[x] = a[i];
			if (x == len) ++len;
		}
		return len;
	}

	T* get_dp() { return dp; }
};
