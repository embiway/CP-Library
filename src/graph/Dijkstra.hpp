/*
	Dijkstra's algorithm for shortest path on positive-weighted graphs
	Time complexity: O(E log V)
	 where V and E are the number of vertices and edges, respectively
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXV, typename T, const int INDEXING>
struct Dijkstra {
	std::vector<std::pair<int, T>> adj[MAXV + INDEXING]; std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> pq;
	const T INF = std::numeric_limits<T>::max(); T dist[MAXV + INDEXING]; int par[MAXV + INDEXING], V;
	void add(int u, int v, T w) { adj[u].emplace_back(v, w); }
	void add_bi(int u, int v, T w) { add(u, v, w); add(v, u, w); }
	void min_path(int v, int V = MAXV) {
		this->V = V; std::fill(dist, dist + V + INDEXING, INF); std::fill(par, par + V + INDEXING, -1);
		pq.emplace(0, v); dist[v] = 0;
		while (!pq.empty()) {
			int cv = pq.top().second, cw = pq.top().first; pq.pop();
			if (cw > dist[cv]) continue;
			for (auto &i : adj[cv]) {
				T d = i.second + dist[cv];
				if (dist[i.first] > d) dist[i.first] = d, par[i.first] = cv, pq.emplace(d, i.first);
			}
		}
	}
	std::vector<int> get_path(int v) {
		std::vector<int> res;
		for (; v != -1; v = par[v]) res.push_back(v);
		std::reverse(res.begin(), res.end()); return res;
	}
	void clear() { for (int i = 0; i < V + INDEXING; i++) adj[i].clear(); }
};
