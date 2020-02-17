/*
	Collection of arithmetic functions involving integers
*/

#pragma once
#include <bits/stdc++.h>

template <typename T> T mod(T a, T m) { T res = a % m; return res < 0 ? res + m : res; }
template <typename T> T add_mod(T a, T b, T m) { return mod(a + b, m); }
template <typename T> T sub_mod(T a, T b, T m) { return mod(a - b, m); }
template <typename T> T mul_mod(T a, T b, T m) { T res = 0; for (; b; a = add_mod(a, a, m), b >>= 1) if (b & 1) res = add_mod(res, a, m); return res; }
template <typename T> T pow_mod(T a, T b, T m) { T res = 1; for (; b; a = mul_mod(a, a, m), b >>= 1) if (b & 1) res = mul_mod(res, a, m); return res; }
template <typename T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
template <typename T> T lcm(T a, T b) { return abs(a / gcd(a, b) * b); }
template <typename T> std::pair<T, T> exgcd(T a, T b) { if (b == 0) return std::make_pair(a > 0 ? 1 : -1, 0); auto res = exgcd(b, a % b); return std::make_pair(res.second, res.first - a / b * res.second); }
template <typename T> T mod_inv_prime(T a, T m) { return gcd(a, m) != 1 ? -1 : pow_mod(a, m - 2, m); }
template <typename T> T mod_inv_coprime(T a, T m) { return gcd(a, m) != 1 ? -1 : mod(exgcd(a, m).first, m); }
