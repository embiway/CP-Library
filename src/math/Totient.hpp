/*
	Two implementations of the Euler totient (pϕ) function
	 - totient() the totient of a given number
	 - totient_sieve() a vector containing phi(x) for all integers [0, N]
	Time complexity:
	 1st method: O(sqrt(N)) where N is the size of the array
	 2nd method: O(N log log N) where N is the size of the array
*/

#pragma once
#include <bits/stdc++.h>

template <typename T>
T totient(T N) {
	T res = N;
	for (T i = 2; i * i <= N; i++) if (N % i == 0) for (res -= res / i; N % i == 0; N /= i);
	if (N > 1) res -= res / N;
	return res;
}

template <typename T>
std::vector<T> totient_sieve(T N) {
	std::vector<T> res(N + 1);
	for (T i = 0; i <= N; i++) res[i] = i & 1 ? i : i >> 1;
	for (T i = 3; i <= N; i += 2) if (res[i] == i) for (T j = i; j <= N; j += i) res[j] -= res[j] / i;
	return res;
}
