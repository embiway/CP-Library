/*
	Iterative Segment Tree for range queries and point updates [l, r]
	Typename TV denotes the array type, TQ denotes the query type
	Time complexity: O(N) init, O(log N) query and update
	 where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename TV, typename TQ, const int INDEXING>
struct SegTree {
	TQ tree[MAXN << 1]; int N; const TQ DEFV, DEFQ; // default value of array and queries
	TQ query_op(TQ a, TQ b); // range query operation
	TQ update_op(TQ a, TV b); // point update operation
	void init(int N = MAXN) {
		this->N = N; for (int i = 0; i < N; i++) tree[N + i] = DEFV;
		for (int i = N - 1; i; i--) tree[i] = query_op(tree[i << 1], tree[i << 1 | 1]);
	}
	template <typename It> void init(It st, It en) {
		N = en - st; for (int i = 0; i < N; i++) tree[N + i] = *(st + i);
		for (int i = N - 1; i; i--) tree[i] = query_op(tree[i << 1], tree[i << 1 | 1]);
	}
	void update(int i, TV v) { for (i += N - INDEXING, tree[i] = update_op(tree[i], v); i >>= 1; ) tree[i] = query_op(tree[i << 1], tree[i << 1 | 1]); }
	TQ query(int l, int r) {
		TQ resl = DEFQ, resr = DEFQ;
		for (l += N - INDEXING, r += N - INDEXING; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) resl = query_op(resl, tree[l++]);
			if (!(r & 1)) resr = query_op(tree[r--], resr);
		}
		return query_op(resl, resr);
	}
};
