/*
    Convex Hull Trick with sorted insertions and queries.
    Originally to solve APIO 2014 P2.
    
    - CONSTRUCTION
        Time:  O(1)
        Space: O(N)
        
    - void init()
        Time:  O(1)
        Space: O(1)
        
    - void insert(const Line x)
        Time:  O(1)
        Space: O(1)
        
    - pair<T, int> get(const T x)
        Time:  O(1)
        Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T>
struct StaticCHT
{
	struct Line
	{
	    T m, b;
	    int id;

	    T get(const T x) { return m * x + b; }
	};

    int ptr, sz;
    Line v[MAXN];
    
    void init() { sz = ptr = 0; }
    
    bool bad(const Line& a, const Line& b, const Line& c) { return (a.b - c.b) * (b.m - a.m) <= (c.m - a.m) * (a.b - b.b); }
    
    void insert(const Line x)
    {
    	while (ptr + 1 < sz && bad(v[sz - 2], v[sz - 1], x)) --sz;
    	v[sz++] = x;
    }
    
    pair<T, int> get(const T x)
    {
    	ptr = min(ptr, sz);
        while (ptr + 1 < sz && v[ptr].get(x) <= v[ptr + 1].get(x)) ++ptr;
        return { v[ptr].get(x), v[ptr].id };
    }
};
