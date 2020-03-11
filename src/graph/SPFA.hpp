/*
	Shortest-Path-Faster-Algorithm for shortest path on positive-weighted graphs
	Time complexity: O(E) average case, O(VE) worst case
	 where V and E are the number of vertices and edges, respectively
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXV, typename T, const int INDEXING>
struct SPFA {
	std::vector<std::pair<int, T>> adj[MAXV + INDEXING]; std::deque<int> dq;
	const T INF = std::numeric_limits<T>::max(); bool inq[MAXV + INDEXING]; T dist[MAXV + INDEXING]; int par[MAXV + INDEXING], V;
	void add(int u, int v, T w) { adj[u].emplace_back(v, w); }
	void add_bi(int u, int v, T w) { add(u, v, w); add(v, u, w); }
	void min_path(int v, int V = MAXV) {
		this->V = V; std::fill(dist, dist + V + INDEXING, INF); std::fill(par, par + V + INDEXING, -1); std::fill(inq, inq + V + INDEXING, false);
		dq.push_back(v); dist[v] = 0, inq[v] = true;
		while (!dq.empty()) {
			int cv = dq.front(); dq.pop_front(); inq[cv] = false;
			for (auto &i : adj[cv]) {
				T d = i.second + dist[cv];
				if (dist[i.first] > d) {
					dist[i.first] = d, par[i.first] = cv;
					if (!inq[i.first]) {
						inq[i.first] = true;
						if (dist[i.first] < dist[dq.front()]) dq.push_front(i.first);
						else dq.push_back(i.first);
					}
				}
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
