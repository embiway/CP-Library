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
	
	T combine(T left, T right) { return max(left, right); }

	void build(const auto& a, const int sz)
	{
		for (int i = 0; i < sz; i++) tree[sz + i] = a[i];
		for (int i = sz - 1; i > 0; i--) tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
	}

	void update(int i, const T v, const int sz)
	{
		for (i += sz, tree[i] = v; i > 0; i >>= 1) tree[i >> 1] = combine(tree[i], tree[i ^ 1]);
	}

	int query(int l, int r, const int sz)
	{
		T resl = 0, resr = 0;
		for (l += sz, r += sz; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) resl = combine(resl, tree[l++]);
			if (r & 1) resr = combine(resr, tree[--r]);
		}
		return res;
	}
	
	void clear() { memset(tree, 0, sizeof(tree)); }
};
