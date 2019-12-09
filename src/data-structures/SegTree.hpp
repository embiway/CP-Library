/*
	Implementation of iterative Segment Tree which supports range-min
	query and point update. The Segment Tree is useful because it is
	very versatile, as it can do basically any math function as a
	query. N is the size of the array.

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
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int N, typename T>
struct SegTree
{
	T tree[2 * N];

	void build(const auto& a, const int sz)
	{
		for (int i = 0; i < sz; i++) tree[sz + i] = a[i];
		for (int i = sz - 1; i; i--) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
	}

	void update(int i, T v)
	{
		for (i += N, tree[i] = v; i > 1; i >>= 1) tree[i >> 1] = max(tree[i], tree[i ^ 1]);
	}

	int query(int l, int r)
	{
		T res = 0;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) res = max(res, tree[l++]);
			if (r & 1) res = max(res, tree[r--]);
		}
		return res;
	}
};
