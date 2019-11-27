/*
	A relatively fast prime-sieve algorithm using the Sieve of Eratosthenes.
	get_primes() uses a bitset to decrease the space complexity by a factor of 64.
	The get_primes_range() function uses a segmented sieve as well as bitset.
	Submitting this to SPOJ - TDPRIMES gets accepted in 0.31s. TODO: learn wheel
	factorization.

	- vector<T> get_primes(int N)
		Time:  O(N * log log N)
		Space: O(N / 64)

	- vector<T> get_primes_range(T A, T B)
	    * R is the range from A to B (B - A + 1) *
		Time:  O(R * log log R)
		Space: O(sqrt(B) + R / 64)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

namespace Sieve
{
	#define ifc(x) (is_prime[(x) >> 6] & (1 << (((x) >> 1) & 31)))
	#define isc(x) (is_prime[(x) >> 6] |= (1 << (((x) >> 1) & 31)))
    
	template <typename T>
	vector<T> get_primes(int N)
	{
		vector<T> is_prime((N >> 6) + 1), res;
		for (T i = 3; i * i <= N; i += 2)
		{
			if (!ifc(i))
			{
				for (T j = i * i, k = i << 1; j <= N; j += k) isc(j);
			}
		}

		if (N >= 2) res.push_back(2);
		for (T i = 3; i <= N; i += 2)
		{
			if (!ifc(i)) res.push_back(i);
		}
		return res;
	}
    
	template <typename T>
	vector<T> get_primes_range(T A, T B)
	{
	    assert(A <= B);
        vector<T> primes = get_primes<T>(sqrt(B)), is_prime(((B - A + 1) >> 6) + 1), res;
        
        if (B < 2) return res;
        if (A < 3) A = 3;
        if ((A & 1) == 0) ++A;
        
        for (T i = 1; i < primes.size(); i++)
        {
            T p = primes[i], j = (A + p - 1) / p * p;
            if ((j & 1) == 0) j += p;

            for (T k = p << 1; j <= B; j += k)
            {
                if (j != p) isc(j - A);
            }
        }
        
        if (A >= 2) res.push_back(2);
        for (T i = 0; i <= B - A; i += 2)
        {
            if (!ifc(i)) res.push_back(A + i);
        }
        return res;
	}
};
