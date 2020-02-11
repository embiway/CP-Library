#pragma once
#include <bits/stdc++.h>

using namespace std;
// WIP (try to implement operation over range (decomposition))
template <const int MAXN>
struct BitArray {
	unsigned long long bits[(MAXN >> 6) + 1];
	int _N;

	void init(int N) {
		_N = N;
	}

	bool operator[] (int i) const {
		return bits[i >> 6] & (1ULL << (i & 63));
	}

	void set(int i) {
		bits[i >> 6] |= (1ULL << (i & 63));
	}

	void reset(int i) {
		bits[i >> 6] &= ~(1ULL << (i & 63));
	}

	void flip(int i) {
		bits[i >> 6] ^= (1ULL << (i & 63));
	}

	bool any() {
		for (int i = 0; i <= _N >> 6; i++) if (bits[i]) return true;
		return false;
	}

	bool all() {
		for (int i = 0; i <= _N >> 6; i++) if (bits[i] != 18446744073709551615ULL) return false;
		return true;
	}

	string to_string() {
		string res = "";
		for (int i = 0; i <= _N; i++) res.push_back((*this)[i] + '0');
		return res;
	}
};
