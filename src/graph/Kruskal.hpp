/*
	Kruskal's algorithm to solve Minimum Spanning Tree in undirected graphs
	Time complexity: O(E log E)
	 where E is the number of edges
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXV, typename T, const int INDEXING>
struct Kruskal {
	struct Edge { int u, v; T w; bool operator < (Edge &e) { return w < e.w; } };
	std::vector<Edge> adj, mst; int par[MAXV + INDEXING], sz[MAXV + INDEXING];
	void add(int u, int v, T w) { adj.push_back({u, v, w}); }
	T min_path(int V = MAXV) {
		std::sort(adj.begin(), adj.end()); for (int i = 0; i < V + INDEXING; i++) par[i] = i, sz[i] = 1;
		T ans = 0; int sz = 0;
		for (auto &i : adj) {
			if (sz > V) break;
			if (join(i.u, i.v)) mst.push_back(i), ans += i.w, ++sz;
		}
		return ans;
	}
	std::vector<Edge> get_path() { return mst; }
	void clear() { adj.clear(); mst.clear(); }
private:
	int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); }
	bool join(int u, int v) {
		if ((u = find(u)) == (v = find(v))) return false;
		if (sz[u] < sz[v]) std::swap(u, v);
		par[v] = u, sz[u] += sz[v];
		return true;
	}
};
