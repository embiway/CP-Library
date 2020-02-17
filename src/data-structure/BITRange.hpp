/*
	Binary Indexed Tree for range sum queries and increments [l, r]
	Time complexity: O(N log N) init, O(log N) query and update
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, typename T, const int INDEXING>
struct BITRange {
	T bit1[MAXN + 1], bit2[MAXN + 1]; int N;
	void init(int N = MAXN) { this->N = N; std::fill(bit1, bit1 + N + 1, 0); std::fill(bit2, bit2 + N + 1, 0); }
	template <typename It> void init(It st, It en) {
		N = en - st; std::fill(bit1, bit1 + N + 1, 0); std::fill(bit2, bit2 + N + 1, 0);
		for (int i = 1; i <= N; i++) update(i, i, *(st + i - 1));
	}
	void update(int l, int r, T x) {
		update_(bit1, l, x); update_(bit1, r + 1, -x);
		update_(bit2, l, x * (l - 1)); update_(bit2, r + 1, -x * r);
	}
	T query(int i) { return i * query_(bit1, i) - query_(bit2, i); }
	T query(int l, int r) { return query(r) - query(l - 1); }
private:
	void update_(T *bit, int i, T x) { for (i += 1 - INDEXING; i <= N; i += i & -i) bit[i] += x; }
	T query_(T *bit, int i) { T sum = 0; for (i += 1 - INDEXING; i; i -= i & -i) sum += bit[i]; return sum; }
};
