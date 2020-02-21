/*
	Count primes up to N, using the Meissel-Lehmer method
	Time complexity: O(N / (log N)^4)
	 where N is the upper bound of the primes to be counted
*/

#pragma once
#include <bits/stdc++.h>

template <const uint32_t PI_CALC = 100000000, const uint32_t PHI_M = 7, const uint32_t PHI_PM = 2 * 3 * 5 * 7 * 11 * 13 * 17>
struct CountPrimes {
    bool np[PI_CALC]; uint32_t prime[PI_CALC], pi[PI_CALC], phi[PHI_PM + 1][PHI_M + 1], sz[PHI_M + 1];
    void init() {
        sz[0] = np[0] = np[1] = 1, prime[1] = 2;
        for (uint32_t i = 3; i * i < PI_CALC; i += 2) {
            if (!np[i])
                for (uint32_t j = i * i, k = i << 1; j < PI_CALC; j += k) np[j] = true;
        for (uint32_t i = 2, cnt = 1; i < PI_CALC; i++) {
            if ((i & 1) && !np[i]) prime[++cnt] = i;
            pi[i] = cnt;
        }
        for (uint32_t i = 0; i <= PHI_PM; i++) phi[i][0] = i;
        for (uint32_t i = 1; i <= PHI_M; i++) {
            sz[i] = prime[i] * sz[i - 1];
            for (uint32_t j = 1; j <= PHI_PM; j++) phi[j][i] = phi[j][i - 1] - phi[j / prime[i]][i - 1];
        }
    }
    uint64_t getphi(uint64_t x, uint32_t a) {
        if (a == 0) return x;
        if (a <= PHI_M) return phi[x % sz[a]][a] + (x / sz[a]) * phi[sz[a]][a];
        if (x <= prime[a] * prime[a]) return pi[x] - a + 1;
        if (x < PI_CALC && x <= prime[a] * prime[a] * prime[a]) {
            uint64_t b = pi[uint32_t(sqrt(x))], P2 = pi[x] - (b + a - 2) * (b - a + 1) / 2;
            for (uint32_t i = a + 1; i <= b; i++) P2 += pi[x / prime[i]];
            return P2;
        }
        return getphi(x, a - 1) - getphi(x / prime[a], a - 1);
    }
    uint64_t count(uint64_t x) {
        if (x < PI_CALC) return pi[x];
        uint32_t a = count(sqrt(sqrt(x))), b = count(sqrt(x)), c = count(cbrt(x));
        uint64_t P2 = getphi(x, a) + uint64_t(b + a - 2) * (b - a + 1) / 2;
        for (uint32_t i = a + 1; i <= b; i++) {
            uint64_t w = x / prime[i]; P2 -= count(w);
            if (i <= c) for (uint32_t j = i; j <= count(sqrt(w)); j++) P2 -= count(w / prime[j]) - j + 1;
        }
        return P2;
    }
};
