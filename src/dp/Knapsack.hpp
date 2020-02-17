/*
	Two implementations to solve the 0/1 Knapsack problem
	 - for small knapsack weights
	 - for small knapsack values
	Time complexity:
	 1st method: O(N * W) where N is the size of the array, and W is the knapsack weight
	 2nd method: O(N * V) where N is the size of the array, and V is the sum of the values
*/

#pragma once
#include <bits/stdc++.h>

template <typename T, typename ItW, typename ItV>
T small_w(int W, ItW st_w, ItW en_w, ItV st_v, ItV en_v) {
	int N = en_w - st_w; std::vector<T> dp(W + 1, 0);
	for (int i = 0; i < N; i++) for (int j = W; j >= *(st_w + i); j--) dp[j] = std::max(dp[j], dp[j - *(st_w + i)] + *(st_v + i));
	return dp[W];
}

template <typename T, typename ItW, typename ItV>
T small_v(int W, ItW st_w, ItW en_w, ItV st_v, ItV en_v) {
	int N = en_w - st_w, V = std::accumulate(st_v, en_v, 0); std::vector<T> dp(V + 1, W + 1);
	dp[0] = 0;
	for (int i = 0; i < N; i++) for (int j = V; j >= *(st_v + i); j--) dp[j] = std::min(dp[j], dp[j - *(st_v + i)] + *(st_w + i));
	for (int i = V; i >= 0; i--) if (dp[i] <= W) return i;
	return -1;
}
