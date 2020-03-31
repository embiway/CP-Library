/*
	Lowest Common Ancestor using Tarjan's offline algorithm
	ans[] stores pair containing the LCA and distances, respectively, between two nodes
	Time complexity: O(V*α(V) + Q) process
	 where V is the number of vertices, α(V) is the inverse Ackermann function, and Q is the number of queries
*/

#pragma once
#include <bits/stdc++.h>
template <const int MAXV, const int MAXQ, typename T, const int INDEXING>
struct TarjanLCA {
	std::vector<std::pair<int, T>> adj[MAXV]; std::vector<std::pair<int, int>> query[MAXV];
	std::pair<int, T> ans[MAXQ]; T dist[MAXV]; bool vis[MAXV]; int anc[MAXV], par[MAXV], sz[MAXV], idx = 0;
	void add(int u, int v, T w) { u -= INDEXING, v -= INDEXING; adj[u].emplace_back(v, w); adj[v].emplace_back(u, w); }
	void add_query(int u, int v) { u -= INDEXING, v -= INDEXING; query[u].emplace_back(v, idx); query[v].emplace_back(u, idx++); }
	void dfs(int cur, int prev, T d) {
		dist[cur] = d, anc[cur] = cur, vis[cur] = true;
		for (auto &i : adj[cur]) if (i.first != prev) { dfs(i.first, cur, d + i.second); join(cur, i.first); anc[find(cur)] = cur; }
		for (auto &i : query[cur]) if (vis[i.first]) { int a = anc[find(i.first)]; ans[i.second] = {a, dist[cur] + dist[i.first] - 2 * dist[a]}; }
	}
	void process(int root, int V = MAXV) { std::fill(vis, vis + V, false); for (int i = 0; i < V; i++) par[i] = i, sz[i] = 1; dfs(root -= INDEXING, -1, 0); }
private:
	int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); }
	bool join(int u, int v) {
		if ((u = find(u)) == (v = find(v))) return false;
		if (sz[u] < sz[v]) std::swap(u, v);
		par[v] = u, sz[u] += sz[v];
		return true;
	}
};
