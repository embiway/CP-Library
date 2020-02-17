/*
	2D Sparse Table for 2D range queries [t, b], [l, r]
	init() is called via 'init(arr, arr + rows)' or 'init(std::begin(arr), std::end(arr))'
	Time complexity: O(NM log N log M) init, O(1) query
	 where N and M are the size of the array's rows and columns, respectively
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, const int MAXM, typename T, const int INDEXING>
struct SparseTable2D {
	T sparse[32 - __builtin_clz(MAXN)][32 - __builtin_clz(MAXM)][MAXN][MAXM]; int lg[std::max(MAXN, MAXM) + 1], N, M;
	T query_op(T a, T b) { return std::min(a, b); } // range query operation
	template <typename It> void init(It st, It en) {
		N = en - st, M = std::end(*st) - std::begin(*st); for (int i = 0; i < N; i++) std::copy(std::begin(*(st + i)), std::end(*(st + i)), sparse[0][0][i]);
		lg[1] = 0; for (int i = 2; i <= std::max(N, M); i++) lg[i] = lg[i >> 1] + 1;
		for (int ir = 0; ir < N; ir++)
			for (int jc = 0; jc < lg[M]; jc++)
				for (int ic = 0; ic + (1 << jc) < M; ic++)
					sparse[0][jc + 1][ir][ic] = query_op(sparse[0][jc][ir][ic], sparse[0][jc][ir][ic + (1 << jc)]);
		for (int jr = 0; jr < lg[N]; jr++)
			for (int ir = 0; ir + (1 << jr) < N; ir++)
				for (int jc = 0; jc <= lg[M]; jc++)
					for (int ic = 0; ic < M; ic++)
						sparse[jr + 1][jc][ir][ic] = query_op(sparse[jr][jc][ir][ic], sparse[jr][jc][ir + (1 << jr)][ic]);
	}
	T query(int t, int b, int l, int r) {
		t -= INDEXING, b -= INDEXING, l -= INDEXING, r -= INDEXING; int kr = lg[b - t + 1], kc = lg[r - l + 1];
		return query_op(query_op(sparse[kr][kc][t][l], sparse[kr][kc][t][r - (1 << kc) + 1]), query_op(sparse[kr][kc][b - (1 << kr) + 1][l], sparse[kr][kc][b - (1 << kr) + 1][r - (1 << kc) + 1]));
	}
};
