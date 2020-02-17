/*
	Two implementations of Sieve of Eratosthenes for primes in a range [A, B)
	Time complexity: O(N log log N) get_primes, O(R + B log log sqrt{B}) get_primes_range
	 where N and B are the upper bound of primes, and R is the range of the lower and upper bounds
*/

#pragma once
#include <bits/stdc++.h>

#define ifc(x) (is_prime[(x) >> 6] & (1 << (((x) >> 1) & 31)))
#define isc(x) (is_prime[(x) >> 6] |= (1 << (((x) >> 1) & 31)))

template <typename T>
std::vector<T> get_primes(T N) {
	std::vector<T> res; std::vector<int> is_prime((N >> 6) + 1);
	for (T i = 3; i * i <= N; i += 2) if (!ifc(i)) for (T j = i * i, k = i << 1; j <= N; j += k) isc(j);
	if (N >= 2) res.push_back(2);
	for (T i = 3; i <= N; i += 2) if (!ifc(i)) res.push_back(i);
	return res;
}

template <typename T>
std::vector<T> get_primes_range(T A, T B) {
	assert(A <= B); std::vector<T> primes = get_primes<T>(std::sqrt(B)), res; std::vector<int> is_prime(((B - A + 1) >> 6) + 1);
	if (B < 2) return res;
	if (A < 3) { res.push_back(2); A = 3; }
	if ((A & 1) == 0) ++A;
	for (int i = 1; i < int(primes.size()); i++) {
		T p = primes[i], j = (A + p - 1) / p * p;
		if ((j & 1) == 0) j += p;
		for (T k = p << 1; j <= B; j += k) if (j != p) isc(j - A);
	}
	for (T i = 0; i <= B - A; i += 2) if (!ifc(i)) res.push_back(A + i);
	return res;
}
