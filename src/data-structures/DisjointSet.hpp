#pragma once
#include <bits/stdc++.h>

using namespace std;

/*
    Supports Disjoint Set find() and union(), and also some other functions.
    With path compression, time complexity is O(α(N)).

    - CONSTRUCTION
        Time:  O(1)
        Space: O(N)

    - void init(const int N = MAXN)
        Time:  O(N)
        Space: O(1)

    - int find(const int v)
        Time:  O(α(N))
        Space: O(α(N))

    - bool join(int v, int w)
        Time:  O(α(N))
        Space: O(α(N))

    - bool connected(const int v, const int w)
        Time:  O(α(N))
        Space: O(α(N))

    - bool size(const int v)
        Time:  O(1)
        Space: O(1)
*/

template <const int MAXN>
struct DisjointSet {
    int parent[MAXN + 1], sz[MAXN + 1];

    void init(const int N = MAXN) {
        for (int i = 1; i <= N; i++) parent[i] = i, sz[i] = 1;
    }

    int find(const int v) {
    	return v == parent[v] ? v : parent[v] = find(parent[v]);
    }

    bool join(int v, int w) {
        if ((v = find(v)) == (w = find(w))) return false;
        if (sz[v] < sz[w]) swap(v, w);
        parent[w] = v;
        sz[v] += sz[w];
        return true;
    }

    bool connected(const int v, const int w) {
    	return find(v) == find(w);
    }

    int size(const int v) {
    	return sz[find(v)];
    }
};
