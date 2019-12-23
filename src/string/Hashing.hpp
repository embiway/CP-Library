/*
	Template to calculate substring hashes in constant time. The get_hash()
	function calculates the hash of a substring [l, r). Refer to
	https://cp-algorithms.com/string/string-hashing.html for a good
	explaination on string hashing.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)

	- void init(const auto& s, const int N)
		Time:  O(N)
		Space: O(1)

	- T get_hash(int l, int r)
		Time:  O(1)
		Space: O(1)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN, typename T, const T MOD, const int OFFSET>
struct Hashing
{
    inline T add_mod(T a, T b) { T res = a + b; return res < MOD ? res : res - MOD; }
    inline T sub_mod(T a, T b) { T res = a - b; return res >= 0 ? res : res + MOD; }
    inline T mul_mod(T a, T b) { return a * b % MOD; }

	T pre[MAXN + 1], hsh[MAXN + 1];
	const T SEED = 987654321; // change this value if needed (must be smaller than MOD)

	void init(const auto& s, const int N)
	{
		pre[0] = 1, hsh[N] = 0;
		for (int i = 1; i <= N; i++) pre[i] = mul_mod(pre[i - 1], SEED);
		for (int i = N - 1; i >= 0; i--) hsh[i] = add_mod(mul_mod(hsh[i + 1], SEED), s[i] - OFFSET + 1);
	}

	T get_hash(int l, int r) { return sub_mod(hsh[l], mul_mod(hsh[r], pre[r - l])); }
};
