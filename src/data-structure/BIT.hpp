/*
	Binary Indexed Tree for range sum queries and point increments [l, r]
	Time complexity: O(N) init, O(log N) query and update
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, typename T, const int INDEXING>
struct BIT {
	T bit[MAXN + 1]; int N, lg;
	void init(int N = MAXN) { this->N = N; std::fill(bit, bit + N + 1, 0); lg = 31 - __builtin_clz(N + 1); }
	template <typename It> void init(It st, It en) {
		N = en - st; std::fill(bit, bit + N + 1, 0); lg = 31 - __builtin_clz(N + 1);
		for (int i = 1; i <= N; i++) {
			bit[i] += *(st + i - 1);
			int idx = i + (i & -i); if (idx <= N) bit[idx] += bit[i];
		}
	}
	void update(int i, T x) { for (i += 1 - INDEXING; i <= N; i += i & -i) bit[i] += x; }
	T query(int i) { T res = 0; for (i += 1 - INDEXING; i; i -= i & -i) res += bit[i]; return res; }
	T query(int l, int r) { return query(r) - query(l - 1); }
	int lower_bound(T x) {
	    int res = 0; T sum = 0;
	    for (int i = lg; i >= 0; i--) {
	        int nxt = res | (1 << i);
	        if (nxt <= N && sum + bit[nxt] < x) res = nxt, sum += bit[nxt];
	    }
	    return res + INDEXING;
	}
	int upper_bound(T x) {
	    int res = 0; T sum = 0;
	    for (int i = lg; i >= 0; i--) {
	        int nxt = res | (1 << i);
	        if (nxt <= N && sum + bit[nxt] < x) res = nxt, sum += bit[nxt];
	    }
	    return res + INDEXING;
	}
};
