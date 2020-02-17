/*
	Bellman-Ford algorithm for shortest path on weighted graphs with negative weights
	neg_cycle is true when there is a negative cycle
	Time complexity: O(VE)
	 where V and E are the number of vertices and edges, respectively
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXV, typename T, const int INDEXING>
struct BellmanFord {
	struct Edge { int u, v; T w; };
	const T INF = std::numeric_limits<T>::max(); std::vector<Edge> adj; T dist[MAXV + INDEXING]; int par[MAXV + INDEXING]; bool neg_cycle;
	void add(int u, int v, T w) { adj.push_back({u, v, w}); }
	void add_bi(int u, int v, T w) { add(u, v, w); add(v, u, w); }
	void min_path(int v, int V = MAXV) {
		std::fill(dist, dist + V + INDEXING, INF); std::fill(par, par + V + INDEXING, -1); dist[v] = 0; neg_cycle = false;
		for (int i = 0; i < V + INDEXING; i++) {
			for (auto& g : adj) {
				T d = dist[g.u] + g.w;
				if (dist[g.u] != INF && d < dist[g.v]) dist[g.v] = d, par[g.v] = g.u;
			}
		}
		for (auto& i : adj) if (dist[i.u] != INF && dist[i.u] + i.w < dist[i.v]) neg_cycle = true;
	}
	std::vector<int> get_path(int v) {
		std::vector<int> res;
		for (; v != -1; v = par[v]) res.push_back(v);
		std::reverse(res.begin(), res.end()); return res;
	}
	void clear() { adj.clear(); }
};
