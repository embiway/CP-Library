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
		i += N;
		tree[i] = v;
		for (; i > 1; i >>= 1) tree[i >> 1] = max(tree[i], tree[i ^ 1]);
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
