/*
	KMP String Matching algorithm in linear time. search() returns
	the index of the first occurence of a match, or -1 if none exists.
	search_all() returns a vector of all possible occurences.

	- CONSTRUCTION
		Time:  O(1)
		Space: O(N)

	- void init(const string& pat)
		Time:  O(M)
		Space: O(M)

	- int search(const string& txt)
		Time:  O(N)
		Space: O(N)

	- vector<int> search_all(const string& txt)
		Time:  O(N)
		Space: O(N)
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

template <const int MAXN>
struct KMP
{
	int LPS[MAXN];
	string pat;
	vector<int> match;

	void init(const string& pat)
	{
		this->pat = pat, LPS[0] = -1;
		for (int i = 0, j = -1; i < int(pat.size()); i++, j++, LPS[i] = j)
		{
			while (j >= 0 && pat[i] != pat[j]) j = LPS[j];
		}
	}

	int search(const string& txt)
	{
		for (int i = 0, j = 0; i < int(txt.size()); i++, j++)
		{
			while (j >= 0 && txt[i] != pat[j]) j = LPS[j];
			if (j == int(pat.size()) - 1) return abs(i - j);
		}
		return -1;
	}

	vector<int> search_all(const string& txt)
	{
		match.clear();
		for (int i = 0, j = 0; i < txt.size(); i++, j++)
		{
			while (j >= 0 && txt[i] != pat[j]) j = LPS[j];
			if (j == int(pat.size()) - 1) match.push_back(abs(i - j));
		}
		return match;
	}
};
