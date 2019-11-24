/*
    - CONSTRUCTION
        Time:  O(1)
        Space: O(N)
    - void init()
        Time:  O(1)
        Space: O(1)
    - void insert(Line<T>& a, Line<T>& b, Line<T>& c)
        Time:  O(1)
        Space: O(1)
    - pair<T, int> get(T x)
        Time:  O(1)
        Space: O(1)
*/

#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Line
{
    T m, b;
    int id;
    
    T get(T x) { return m * x + b; }
};

template <const int MAXN, typename T>
struct StaticCHT
{
    int ptr, sz;
    Line<T> v[MAXN];
    
    void init() { sz = ptr = 0; }
    
    bool bad(Line<T>& a, Line<T>& b, Line<T>& c) { return (a.b - c.b) * (b.m - a.m) <= (c.m - a.m) * (a.b - b.b); }
    
    void insert(Line<T> x)
    {
        while (ptr + 1 < sz && bad(v[sz - 2], v[sz - 1], x)) --sz;
        v[sz++] = x;
    }
    
    pair<T, int> get(T x)
    {
        ptr = min(ptr, sz);
        while (ptr + 1 < sz && v[ptr].get(x) <= v[ptr + 1].get(x)) ++ptr;
        return { v[ptr].get(x), v[ptr].id };
    }
};
