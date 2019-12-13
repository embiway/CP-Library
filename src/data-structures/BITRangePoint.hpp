/*
    Implementation of Binary Indexed Tree (Fenwick Tree).
    Calculates point query and range update in logarithmic time.
    Where N is the size of the array.

    - CONSTRUCTION
        Time:  O(1)
        Space: O(N)

    - void init()
        Time:  O(1)
        Space: O(1)

    - void init(const auto& a, const int N)
    	Time:  O(N * log N)
    	Space: O(1)

    - void update(const int l, const int r, const T x, const int N = MAXN)
        Time:  O(log N)
        Space: O(1)

    - T query(int i)
        Time:  O(log N)
        Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct BITRangePoint
{
	T bit[MAXN + 1];

	void init() { memset(bit, 0, sizeof(bit)); }

	void init(const auto& a, const int N)
	{
		for (int i = 1; i <= N; i++) update(i, i, a[i]);
	}

	void update(const int l, const int r, const T x, const int N = MAXN)
	{
		_update(l, x, N);
		_update(r + 1, -x, N);
	}

	T query(int i)
	{
		T sum = 0;
		for (; i > 0; i -= i & -i) sum += bit[i];
		return sum;
	}

private:
	void _update(int i, const T x, const int N = MAXN)
	{
		for (; i <= N; i += i & -i) bit[i] += x;
	}
};
