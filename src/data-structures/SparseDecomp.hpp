/*
	An algorithm to solve RMQ. Uses 'macro' and 'micro' sparse tables
	and sqrt decomposition achieving O(N log log N) time complexity.
	A link to this structure can be found here: "https://web.stanfor
	d.edu/class/cs166/lectures/00/Small00.pdf" Theoretically, this
	structure can be recursed several times to achieve an O(N log* N)
	algorithm. Note: The current implementation is buggy and the block
	size must be log2(N) for it to work.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N log log N)

	- void init(const auto& a, const int N = MAXN, const int BLKSZ = MAXBLKSZ)
		Time:  O(N log log N)
		Space: O(1)

	- T query(const int l, const int r)
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, const int MAXBLKSZ, typename T>
struct SparseDecomp {
    T macro[32 - __builtin_clz(MAXN / MAXBLKSZ)][MAXN / MAXBLKSZ + 1], micro[32 - __builtin_clz(MAXBLKSZ)][MAXN];
    int lg[MAXN + 1], _N, _BLKSZ;

    T merge(T left, T right); // query type?

    void init(const auto& a, const int N = MAXN, const int BLKSZ = MAXBLKSZ) {
    	_N = N, _BLKSZ = BLKSZ;
        lg[1] = 0;
        for (int i = 2; i <= _N; i++) lg[i] = lg[i >> 1] + 1;
        for (int i = 0; i < _N; i++) micro[0][i] = a[i];
        for (int i = 0; i < _N; i += _BLKSZ) {
            int bound = min(_N, i + _BLKSZ);
            for (int k = 0; k < lg[_BLKSZ]; k++) {
                for (int j = i; j + (1 << k) < bound; j++) {
                    micro[k + 1][j] = merge(micro[k][j], micro[k][j + (1 << k)]);
                }
            }
            macro[0][i / _BLKSZ] = query_micro(i, bound - 1);
        }
        for (int j = 0; j < lg[_N / _BLKSZ]; j++) {
            for (int i = 0; i + (1 << j) < _N / _BLKSZ; i++) {
                macro[j + 1][i] = merge(macro[j][i], macro[j][i + (1 << j)]);
            }
        }
    }

    T query(const int l, const int r) {
        int lblk = l / _BLKSZ, rblk = r / _BLKSZ, lbound = (lblk + 1) * _BLKSZ - 1, rbound = rblk * _BLKSZ;
        if (lblk == rblk) return query_micro(l, r);
        else if (rblk - lblk == 1) return merge(query_micro(l, lbound), query_micro(rbound, r));
        else return merge(query_macro(lblk + 1, rblk - 1), merge(query_micro(l, lbound), query_micro(rbound, r)));
    }

private:
    T query_micro(const int l, const int r) {
        int k = lg[r - l + 1];
        return merge(micro[k][l], micro[k][r - (1 << k) + 1]);
    }

    T query_macro(const int l, const int r) {
        int k = lg[r - l + 1];
        return merge(macro[k][l], macro[k][r - (1 << k) + 1]);
    }
};
