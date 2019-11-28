/*
	Implementation of Kruskal's Algorithm to solve Minimum Spanning Tree.
	Kruskal's Algorithm greedily solves by finding smallest weight which does
	not produce a cycle, which can be achieved fast using the Disjoint Set.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(1)

	- void add(int u, int v, T w)
		Time:  O(1)
		Space: O(1)

	- T min_path()
		Time:  O(E * log E)
		Space: O(V + E)

	- vector<Edge<T>> get_path()
		Time:  O(V)
		Space: O(1)

	- void clear()
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include "../data-structures/DisjointSet.hpp"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Edge
{
	int u, v; T w;

	Edge(int u, int v, T w) : u(u), v(v), w(w) {}

	bool operator < (const Edge& e) const { return w < e.w; }
};

template <const int V, typename T>
struct Kruskal
{
	vector<Edge<T>> graph, mst;
	DisjointSet<V> ds;

	void add(int u, int v, T w) { graph.emplace_back(u, v, w); }

	T min_path()
	{
		ds.init();
		sort(graph.begin(), graph.end());

		T ans = 0; int sz = 0;
		for (const auto& i : graph)
		{
			if (sz > V) break;
			if (ds.join(i.u, i.v)) { mst.push_back(i); ans += i.w; ++sz; }
		}
		return ans;
	}

	vector<Edge<T>> get_path() { return mst; }

	void clear() { graph.clear(); mst.clear(); }
};
