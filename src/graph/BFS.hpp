/*
	Implementation of BFS (Breadth-First Search) with std::queue.
	min_path() returns the dist[] array, where the disconnected nodes
	have a value of INT_MAX. The get_path() function takes in an argument,
	the destination, and returns a vector of a shortest path from the
	source (given in min_path() argument), to the destination.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(V)

	- void add(int u, int v)
		Time:  O(1)
		Space: O(1)

	- void add_bi(int u, int v)
		Time:  O(1)
		Space: O(1)

	- int* min_path(int u)
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

template <const int V>
struct BFS
{
	vector<int> adj[V + 1];
	queue<int> q;
	int dist[V + 1], parent[V + 1];

	void add(int u, int v) { adj[u].push_back(v); }

	void add_bi(int u, int v) { add(u, v); add(v, u); }

	int* min_path(int v)
	{
		queue<int>().swap(q);
		fill(dist, dist + V + 1, INT_MAX);
		memset(parent, -1, sizeof(parent));

		q.push(v);
		dist[v] = 0;

		while (!q.empty())
		{
			int curr = q.front();
			q.pop();

			for (int i : adj[curr])
			{
				if (dist[i] == INT_MAX)
				{
					parent[i] = curr;
					dist[i] = dist[curr] + 1;
					q.push(i);
				}
			}
		}
		return dist;
	}

	vector<int> get_path(int v)
	{
		vector<int> res;
		for (; v != -1; v = parent[v]) res.push_back(v);
		reverse(res.begin(), res.end());
		return res;
	}

	void clear() { for (int i = 0; i <= V; i++) adj[i].clear(); }
};
