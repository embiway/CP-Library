/*
	Square Root Decomposition for range queries and point updates [l, r]
	Typename TV denotes the array type, TQ denotes the query type
	update_assoc is specifically for associative updates
	Time complexity: O(N) init, O(N / B + B) query, O(1) update_assoc, O(B) update
	 where B is the block size, and N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, const int BLKSZ, typename TV, typename TQ, const int INDEXING>
struct SqrtDecomp {
	TQ blk[MAXN / BLKSZ], val[MAXN]; int N; const TQ DEFV, DEFQ; // default value of array and queries
	TQ query_op(TQ a, TQ b); // range query operation
	TQ update_op(TQ a, TV b); // range update operation
	void init(int N = MAXN) {
		this->N = N; std::fill(blk, blk + N / BLKSZ, DEFQ);
		for (int i = 0; i < N; i++) { int idx = i / BLKSZ; blk[idx] = query_op(blk[idx], val[i] = DEFV); }
	}
	template <typename It> void init(It st, It en) {
		N = en - st; std::fill(blk, blk + N / BLKSZ, DEFQ);
		for (int i = 0; i < N; i++) { int idx = i / BLKSZ; blk[idx] = query_op(blk[idx], val[i] = *(st + i)); }
	}
	void update_assoc(int i, TV v) { val[i -= INDEXING] = update_op(val[i], v); int idx = i / BLKSZ; blk[idx] = update_op(blk[idx], v); }
	void update(int i, TV v) {
		val[i -= INDEXING] = update_op(val[i], v); int idx = i / BLKSZ; blk[idx] = DEFQ;
		for (int j = idx * BLKSZ; j < std::min(N, (idx + 1) * BLKSZ); j++) blk[idx] = query_op(blk[idx], val[j]);
	}
	TQ query(int l, int r) {
		TQ res = DEFQ;
		int lidx = (l -= INDEXING) / BLKSZ, ridx = (r -= INDEXING) / BLKSZ;
		if (lidx == ridx) for (int i = l; i <= r; i++) res = query_op(res, val[i]);
		else {
			for (int i = l; i < (lidx + 1) * BLKSZ; i++) res = query_op(res, val[i]);
			for (int i = lidx + 1; i < ridx; i++) res = query_op(res, blk[i]);
			for (int i = ridx * BLKSZ; i <= r; i++) res = query_op(res, val[i]);
		}
		return res;
	}
};
