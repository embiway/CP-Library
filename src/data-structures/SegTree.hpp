/*
	Implementation of iterative Segment Tree which supports range-max
	query and point update. The Segment Tree is useful because it is
	very versatile, as it can do basically any math function as a
	query. Keep in mind that the queries are 0-indexed, and range is [l, r).
	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)
	- void build(const auto& a, const int sz)
		Time:  O(N)
		Space: O(1)

	- void build(const int sz)
		Time:  O(N)
		Space: O(1)
	- void update(int i, T v)
		Time:  O(log N)
		Space: O(1)
	- int query(int l, int r)
		Time:  O(log N)
		Space: O(1)

	- void clear()
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int N, typename T>
struct SegTree
{
	T tree[2 * N];
	const T DEFAULT = 0;

	T merge(T left, T right) { return left + right; }

	void build(const auto& a, const int sz)
	{
		for (int i = 0; i < sz; i++) tree[sz + i] = a[i];
		for (int i = sz - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	void build(const int sz)
	{
	    for (int i = 0; i < sz; i++) tree[sz + i] = DEFAULT;
		for (int i = sz - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	void update(int i, const T v, const int sz)
	{
		for (i += sz, tree[i] = v; i >>= 1; ) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	T query(int l, int r, const int sz)
	{
		T resl = DEFAULT, resr = DEFAULT;
		for (l += sz, r += sz; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) resl = merge(resl, tree[l++]);
			if (r & 1) resr = merge(resr, tree[--r]);
		}
		return merge(resl, resr);
	}
};
