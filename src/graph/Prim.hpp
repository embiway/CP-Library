/*
	Implementation of Prim's Algorithm to solve Minimum Spanning Tree.
	Prim's algorithm, like Kruskal's algorithm also greedily solves by
	picking the minimum weightw hich connects to tree. The implementation
	here uses a binary heap, although a fibonacci heap would allow for
	a lower time complexity.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(1)

	- void add(const int u, const int v, const T w)
		Time:  O(1)
		Space: O(1)

	- T min_path(const int V = MAXV)
		Time:  O(E * log V)
		Space: O(V + E)

	- vector<Edge<T>> get_path()
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
struct Prim
{
	struct Edge
	{
		int u, v; T w;

		Edge(int u, int v, T w) : u(u), v(v), w(w) {}

		bool operator < (const Edge& e) const { return w < e.w; }
	};

	struct Node
	{
		int v; T w;

		Node(int v, T w) : v(v), w(w) {}

		bool operator < (const Node& n) const { return n.w < w; }
	};

	vector<Node> adj[MAXV + 1];
	vector<Edge> mst;
	priority_queue<Node> pq;
	T cost[MAXV + 1];
	bool visited[MAXV + 1];
	pair<int, T> parent[MAXV + 1];

	void add(const int u, const int v, const T w) { adj[u].emplace_back(v, w); adj[v].emplace_back(u, w); }

	T min_path(const int V = MAXV)
	{
		priority_queue<Node>().swap(pq);
		fill(cost, cost + V + 1, INT_MAX);
		memset(visited, 0, sizeof(visited));
		memset(parent, -1, sizeof(parent));

		pq.emplace(0, 0);
		cost[0] = 0;

		T ans = 0;
		while (!pq.empty())
		{
			int cv = pq.top().v, cw = pq.top().w;
			pq.pop();

			if (visited[cv]) continue;
			visited[cv] = true;

			ans += cw;
			for (const auto& i : adj[cv])
			{
				if (!visited[i.v] && cost[i.v] > i.w)
				{
					cost[i.v] = i.w;
					pq.push(i);
					parent[i.v] = {cv, i.w};
				}
			}
		}

		for (int i = 0; i <= V; i++)
		{
			if (parent[i].first != -1) mst.emplace_back(i, parent[i].first, parent[i].second);
		}
		return ans;
	}

	vector<Edge> get_path() { return mst; }
};
