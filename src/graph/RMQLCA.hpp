/*
	Lowest Common Ancestor by converting to Range Minimum Query (RMQ)
	Also calculates distance using the formula dist[u] + dist[v] - 2 * dist[lca(u, v)]
	Time complexity: O(V log V) process, O(1) query, dist
	 where V is the number of vertices
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXV, typename T, const int INDEXING>
struct RMQLCA {
	std::vector<std::pair<int, T>> adj[MAXV]; T dist[MAXV]; int tour[MAXV], sparse[32 - __builtin_clz(2 * MAXV)][2 * MAXV], lg[2 * MAXV], idx;
	void add(int u, int v, T w) { u -= INDEXING, v -= INDEXING; adj[u].emplace_back(v, w); adj[v].emplace_back(u, w); }
	void dfs(int cur, int prev, T d) {
		dist[cur] = d, sparse[0][tour[cur] = idx++] = cur;
		for (auto &i : adj[cur]) if (i.first != prev) { dfs(i.first, cur, d + i.second); sparse[0][idx++] = cur; }
	}
	void process(int root, int V = MAXV) {
		idx = 0; dfs(root - INDEXING, -1, 0); lg[1] = 0; for (int i = 2; i <= idx; i++) lg[i] = lg[i >> 1] + 1;
		for (int j = 0; j < lg[idx]; j++)
			for (int i = 0; i + (1 << j) < idx; i++)
				sparse[j + 1][i] = argmin(sparse[j][i], sparse[j][i + (1 << j)]);
	}
	int query(int u, int v) { u -= INDEXING, v -= INDEXING; if (tour[u] > tour[v]) std::swap(u, v); return query_(tour[u], tour[v]) + INDEXING; }
	T distance(int u, int v) { return dist[u - INDEXING] + dist[v - INDEXING] - 2 * dist[query(u, v) - INDEXING]; }
private:
    int argmin(int u, int v) { return dist[u] < dist[v] ? u : v; }
    T query_(int l, int r) { int k = lg[r - l + 1]; return argmin(sparse[k][l], sparse[k][r - (1 << k) + 1]); }
};
