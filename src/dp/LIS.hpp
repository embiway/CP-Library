/*
	A Longest Increasing Subsequence implementation using binary search.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)

	- void init(T arr[])
		Time:  O(N)
		Space: O(1)

	- int get_length()
		Time:  O(N * log N)
		Space: O(N)

	- T* get_dp()
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int N, typename T>
struct LIS
{
	T arr[N], dp[N];

	void init(T arr[]) { for (int i = 0; i < N; i++) this->arr[i] = arr[i]; }

	int get_length()
	{
		int len = 0;
		for (int i = 0; i < N; i++)
		{
			int x = lower_bound(dp, dp + len, arr[i]) - dp;
			dp[x] = arr[i];
			if (x == len) ++len;
		}
		return len;
	}

	T* get_dp() { return dp; }
};
