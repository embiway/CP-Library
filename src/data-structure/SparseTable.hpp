/*
	Sparse Table for range queries [l, r]
	Time complexity: O(N log N) init, O(1) query
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, typename T, const int INDEXING>
struct SparseTable {
	T sparse[32 - __builtin_clz(MAXN)][MAXN]; int lg[MAXN + 1], N;
	T query_op(T a, T b); // range query operation
	template <typename It> void init(It st, It en) {
		N = en - st; std::copy(st, en, sparse[0]);
		lg[1] = 0; for (int i = 2; i <= N; i++) lg[i] = lg[i >> 1] + 1;
		for (int j = 0; j < lg[N]; j++)
			for (int i = 0; i + (1 << j) < N; i++)
				sparse[j + 1][i] = query_op(sparse[j][i], sparse[j][i + (1 << j)]);
	}
	T query(int l, int r) { l -= INDEXING, r -= INDEXING; int k = lg[r - l + 1]; return query_op(sparse[k][l], sparse[k][r - (1 << k) + 1]); }
};
