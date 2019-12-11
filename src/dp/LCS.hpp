/*
	Implementation of the classic Longest Common Subsequence problem.
	The LCS() function returns a vector of the sequence. Also, a fast
	algorithm for calculating the LCS of strings is implemented using
	the Allison-Dix algorithm.

	- vector<T> LCS(const auto& a, const auto& b, const int n, const int m)
		Time:  O(N * M)
		Space: O(N * M)

	- int LCS(string a, string b)
		Time:  O(N * M / 64)
		Space: O(N * 26)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <typename T>
vector<T> LCS(const auto& a, const auto& b, const int n, const int m)
{
	int** dp = new int*[n + 1];
	for (int i = 0; i <= n; i++) dp[i] = new int[m + 1];

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else                      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	vector<T> lcs;
	for (int i = n, j = m; i && j; )
	{
		if (dp[i][j] == dp[i - 1][j]) --i;
		else if (dp[i][j] == dp[i][j - 1]) --j;
		else
		{
			lcs.push_back(a[i - 1]);
			--i, --j;
		}
	}

	for (int i = 0; i <= n; i++) delete[] dp[i];
	delete[] dp;

	reverse(lcs.begin(), lcs.end());
	return lcs;
}

int LCS(string a, string b)
{
	typedef unsigned long long ull;

	int n = a.size(), m = b.size();
	if (n < m) { a.swap(b); swap(n, m); }
	const int sz = (n + 63) >> 6;

	ull* l = new ull[n + 1];
	ull** occ = new ull*[26];
	for (int i = 0; i <= 26; i++) occ[i] = new ull[n + 1];

	ull bit = 1;
	for (int i = 0, j = 0; i < n; i++)
	{
		occ[a[i] - 'a'][j] |= bit;
		bit <<= 1;
		if (!bit) ++bit, ++j;
	}

	ull b1, b2, c, v, u;
	for (int i = 0; i < m; i++)
	{
		b1 = 1, b2 = 0;
		for (int j = 0; j < sz; j++) u = l[j] | occ[b[i] - 'a'][j], c = l[j] >> 63, v = u - ((l[j] << 1) | (b1 + b2)), b1 = c, b2 = v > u, l[j] = u & ~v;
	}

	int lcs = 0;
	for (int i = 0; i < sz; i++)
	{
		for (; l[i]; lcs++) l[i] &= l[i] - 1;
	}

	for (int i = 0; i <= 26; i++) delete[] occ[i];
	delete[] occ;
	delete[] l;
	return lcs;
}
