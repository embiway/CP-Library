/*
    Sparse Table implementation on Range Minimum Query (can be modified
    for other query types).
    Also stores table of 'log2' for faster queries.
    
    - CONSTRUCTION
        Time:  O(1)
        Space: O(N * log N)
    
    - void init(auto& arr)
        Time:  O(N * log N)
        Space: O(1)
        
    - T query(int l, int r)
        Time:  O(1)
        Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int N, typename T>
struct SparseTable
{
    static const int LG = 32 - __builtin_clz(N);
    int lg[N + 1];
    T st[N][LG];
    
    void init(const auto& arr)
    {
        for (int i = 0; i < N; i++) st[i][0] = arr[i];
        lg[1] = 0;
        for (int i = 2; i <= N; i++) lg[i] = lg[i >> 1] + 1;
        
        for (int j = 1; j <= LG; j++)
        {
            for (int i = 0; i + (1 << j) <= N; i++)
            {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    
    T query(const int l, const int r)
    {
        int k = lg[r - l + 1];
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
};
