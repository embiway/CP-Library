/*
	Prim's algorithm to solve Minimum Spanning Tree in undirected graphs (0-indexed)
	Time complexity: O(E log V)
	 where V and E are the number of vertices and edges, respectively
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXV, typename T, const int INDEXING>
struct Prim {
	struct Edge { int u, v; T w; };
	std::vector<std::pair<int, T>> adj[MAXV + INDEXING]; std::vector<Edge> mst; std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> pq;
	const T INF = std::numeric_limits<T>::max(); T cost[MAXV + INDEXING]; bool vis[MAXV + INDEXING]; std::pair<int, T> par[MAXV + INDEXING]; int V;
	void add(int u, int v, T w) { adj[u].emplace_back(v, w); adj[v].emplace_back(u, w); }
	T min_path(int V = MAXV) {
		this->V = V; pq = {}; std::fill(cost, cost + V + INDEXING, INF); std::fill(vis, vis + V + INDEXING, false); std::fill(par, par + V + INDEXING, std::make_pair(-1, 0));
		pq.emplace(0, INDEXING); cost[INDEXING] = 0; T ans = 0;
		while (!pq.empty()) {
			int cv = pq.top().second; T cw = pq.top().first; pq.pop();
			if (vis[cv]) continue;
			vis[cv] = true, ans += cw;
			for (auto &i : adj[cv]) {
				if (!vis[i.first] && cost[i.first] > i.second) cost[i.first] = i.second, par[i.first] = {cv, i.second}, pq.emplace(i.second, i.first);
			}
		}
		for (int i = 0; i < V + INDEXING; i++) if (par[i].first != -1) mst.push_back({i, par[i].first, par[i].second});
		return ans;
	}
	std::vector<Edge> get_path() { return mst; }
	void clear() { mst.clear(); for (int i = 0; i < V + INDEXING; i++) adj[i].clear(); }
};
