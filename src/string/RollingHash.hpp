/*
	Rolling Hash for fast computation of substring hashes
	Time complexity: O(N) init, O(1) get_hash, concat
	 where N is the size of the string
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, typename T, const T MOD, const int OFFSET, const int INDEXING>
struct RollingHash {
	template <typename T> T mod(T a, T m) { T res = a % m; return res < 0 ? res + m : res; }
	template <typename T> T add_mod(T a, T b, T m) { return mod(a + b, m); }
	T sub_mod(T a, T b, T m) { return mod(a - b, m); }
	T mul_mod(T a, T b, T m) { T res = 0; for (; b; a = add_mod(a, a, m), b >>= 1) if (b & 1) res = add_mod(res, a, m); return res; }
	T pre[MAXN + 1], hsh[MAXN + 1];
	void init(It st, It en, const T BASE = MOD / 2 + 5) {
		pre[0] = 1, hsh[N] = 0;
		for (int i = 1; i <= N; i++) pre[i] = mul_mod(pre[i - 1], BASE);
		for (It i = st; i != en; i++) hsh[i] = add_mod(mul_mod(hsh[i + 1], BASE), *i - OFFSET + 1);
	}
	T get_hash(int l, int r) { l -= INDEXING, r -= INDEXING; return sub_mod(hsh[l], mul_mod(hsh[r], pre[r - l])); }
	T concat(T a, T b, int alen) { return add_mod(a, mul_mod(b, pre[alen])); }
};
