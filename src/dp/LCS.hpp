/*
	Two implementations of the Longest Common Subsequence problem
	 - classic DP method which returns a vector of the LCS
	 - Allison-Dix algorithm for lowercase strings (1st string must be larger)
	Time complexity:
	 1st method: O(NM) where N and M are the lengths of the arrays, respectively
	 2nd method: O(NM / 64) where N and M are the lengths of the strings, respectively
*/

#pragma once
#include <bits/stdc++.h>

template <typename It1, typename It2>
std::vector<typename std::iterator_traits<It1>::value_type> LCS(It1 st1, It1 en1, It2 st2, It2 en2) {
	int N = en1 - st1, M = en2 - st2, **dp = new int*[N + 1]; std::vector<typename std::iterator_traits<It1>::value_type> lcs;
	for (int i = 0; i <= N; i++) dp[i] = new int[M + 1];
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			dp[i][j] = *(st1 + i - 1) == *(st2 + j - 1) ? dp[i - 1][j - 1] + 1 : std::max(dp[i - 1][j], dp[i][j - 1]);
	for (int i = N, j = M; i && j; ) {
		if (dp[i][j] == dp[i - 1][j]) --i;
		else if (dp[i][j] == dp[i][j - 1]) --j;
		else lcs.push_back(*(st1 + i - 1)), --i, --j;
	}
	for (int i = 0; i <= N; i++) delete[] dp[i];
	delete[] dp; std::reverse(lcs.begin(), lcs.end());
	return lcs;
}

template <typename It1, typename It2>
int LCS(It1 st1, It1 en1, It2 st2, It2 en2) {
	int N = en1 - st1, M = en2 - st2, sz = (N + 63) >> 6, lcs = 0;
	uint64_t bit = 1, b1, b2, v, u, *l = new uint64_t[N + 1], **occ = new uint64_t*[26];
	for (int i = 0; i <= 26; i++) occ[i] = new uint64_t[N + 1];
	for (int i = 0, j = 0; i < N; i++) {
		occ[*(st1 + i) - 'a'][j] |= bit, bit <<= 1;
		if (!bit) ++bit, ++j;
	}
	for (int i = 0; i < M; i++)
		for (int j = 0, b1 = 1, b2 = 0; j < sz; j++)
			u = l[j] | occ[*(st2 + i) - 'a'][j], v = u - ((l[j] << 1) | (b1 + b2)), b1 = l[j] >> 63, b2 = v > u, l[j] = u & ~v;
	for (int i = 0; i < sz; i++) for (; l[i]; lcs++) l[i] &= l[i] - 1;
	for (int i = 0; i <= 26; i++) delete[] occ[i];
	delete[] occ; delete[] l;
	return lcs;
}
