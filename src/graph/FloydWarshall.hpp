/*
	Implementation of the Floyd Warshall shortest path
	algorithm. Negative cycles are denoted as -INF, and
	no valid path is denoted as INF. TODO: Johnson's algorithm
	can be implemented with time complexity of O(V ^ 2 * log V + V * E).

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N ^ 2)

	- void init(const int V = MAXV)
		Time:  O(N)
		Space: O(1)

	- void add(const int u, const int v, const T w)
		Time:  O(1)
		Space: O(1)

	- void add_bi(const int u, const int v, const T w)
		Time:  O(1)
		Space: O(1)

	- void get_paths()
		Time:  O(N ^ 3)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXV, typename T>
struct FloydWarshall {
	const T INF = numeric_limits<T>::max();
	T dist[MAXV][MAXV];
	int _V;

	void init(const int V = MAXV) {
		_V = V;
		for (int i = 0; i < _V; i++) {
			fill(dist[i], dist[i] + _V, INF);
			dist[i][i] = 0;
		}
	}

	void add(const int u, const int v, const T w) {
		dist[u][v] = min(dist[u][v], w);
	}

	void add_bi(const int u, const int v, const T w) {
		add(u, v, w); add(v, u, w);
	}

	void get_paths() {
		for (int i = 0; i < _V; i++) {
			for (int j = 0; j < _V; j++) {
				if (dist[j][i] != INF) {
					for (int k = 0; k < _V; k++) {
						if (dist[i][k] != INF && dist[j][i] + dist[i][k] < dist[j][k]) {
							dist[j][k] = dist[j][i] + dist[i][k];
						}
					}
				}
			}
		}
		for (int i = 0; i < _V; i++) {
			for (int j = 0; j < _V; j++) {
				for (int k = 0; k < _V; k++) {
					if (dist[k][k] < 0 && dist[i][k] != INF && dist[k][j] != INF) {
						dist[i][j] = -INF;
						break;
					}
				}
			}
		}
	}
};
