/*
	Disjoint Set Union for union/find operations in disjoint subsets
	Optimizations include union by size and path compression
	Time complexity: O(N) init, O(α(N)) join and find
	 where α(N) is the inverse Ackermann function, and N is the size of the disjoint set
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, const int INDEXING>
struct DSU {
	int par[MAXN + INDEXING], sz[MAXN + INDEXING];
	void init(int N = MAXN) { for (int i = 0; i < N + INDEXING; i++) par[i] = i, sz[i] = 1; }
	int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); }
	bool join(int u, int v) {
		if ((u = find(u)) == (v = find(v))) return false;
		if (sz[u] < sz[v]) std::swap(u, v);
		par[v] = u, sz[u] += sz[v];
		return true;
	}
	bool connected(int u, int v) { return find(u) == find(v); }
	int size(int v) { return sz[find(v)]; }
};
