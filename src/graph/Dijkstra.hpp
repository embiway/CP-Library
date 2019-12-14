/*
	Implementation of Dijkstra's algorithm with std::priority_queue and
	a custom node. Similar to the BFS implementation, min_path() performs
	the BFS algorithm, where the disconnected nodes have a value of
	numeric_limits<T>::max(). The get_path() function takes in an argument,
	the destination, and returns a vector of a shortest path from the
	source (given in min_path() argument), to the destination. Keep in mind,
	Dijkstra's algorithm only works for non-negative weights.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)

	- void add(int u, int v, T w)
		Time:  O(1)
		Space: O(1)

	- void add_bi(int u, int v, T w)
		Time:  O(1)
		Space: O(1)

	- void min_path(int v, int V = MAXV)
		Time:  O((V + E) * log V)
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

template <const int MAXV, typename T>
struct Dijkstra
{
	struct Node
	{
		int v; T w;

		Node(int v, T w) : v(v), w(w) {}

		bool operator < (const Node& n) const { return n.w < w; }
	};

	const T INF = numeric_limits<T>::max();
	vector<Node> adj[MAXV + 1];
	priority_queue<Node> pq;
	T dist[MAXV + 1];
	int parent[MAXV + 1];

	void add(int u, int v, T w) { adj[u].emplace_back(v, w); }

	void add_bi(int u, int v, T w) { add(u, v, w); add(v, u, w); }

	void min_path(int v, int V = MAXV)
	{
		priority_queue<Node>().swap(pq);
		fill(dist, dist + V + 1, INF);
		memset(parent, -1, sizeof(parent));

		pq.emplace(v, 0);
		dist[v] = 0;

		while (!pq.empty())
		{
			int cv = pq.top().v, cw = pq.top().w;
			pq.pop();

			if (cw > dist[cv]) continue;

			for (const auto& i : adj[cv])
			{
				T d = i.w + dist[cv];
				if (dist[i.v] > d)
				{
					parent[i.v] = cv;
					dist[i.v] = d;
					pq.emplace(i.v, dist[i.v]);
				}
			}
		}
	}

	vector<int> get_path(int v)
	{
		vector<int> res;
		for (; v != -1; v = parent[v]) res.push_back(v);
		reverse(res.begin(), res.end());
		return res;
	}

	void clear() { for (int i = 0; i <= MAXV; i++) adj[i].clear(); }
};
