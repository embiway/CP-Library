/*
	Implementation of Square Root Decomposition, with range query
	and point update. Sqrt Decomp is advantageous in that it is quite
	versatile, althought time complexity is not as good.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)

	- void init(const auto& a, const int N = MAXN, const int BLKSZ = MAXBLKSZ)
		Time:  O(1)
		Space: O(N)

	- void init(const int N = MAXN, const int BLKSZ = MAXBLKSZ)
		Time:  O(1)
		Space: O(N)

	- void update(const int i, const T v, const int N = MAXN, const int BLKSZ = MAXBLKSZ)
		Time:  O(1)
		Space: O(1)

	- T query(const int l, const int r, const int N = MAXN, const int BLKSZ = MAXBLKSZ)
		Time:  O(sqrt(N))
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, const int MAXBLKSZ, typename T>
struct SqrtDecomp
{
	T blocks[MAXN / MAXBLKSZ + 1], arr[MAXN];
	const T DEFAULT; // default value?

	T merge(T left, T right); // query type?

	void init(const auto& a, const int N = MAXN, const int BLKSZ = MAXBLKSZ)
	{
		fill(blocks, blocks + N / BLKSZ + 1, DEFAULT);
		for (int i = 0; i < N; i++)
		{
			int idx = i / BLKSZ;
			blocks[idx] = merge(blocks[idx], arr[i] = a[i]);
		}
	}

	void init(const int N = MAXN, const int BLKSZ = MAXBLKSZ)
	{
		fill(blocks, blocks + N / BLKSZ + 1, DEFAULT);
		for (int i = 0; i < N; i++)
		{
			int idx = i / BLKSZ;
			blocks[idx] = merge(blocks[idx], arr[i] = DEFAULT);
		}
	}

	void update(const int i, const T v, const int N = MAXN, const int BLKSZ = MAXBLKSZ)
	{
		int idx = i / BLKSZ;
		blocks[idx] = merge(blocks[idx], v);
	}

	T query(const int l, const int r, const int N = MAXN, const int BLKSZ = MAXBLKSZ)
	{
		T res = DEFAULT;
		int lidx = l / BLKSZ, ridx = r / BLKSZ;

		if (lidx == ridx) for (int i = l; i <= r; i++) res = merge(res, arr[i]);
		else
		{
			for (int i = l; i < (lidx + 1) * BLKSZ; i++) res = merge(res, arr[i]);
			for (int i = lidx + 1; i < ridx; i++) res = merge(res, blocks[i]);
			for (int i = ridx * BLKSZ; i <= r; i++) res = merge(res, arr[i]);
		}
		return res;
	}
};
