/*
	Implementation of iterative Segment Tree which supports range
	query and point update. The Segment Tree is useful because it is
	very versatile, as it can perform many operations. Keep in mind
	that the queries are 0-indexed, and range is [l, r).

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)
	- void build(const auto& a, const int N)
		Time:  O(N)
		Space: O(1)
		
	- void build(const int N)
		Time:  O(N)
		Space: O(1)

	- void update(int i, const T v, const int N)
		Time:  O(log N)
		Space: O(1)

	- T query(int l, int r, const int N)
		Time:  O(log N)
		Space: O(1)

	- void clear()
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct SegTree
{
	T tree[2 * MAXN];
	const T DEFAULT = 0;

	T merge(T left, T right); // query type?

	void build(const auto& a, const int N)
	{
		for (int i = 0; i < N; i++) tree[N + i] = a[i];
		for (int i = N - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	void build(const int N)
	{
	    for (int i = 0; i < N; i++) tree[N + i] = DEFAULT;
		for (int i = N - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	void update(int i, const T v, const int N)
	{
		for (i += N, tree[i] = v; i >>= 1; ) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}

	T query(int l, int r, const int N)
	{
		T resl = DEFAULT, resr = DEFAULT;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) resl = merge(resl, tree[l++]);
			if (r & 1) resr = merge(resr, tree[--r]);
		}
		return merge(resl, resr);
	}

	void clear() { memset(tree, DEFAULT, sizeof(tree)); }
};
