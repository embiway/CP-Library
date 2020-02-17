/*
	Convex Hull Trick for finding extremal value of a set of linear functions
	Static variant requires insertions and queries in sorted order
	Time complexity: O(N) init, O(1) query and insertion
	 where N is the number of linear functions
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, typename T, typename Compare = std::less<T>>
struct StaticCHT {
	int ptr, sz, ID[MAXN]; T M[MAXN], B[MAXN]; Compare comp;
	void init() { sz = ptr = 0; }
	void insert(T m, T b, int id) {
		while (ptr + 1 < sz && !comp((m - M[sz - 2]) * (B[sz - 2] - B[sz - 1]), (B[sz - 2] - b) * (M[sz - 1] - M[sz - 2]))) --sz;
		M[sz] = m, B[sz] = b, ID[sz++] = id;
	}
	std::pair<T, int> get(T x) {
		ptr = std::min(ptr, sz);
		while (ptr + 1 < sz && !comp(M[ptr + 1] * x + B[ptr + 1], M[ptr] * x + B[ptr])) ++ptr;
		return { M[ptr] * x + B[ptr], ID[ptr] };
	}
};
