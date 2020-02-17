/*
    Binary Indexed Tree for range sum queries and point increments [l, r]
    Time complexity: O(N log N) init, O(log N) query and update
     where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, typename T, const int INDEXING>
struct BITRangePoint {
	T bit[MAXN + 1]; int N;
	void init(int N = MAXN) { this->N = N; std::fill(bit, bit + N + 1, 0); }
	template <typename It> void init(It st, It en) {
		N = en - st; std::fill(bit, bit + N + 1, 0);
		for (int i = 1; i <= N; i++) update(i, i, *(st + i - 1));
	}
	void update(int l, int r, T x) { update_(l, x); update_(r + 1, -x); }
	T query(int i) { T sum = 0; for (i += 1 - INDEXING; i; i -= i & -i) sum += bit[i]; return sum; }
private:
	void update_(int i, T x) { for (i += 1 - INDEXING; i <= N; i += i & -i) bit[i] += x; }
};
