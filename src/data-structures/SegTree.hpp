/*
	Implementation of iterative Segment Tree which supports range
	query and point update. The Segment Tree is useful because it is
	very versatile, as it can perform many operations. Keep in mind
	that the queries are 0-indexed, and range is [l, r).

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)
	- void init(const auto& a, const int N = MAXN)
		Time:  O(N)
		Space: O(1)
		
	- void init(const int N = MAXN)
		Time:  O(N)
		Space: O(1)

	- void update(int i, const T v)
		Time:  O(log N)
		Space: O(1)

	- T query(int l, int r)
		Time:  O(log N)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct SegTree
{
	T tree[2 * MAXN];
	const T DEFN; // default node value?
	int _N;

	T merge(T& left, T& right); // query type?

	void init(const auto& a, const int N = MAXN) {
		_N = N;
		for (int i = 0; i < _N; i++) tree[_N + i] = a[i];
		for (int i = _N - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	void init(const int N = MAXN) {
		_N = N;
	    for (int i = 0; i < _N; i++) tree[_N + i] = DEFN;
		for (int i = _N - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	void update(int i, const T v) {
		for (i += _N, tree[i] = v; i >>= 1; ) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	T query(int l, int r) {
		T resl = DEFN, resr = DEFN;
		for (l += _N, r += _N; l < r; l >>= 1, r >>= 1) {
			if (l & 1) resl = merge(resl, tree[l++]);
			if (r & 1) resr = merge(tree[--r], resr);
		}
		return merge(resl, resr);
	}
};
