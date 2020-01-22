/*
	Implementation of Bellman Ford's algorithm  for shortest path
	with negative weights. Can detect negative cycle through the
	function is_neg_cycle(). Similar to the BFS implementation,
	min_path() returns the dist[] array, where the disconnected
	nodes have a value of numeric_limits<T>::max().

	- CONSTRUCTION
		Time:  O(1)
		Space: O(V)

	- void add(const int u, const int v, const T w)
		Time:  O(1)
		Space: O(1)

	- void add_bi(const int u, const int v, const T w)
		Time:  O(1)
		Space: O(1)

	- T* min_path(const int v, const int V = MAXV)
		Time:  O(V * E)
		Space: O(V + E)

	- vector<int> get_path(int v)
		Time:  O(V)
		Space: O(V)

	- bool is_neg_cycle()
		Time:  O(1)
		Space: O(1)

	- void clear()
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXV, typename T>
struct BellmanFord {
	struct Edge {
		int u, v; T w;
		Edge(int u, int v, T w) : u(u), v(v), w(w) {}
		bool operator < (const Edge& e) const { return w < e.w; }
	};

	const T INF = numeric_limits<T>::max();
	vector<Edge> graph;
	T dist[MAXV + 1];
	int parent[MAXV + 1];
	bool neg_cycle;

	void add(const int u, const int v, const T w) {
		graph.emplace_back(u, v, w);
	}

	void add_bi(const int u, const int v, const T w) {
		add(u, v, w); add(v, u, w);
	}

	T* min_path(const int v, const int V = MAXV) {
		fill(dist, dist + V + 1, INF);
		memset(parent, -1, sizeof(parent));
		neg_cycle = false;
		dist[v] = 0;
		for (int i = 0; i <= V; i++) {
			for (const auto& g : graph) {
				T d = dist[g.u] + g.w;
				if (dist[g.u] != INF && d < dist[g.v]) {
					dist[g.v] = d;
					parent[g.v] = g.u;
				}
			}
		}
		for (const auto& i : graph) {
			if (dist[i.u] != INF && dist[i.u] + i.w < dist[i.v]) {
				neg_cycle = true;
			}
		}
		return dist;
	}

	vector<int> get_path(int v) {
		vector<int> res;
		for (; v != -1; v = parent[v]) res.push_back(v);
		reverse(res.begin(), res.end());
		return res;
	}

	bool is_neg_cycle() {
		return neg_cycle;
	}

	void clear() {
		graph.clear();
	}
};
