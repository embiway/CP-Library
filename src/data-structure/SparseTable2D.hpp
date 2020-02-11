/*
	Implementation of a 2D Sparse Table. Essentially the same
	as SparseTable.hpp, except it's 2D. Read this Codeforces
	blog for more info: "https://codeforces.com/blog/entry/45485".

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N * M * log N * log M)

	- void init(const auto& a, const int N = MAXN, const int M = MAXM)
		Time:  O(N * M * log N * log M)
		Space: O(1)

	- T query(const int u, const int d, const int l, const int r)
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, const int MAXM, typename T>
struct SparseTable2D
{
	static const int MAXLGN = 32 - __builtin_clz(MAXN), MAXLGM = 32 - __builtin_clz(MAXM);
	T st[MAXLGN][MAXN][MAXLGM][MAXM];
	int lg[max(MAXN, MAXM) + 1], _N, _M;

	T merge(T left, T right); // query type?

	void init(const auto& a, const int N = MAXN, const int M = MAXM) {
		_N = N, _M = M;
		const int LGN = 32 - __builtin_clz(_N), LGM = 32 - __builtin_clz(_M);
		for (int ir = 0; ir < _N; ir++) {
			for (int ic = 0; ic < _M; ic++) {
				st[0][ir][0][ic] = a[ir][ic];
			}
		}
		for (int ir = 0; ir < _N; ir++) {
			for (int jc = 0; jc < LGM - 1; jc++) {
				for (int ic = 0; ic + (1 << jc) < _M; ic++) {
					st[0][ir][jc + 1][ic] = merge(st[0][ir][jc][ic], st[0][ir][jc][ic + (1 << jc)]);
				}
			}
		}
		lg[1] = 0;
		for (int i = 2; i <= max(_N, _M); i++) lg[i] = lg[i >> 1] + 1;
		for (int jr = 0; jr < LGN - 1; jr++) {
			for (int ir = 0; ir + (1 << jr) < _N; ir++) {
				for (int jc = 0; jc < LGM; jc++) {
					for (int ic = 0; ic < _M; ic++) {
						st[jr + 1][ir][jc][ic] = merge(st[jr][ir][jc][ic], st[jr][ir + (1 << jr)][jc][ic]);
					}
				}
			}
		}
	}

	T query(const int u, const int d, const int l, const int r) {
		int kr = lg[d - u + 1], kc = lg[r - l + 1];
		return merge(merge(st[kr][u][kc][l], st[kr][u][kc][r - (1 << kc) + 1]), merge(st[kr][d - (1 << kr) + 1][kc][l], st[kr][d - (1 << kr) + 1][kc][r - (1 << kc) + 1]));
	}
};
