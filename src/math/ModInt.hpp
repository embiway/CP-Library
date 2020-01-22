/*
	A handy collection of operations involving modulo,
	such as pow_mod() and mul_mod(). It can probably handle
	numbers up to 2 ^ 63 - 1.
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

namespace ModInt {
	typedef unsigned long long ull;

	ull mul_mod(ull a, ull b, ull m) {
		ull res = 0;
		while (b) {
			if (b & 1) res = (res + a) % m;
			a = (a << 1) % m;
			b >>= 1;
		}
		return res;
	}

	ull pow_mod(ull a, ull b, ull m) {
		ull res = 1;
		while (b) {
			if (b & 1) res = mul_mod(res, a, m);
			a = mul_mod(a, a, m);
			b >>= 1;
		}
		return res;
	}
}
