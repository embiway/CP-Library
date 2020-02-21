/*
	Topological Sort algorithm to achieve order such that for every vertex u -> v, v goes before u
	Time complexity: O(V + E)
	 where V and E are the number of vertices and edges, respectively
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXV, const int INDEXING>
struct TopologicalSort {
	std::vector<int> adj[MAXV + INDEXING]; std::vector<int> res; int deg[MAXV + INDEXING], V = 0;
	void add(int u, int v) { adj[u].push_back(v); ++V; }
	std::vector<int> toposort() {
		std::fill(deg, deg + V + INDEXING, 0); res.clear();
		for (int i = INDEXING; i < V + INDEXING; i++) for (auto &j : adj[i]) ++deg[j];
		for (int i = INDEXING; i < V + INDEXING; i++) if (!deg[i]) res.push_back(i);
		for (int i = 0; i < int(res.size()); i++) for (auto &j : adj[res[i]]) if (!--deg[j]) res.push_back(j);
		return int(res.size()) == V ? res : std::vector<int>();
	}
	void clear() { for (int i = 0; i < V + INDEXING; i++) adj[i].clear(); V = 0; }
};
