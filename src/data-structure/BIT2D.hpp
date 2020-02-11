/*
    Implementation of 2D Binary Indexed Tree.
    Calculates 2D range sum query with a similar method to 'BIT.hpp', except it's 2D.
    Where N is the size of the array.

    - CONSTRUCTION
        Time:  O(1)
        Space: O(N * M)

    - void init(const int N = MAXN, const int M = MAXM)
        Time:  O(1)
        Space: O(1)

    - void init(const auto& a, const int N = MAXN, const int M = MAXM)
        Time:  O(N * M * log N * log M)
        Space: O(1)

    - void update(int i, int j, const T x)
        Time:  O(log N * log M)
        Space: O(1)

    - T query(int i, int j)
        Time:  O(log N * log M)
        Space: O(1)

    - T query(int l, int b, int r, int t)
        Time:  O(log N * log M)
        Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, const int MAXM, typename T>
struct BIT2D {
    T bit2d[MAXN + 1][MAXM + 1];
    int _N, _M;

    void init(const int N = MAXN, const int M = MAXM) {
    	_N = N, _M = M;
    	memset(bit2d, 0, sizeof(bit2d));
    }

    void init(const auto& a, const int N = MAXN, const int M = MAXM) {
    	_N = N, _M = M;
    	for (int i = 1; i <= _N; i++) for (int j = 1; j <= _M; j++) update(i, j, a[i][j]);
    }

    void update(int i, int j, const T x) {
        for (int ii = i; ii <= _N; ii += ii & -ii) for (int jj = j; jj <= _M; jj += jj & -jj) bit2d[ii][jj] += x;
    }

    T query(int i, int j) {
        T res = 0;
        for (int ii = i; ii > 0; ii -= ii & -ii) for (int jj = j; jj > 0; jj -= jj & -jj) res += bit2d[ii][jj];
        return res;
    }

    T query(const int l, const int b, const int r, const int t) {
        return query(r, t) - query(r, b - 1) - query(l - 1, t) + query(l - 1, b - 1);
    }
};
