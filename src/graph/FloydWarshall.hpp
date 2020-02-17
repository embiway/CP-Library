/*
	Floyd-Warshall algorithm for all-pairs shortest path in weighted graphs
	INF denotes no path, -INF denotes negative cycle
	 where INF is the value of std::numeric_limits<T>::max()
	Time complexity: O(V^3)
	 where V is the number of vertices
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXV, typename T, const int INDEXING>
struct FloydWarshall {
	const T INF = std::numeric_limits<T>::max(); T dist[MAXV + INDEXING][MAXV + INDEXING]; int V;
	void init(int V = MAXV) {
		this->V = V;
		for (int i = 0; i < V + INDEXING; i++) {
			std::fill(dist[i], dist[i] + V + INDEXING, INF);
			dist[i][i] = 0;
		}
	}
	void add(int u, int v, T w) { dist[u][v] = std::min(dist[u][v], w); }
	void add_bi(int u, int v, T w) { add(u, v, w); add(v, u, w); }
	void min_paths() {
		for (int i = 0; i < V + INDEXING; i++)
			for (int j = 0; j < V + INDEXING; j++)
				if (dist[j][i] != INF)
					for (int k = 0; k < V + INDEXING; k++)
						if (dist[i][k] != INF && dist[j][i] + dist[i][k] < dist[j][k])
							dist[j][k] = dist[j][i] + dist[i][k];
		for (int i = 0; i < V + INDEXING; i++)
			for (int j = 0; j < V + INDEXING; j++)
				for (int k = 0; k < V + INDEXING; k++)
					if (dist[k][k] < 0 && dist[i][k] != INF && dist[k][j] != INF) {
						dist[i][j] = -INF;
						break;
					}
	}
};
