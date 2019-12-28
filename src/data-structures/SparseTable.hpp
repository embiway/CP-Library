/*
    Sparse Table implementation on Range Query (for any associative and
    idempotent query type). Also stores table of 'log2' for faster
    queries. Keep in mind, the range is zero-indexed and cover [l, r].
    
    - CONSTRUCTION
        Time:  O(1)
        Space: O(N * log N)
    
    - void init(const auto& a, const int N = MAXN)
        Time:  O(N * log N)
        Space: O(1)
        
    - T query(int l, int r)
        Time:  O(1)
        Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct SparseTable
{
    static const int MAXLG = 32 - __builtin_clz(MAXN);
    int lg[MAXN + 1];
    T st[MAXLG][MAXN];
    
    T merge(T left, T right); // query type?

    void init(const auto& a, const int N = MAXN)
    {
    	const int LG = 32 - __builtin_clz(N);
        for (int i = 0; i < N; i++) st[0][i] = a[i];

        lg[1] = 0;
        for (int i = 2; i <= N; i++) lg[i] = lg[i >> 1] + 1;
        
        for (int j = 0; j < LG; j++)
        {
            for (int i = 0; i + (1 << j) < N; i++)
            {
                st[j + 1][i] = merge(st[j][i], st[j][i + (1 << j)]);
            }
        }
    }
    
    T query(const int l, const int r)
    {
        int k = lg[r - l + 1];
        return merge(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
