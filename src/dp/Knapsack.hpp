/*
	Solver for the 0/1 Knapsack problem, where N is the size of the knapsack,
	W is the max weight, w is the array of weights, and v is the array of values.
	If W is small, use small_w(). If the sum of v[i] is small, use small_v().

	- T small_w(int N, int W, auto& w, auto& v)
		Time:  O(N * W)
		Space: O(W)

	- T small_v(int N, int W, auto& w, auto& v)
		Time:  O(N * sum(v))
		Space: O(sum(v))
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

namespace Knapsack {
	template <typename T>
	T small_w(const int N, const int W, const auto& w, const auto& v) {
		vector<T> dp(W + 1);
		for (int i = 0; i < N; i++) {
			for (int j = W; j >= w[i]; j--) {
				dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
			}
		}
		return dp[W];
	}

	template <typename T>
	T small_v(const int N, const int W, const auto& w, const auto& v) {
		int V = 0; for (int i = 0; i < N; i++) V += v[i];
		vector<T> dp(V + 1, W + 1);
		dp[0] = 0;
		for (int i = 0; i < N; i++) {
			for (int j = V; j >= v[i]; j--) {
				dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
			}
		}
		for (int i = V; i >= 0; i--) {
			if (dp[i] <= W) {
				return i;
			}
		}
	}
}
