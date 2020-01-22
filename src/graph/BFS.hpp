/*
	Implementation of BFS (Breadth-First Search) with std::queue.
	min_path() performs the BFS algorithm, where the disconnected
	nodes have a value of numeric_limits<T>::max(). The get_path()
	function takes in an argument, the destination, and returns a
	vector of a shortest path from the source (given in min_path()
	argument), to the destination.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(V)

	- void add(const int u, const int v)
		Time:  O(1)
		Space: O(1)

	- void add_bi(const int u, const int v)
		Time:  O(1)
		Space: O(1)

	- vector<int> min_path(const int v, const int V = MAXV)
		Time:  O(V + E)
		Space: O(V + E)

	- vector<int> get_path(int v)
		Time:  O(V)
		Space: O(V)

	- void clear()
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXV>
struct BFS {
	vector<int> adj[MAXV + 1];
	queue<int> q;
	int dist[MAXV + 1], parent[MAXV + 1], _V;

	void add(const int u, const int v) {
		adj[u].push_back(v);
	}

	void add_bi(const int u, const int v) {
		add(u, v); add(v, u);
	}

	void min_path(const int v, const int V = MAXV) {
		_V = V;
		queue<int>().swap(q);
		fill(dist, dist + _V + 1, INT_MAX);
		memset(parent, -1, sizeof(parent));
		q.push(v);
		dist[v] = 0;
		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			for (int i : adj[curr]) {
				if (dist[i] == INT_MAX) {
					parent[i] = curr;
					dist[i] = dist[curr] + 1;
					q.push(i);
				}
			}
		}
	}

	vector<int> get_path(int v) {
		vector<int> res;
		for (; v != -1; v = parent[v]) res.push_back(v);
		reverse(res.begin(), res.end());
		return res;
	}

	void clear() {
		for (int i = 0; i <= _V; i++) adj[i].clear();
	}
};
