/*
	Implementation of Binary Indexed Tree (Fenwick Tree).
	Calculates range query and range update using two trees.
	Where N is the size of the array.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)

	- void init()
		Time:  O(1)
		Space: O(1)

	- void init(const auto& a, const int N = MAXN)
		Time:  O(N * log N)
		Space: O(1)

	- void update(const int l, const int r, const T x, const int N = MAXN)
		Time:  O(log N)
		Space: O(1)

	- T query(const int i)
		Time:  O(log N)
		Space: O(1)

	- T query(const int l, const int r)
		Time:  O(log N)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct BITRange
{
	T bit1[MAXN + 1], bit2[MAXN + 1];

	void init() { memset(bit1, 0, sizeof(bit1)); memset(bit2, 0, sizeof(bit2)); }

	void init(const auto& a, const int N = MAXN)
	{
		memset(bit1, 0, sizeof(bit1)); memset(bit2, 0, sizeof(bit2));
		for (int i = 1; i <= N; i++) update(i, i, a[i]);
	}

	void update(const int l, const int r, const T x, const int N = MAXN)
	{
		_update(bit1, l, x, N);
		_update(bit1, r + 1, -x, N);
		_update(bit2, l, x * (l - 1), N);
		_update(bit2, r + 1, -x * r, N);
	}


	T query(const int i)
	{
		return i * _query(bit1, i) - _query(bit2, i);
	}

	T query(const int l, const int r)
	{
		return query(r) - query(l - 1);
	}

private:
	void _update(T bit[], int i, const T x, const int N = MAXN)
	{
		for (; i <= N; i += i & -i) bit[i] += x;
	}

	T _query(T bit[], int i)
	{
		T sum = 0;
		for (; i > 0; i -= i & -i) sum += bit[i];
		return sum;
	}
};
