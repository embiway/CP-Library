/*
    Implementation of Binary Indexed Tree (Fenwick Tree), with a linear-time initialization.
    Calculates range sum query and point update in logarithmic time.
    Where N is the size of the array.
    
    - CONSTRUCTION
        Time:  O(1)
        Space: O(N)
        
    - void init()
        Time:  O(1)
        Space: O(1)
        
    - void init(const auto& a, const int N = MAXN)
        Time:  O(N)
        Space: O(1)
        
    - void update(int i, const T x, const int N = MAXN)
        Time:  O(log N)
        Space: O(1)
        
    - T query(int i)
        Time:  O(log N)
        Space: O(1)
        
    - T query(int l, int r)
        Time:  O(log N)
        Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct BIT
{
    T bit[MAXN + 1];
    
    void init() { memset(bit, 0, sizeof(bit)); }
    
    void init(const auto& a, const int N = MAXN)
    {
        memset(bit, 0, sizeof(bit));
        for (int i = 1; i <= N; i++)
        {
            bit[i] += a[i];
            int idx = i + (i & -i);
            if (idx <= N) bit[idx] += bit[i];
        }
    }
    
    void update(int i, const T x, const int N = MAXN)
    {
        for (; i <= N; i += i & -i) bit[i] += x;
    }
    
    T query(int i)
    {
        T res = 0;
        for (; i > 0; i -= i & -i) res += bit[i];
        return res;
    }
    
    T query(const int l, const int r)
    {
        return query(r) - query(l - 1);
    }
};
