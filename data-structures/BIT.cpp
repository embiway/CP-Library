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
        
    - void init(auto& a, int sz)
        Time:  O(N)
        Space: O(1)
        
    - void update(int i, T x)
        Time:  O(log N)
        Space: O(1)
        
    - T query(int i)
        Time:  O(log N)
        Space: O(1)
        
    - T query(int l, int r)
        Time:  O(log N)
        Space: O(1)
*/

#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct BIT
{
    T bit[MAXN];
    
    void init() { memset(bit, 0, sizeof(bit)); }
    
    void init(auto& a, int sz)
    {
        memset(bit, 0, sizeof(bit));
        for (int i = 1; i <= sz; i++)
        {
            bit[i] += a[i];
            int idx = i + (i & -i);
            if (idx <= sz) bit[idx] += bit[i];
        }
    }
    
    void update(int i, T x)
    {
        for (; i < MAXN; i += i & -i) bit[i] += x;
    }
    
    T query(int i)
    {
        T res = 0;
        for (; i > 0; i -= i & -i) res += bit[i];
        return res;
    }
    
    T query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};
