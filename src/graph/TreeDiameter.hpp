/*
	Calculate diameter of a weighted tree
	Time complexity: O(V)
	 where V is the number of vertices
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXV, typename T, const int INDEXING>
struct TreeDiameter {
	std::vector<std::pair<int, T>> adj[MAXV + INDEXING]; int par[MAXV + INDEXING], start;
	void add(int u, int v, T w) { adj[u].emplace_back(v, w); adj[v].emplace_back(u, w); }
	std::pair<T, int> dfs(int cur, int prev) {
		std::pair<T, int> res = {0, cur}; par[cur] = prev;
		for (auto &i : adj[cur]) {
			if (i.first != prev) { std::pair<T, int> cost = dfs(i.first, cur); cost.first += i.second, res = std::max(res, cost); }
		}
		return res;
	}
	T get_diameter() { std::pair<int, T> p = dfs(INDEXING, -1), q = dfs(p.second, -1); start = q.second; return q.first; }
	std::vector<int> get_path() {
		std::vector<int> res;
		for (int v = start; v != -1; v = par[v]) res.push_back(v);
		return res;
	}
	void clear() { for (int i = 0; i < MAXV + INDEXING; i++) adj[i].clear(); }
};
