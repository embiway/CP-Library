/*
	2D Binary Indexed Tree for 2D range sum queries [t, b], [l, r] and point increments
	init() is called via 'init(arr, arr + rows)' or 'init(std::begin(arr), std::end(arr))'
	Time complexity: O(NM log N log M) init, O(log N log M) query and update
	 where N and M are the size of the array's rows and columns, respectively
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, const int MAXM, typename T, const int INDEXING>
struct BIT2D {
	T bit[MAXN + 1][MAXM + 1]; int N, M;
	void init(int N = MAXN, int M = MAXM) { this->N = N, this->M = M; std::fill(*bit, *bit + (N + 1) * (M + 1), 0); }
	template <typename It> void init(It st, It en) {
		N = en - st, M = std::end(*st) - std::begin(*st); std::fill(*bit, *bit + (N + 1) * (M + 1), 0);
		for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) update(i, j, (*(st + i - 1))[j - 1]);
	}
	void update(int i, int j, T x) { for (int ii = i - INDEXING + 1; ii <= N; ii += ii & -ii) for (int jj = j - INDEXING + 1; jj <= M; jj += jj & -jj) bit[ii][jj] += x; }
	T query(int i, int j) { T res = 0; for (int ii = i - INDEXING + 1; ii; ii -= ii & -ii) for (int jj = j - INDEXING + 1; jj; jj -= jj & -jj) res += bit[ii][jj]; return res; }
	T query(int t, int b, int l, int r) { return query(b, r) - query(t - 1, r) - query(b, l - 1) + query(t - 1, l - 1); }
};
